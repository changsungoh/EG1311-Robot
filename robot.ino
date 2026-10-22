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
// Current physical observation:
// - The previous HIGH/LOW motor command drove the robot backwards.
// - Forward is therefore set to the opposite LOW/HIGH command on both sides.
//
// Values that still need final course calibration:
// - STOP_DISTANCE_CM
// - SERVO_REST_ANGLE / SERVO_FIRE_ANGLE
// - Settling/firing delays

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

// Reduced from the old 30 cm starter value so the robot can approach
// the wall more closely. Fine-tune on the real course.
const float STOP_DISTANCE_CM = 15.0;

const int SERVO_REST_ANGLE = 0;
const int SERVO_FIRE_ANGLE = 90;

const unsigned long SETTLING_DELAY_MS = 500;
const unsigned long FIRE_HOLD_MS = 500;

// ---------- State ----------
Servo catapultServo;
bool catapultFired = false;

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
  // Reversed from the earlier command because the physical robot
  // was observed moving backwards.
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, HIGH);

  digitalWrite(RIGHT_IN3_PIN, LOW);
  digitalWrite(RIGHT_IN4_PIN, HIGH);
}

void stopMotors() {
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, LOW);

  digitalWrite(RIGHT_IN3_PIN, LOW);
  digitalWrite(RIGHT_IN4_PIN, LOW);
}

void fireCatapultOnce() {
  if (catapultFired) {
    return;
  }

  stopMotors();
  delay(SETTLING_DELAY_MS);

  catapultServo.write(SERVO_FIRE_ANGLE);
  delay(FIRE_HOLD_MS);
  catapultServo.write(SERVO_REST_ANGLE);

  catapultFired = true;
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

  catapultServo.attach(SERVO_PIN, 660, 2400);
  catapultServo.write(SERVO_REST_ANGLE);

  Serial.println("EG1311 robot ready.");
  delay(1000);
}

void loop() {
  float distanceCm = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Fail safe: if the sensor gives no valid echo, do not keep driving.
  if (distanceCm < 0) {
    Serial.println("No ultrasonic reading -> STOP");
    stopMotors();
    delay(100);
    return;
  }

  // Once the catapult has fired, keep the robot stationary.
  if (catapultFired) {
    stopMotors();
    delay(100);
    return;
  }

  if (distanceCm > STOP_DISTANCE_CM) {
    Serial.println("Forward");
    moveForward();
  } else {
    Serial.println("Wall reached -> STOP");
    stopMotors();
    fireCatapultOnce();
  }

  delay(50);
}
