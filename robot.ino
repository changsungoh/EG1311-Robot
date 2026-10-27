// EG1311 Robot - Integrated autonomous program
// Branch policy: feature branch -> dev -> main
//
// Confirmed team wiring:
// - HC-SR04: TRIG D9, ECHO D10
// - Left motor:  D5 -> L293D IN1, D6 -> L293D IN2
// - Right motor: D7 -> L293D IN3, D8 -> L293D IN4
// - Servo signal: D3
// - L293D enable pins 1 and 9 are tied HIGH to 5V.
//
// Latest physical observation:
// - HIGH/LOW makes the robot move backwards.
// - Forward is therefore LOW/HIGH on both sides.
//
// Sequence:
// 1. Drive forward over the obstacles.
// 2. Stop near the wall.
// 3. Fire the catapult.
// 4. Reverse for BACKUP_TIME_MS.
// 5. Stop.
//
// Servo control:
// - Rest pulse: 660 us
// - Fire pulse: 2500 us

#include <Servo.h>

// ---------- Wiring ----------
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

const int LEFT_IN1_PIN = 5;
const int LEFT_IN2_PIN = 6;
const int RIGHT_IN3_PIN = 7;
const int RIGHT_IN4_PIN = 8;

const int SERVO_PIN = 3;

// ---------- Calibration ----------
const float SOUND_SPEED_CM_PER_US = 0.0345;
const float STOP_DISTANCE_CM = 15.0;

const int SERVO_REST_PULSE_US = 660;
const int SERVO_FIRE_PULSE_US = 2500;

const unsigned long SETTLING_DELAY_MS = 500;
const unsigned long FIRE_HOLD_MS = 500;

// Slight forward-speed reduction without rewiring the L293D enable pins.
// 45 ms ON + 5 ms OFF = 90% software duty cycle.
const unsigned long FORWARD_ON_MS = 45;
const unsigned long FORWARD_OFF_MS = 5;

// Tune this so the robot reverses the required distance after firing.
const unsigned long BACKUP_TIME_MS = 3000;

// ---------- State ----------
Servo catapultServo;
bool sequenceComplete = false;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long echoTimeUs = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (echoTimeUs == 0) {
    return -1.0;
  }

  return echoTimeUs * SOUND_SPEED_CM_PER_US / 2.0;
}

void moveForward() {
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, HIGH);

  digitalWrite(RIGHT_IN3_PIN, LOW);
  digitalWrite(RIGHT_IN4_PIN, HIGH);
}

void moveForwardReducedSpeed() {
  moveForward();
  delay(FORWARD_ON_MS);
  stopMotors();
  delay(FORWARD_OFF_MS);
}

void moveBackward() {
  // Exact opposite of moveForward().
  digitalWrite(LEFT_IN1_PIN, HIGH);
  digitalWrite(LEFT_IN2_PIN, LOW);

  digitalWrite(RIGHT_IN3_PIN, HIGH);
  digitalWrite(RIGHT_IN4_PIN, LOW);
}

void stopMotors() {
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, LOW);

  digitalWrite(RIGHT_IN3_PIN, LOW);
  digitalWrite(RIGHT_IN4_PIN, LOW);
}

void fireAndReturn() {
  stopMotors();
  delay(SETTLING_DELAY_MS);

  catapultServo.writeMicroseconds(SERVO_FIRE_PULSE_US);
  delay(FIRE_HOLD_MS);
  catapultServo.writeMicroseconds(SERVO_REST_PULSE_US);

  // Return after firing.
  delay(200);
  moveBackward();
  delay(BACKUP_TIME_MS);
  stopMotors();

  sequenceComplete = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  pinMode(LEFT_IN1_PIN, OUTPUT);
  pinMode(LEFT_IN2_PIN, OUTPUT);
  pinMode(RIGHT_IN3_PIN, OUTPUT);
  pinMode(RIGHT_IN4_PIN, OUTPUT);

  stopMotors();

  catapultServo.attach(SERVO_PIN, SERVO_REST_PULSE_US, SERVO_FIRE_PULSE_US);
  catapultServo.writeMicroseconds(SERVO_REST_PULSE_US);

  Serial.println("EG1311 robot ready.");
  delay(1000);
}

void loop() {
  // Full run is completed once: forward -> fire -> reverse -> stop.
  if (sequenceComplete) {
    stopMotors();
    delay(100);
    return;
  }

  float distanceCm = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  if (distanceCm < 0) {
    Serial.println("No ultrasonic reading -> STOP");
    stopMotors();
    delay(100);
    return;
  }

  if (distanceCm > STOP_DISTANCE_CM) {
    Serial.println("Forward (90% speed)");
    moveForwardReducedSpeed();
  } else {
    Serial.println("Wall reached -> FIRE -> REVERSE");
    fireAndReturn();
  }

  delay(50);
}
