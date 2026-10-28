// EG1311 Robot - Integrated autonomous program
// Branch policy: feature branch -> dev -> main
//
// Confirmed team wiring:
// - HC-SR04: TRIG D9, ECHO D10
// - Left motor direction:  D4 -> L293D pin 2 (1A), D7 -> pin 7 (2A)
// - Right motor direction: D8 -> L293D pin 10 (3A), D12 -> pin 15 (4A)
// - Motor enables (PWM):  D5 -> L293D pin 1 (1,2EN), D6 -> pin 9 (3,4EN)
// - Servo signal: D3
//
// Latest physical observation:
// - Motor direction was physically reversed.
// - Forward is now HIGH/LOW on both sides.
//
// Sequence:
// 1. Drive forward over the obstacles.
// 2. Stop near the wall.
// 3. Fire the catapult.
// 4. Reverse for BACKUP_TIME_MS.
// 5. Stop.
//
// Servo control:
// - Throw pulse: 1273 us
// - Withdraw pulse: 2500 us
// - Approximately 120 degrees of travel

#include <Servo.h>

// ---------- Wiring ----------
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

const int LEFT_IN1_PIN = 4;
const int LEFT_IN2_PIN = 7;
const int RIGHT_IN3_PIN = 8;
const int RIGHT_IN4_PIN = 12;

const int LEFT_ENABLE_PIN = 5;
const int RIGHT_ENABLE_PIN = 6;

const int SERVO_PIN = 3;

// ---------- Calibration ----------
const float SOUND_SPEED_CM_PER_US = 0.0345;
const float STOP_DISTANCE_CM = 25.0;

const int SERVO_THROW_PULSE_US = 1273;
const int SERVO_WITHDRAW_PULSE_US = 2500;

const int SERVO_MIN_PULSE_US = 544;
const int SERVO_MAX_PULSE_US = 2500;

const unsigned long SETTLING_DELAY_MS = 500;
const unsigned long FIRE_HOLD_MS = 500;

// Slight forward-speed reduction using the L293D enable pins.
// PWM range is 0-255; 230 is about 90% duty cycle.
const int FORWARD_SPEED_PWM = 230;
const int BACKWARD_SPEED_PWM = 190;

// Confirm a possible wall while the robot is stationary.
// This avoids requiring the robot to "clear" the ramp before wall detection can work.
const int WALL_CONFIRM_READINGS = 3;

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

bool confirmWall() {
  stopMotors();
  delay(100);

  for (int i = 0; i < WALL_CONFIRM_READINGS; i++) {
    float confirmDistanceCm = readDistanceCm();

    Serial.print("Confirm reading ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(confirmDistanceCm);
    Serial.println(" cm");

    if (confirmDistanceCm < 0 || confirmDistanceCm > STOP_DISTANCE_CM) {
      return false;
    }

    delay(50);
  }

  return true;
}

void moveForward() {
  analogWrite(LEFT_ENABLE_PIN, FORWARD_SPEED_PWM);
  analogWrite(RIGHT_ENABLE_PIN, FORWARD_SPEED_PWM);

  digitalWrite(LEFT_IN1_PIN, HIGH);
  digitalWrite(LEFT_IN2_PIN, LOW);

  digitalWrite(RIGHT_IN3_PIN, HIGH);
  digitalWrite(RIGHT_IN4_PIN, LOW);
}

void setBackwardDirection() {
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, HIGH);

  digitalWrite(RIGHT_IN3_PIN, LOW);
  digitalWrite(RIGHT_IN4_PIN, HIGH);
}

void moveBackwardSmooth() {
  // Soft-start reverse to reduce the sudden weight transfer that can tip the robot.
  setBackwardDirection();

  for (int pwm = 120; pwm <= BACKWARD_SPEED_PWM; pwm += 10) {
    analogWrite(LEFT_ENABLE_PIN, pwm);
    analogWrite(RIGHT_ENABLE_PIN, pwm);
    delay(40);
  }
}

void stopMotors() {
  analogWrite(LEFT_ENABLE_PIN, 0);
  analogWrite(RIGHT_ENABLE_PIN, 0);

  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, LOW);

  digitalWrite(RIGHT_IN3_PIN, LOW);
  digitalWrite(RIGHT_IN4_PIN, LOW);
}

void fireAndReturn() {
  stopMotors();
  delay(SETTLING_DELAY_MS);

  catapultServo.writeMicroseconds(SERVO_THROW_PULSE_US);
  delay(FIRE_HOLD_MS);
  catapultServo.writeMicroseconds(SERVO_WITHDRAW_PULSE_US);

  // Return after firing.
  delay(300);
  moveBackwardSmooth();
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
  pinMode(LEFT_ENABLE_PIN, OUTPUT);
  pinMode(RIGHT_ENABLE_PIN, OUTPUT);

  stopMotors();

  catapultServo.attach(SERVO_PIN, SERVO_MIN_PULSE_US, SERVO_MAX_PULSE_US);
  catapultServo.writeMicroseconds(SERVO_WITHDRAW_PULSE_US);

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

  if (distanceCm <= STOP_DISTANCE_CM) {
    Serial.println("Possible wall -> STOP and confirm");

    if (confirmWall()) {
      Serial.println("Wall confirmed -> FIRE -> REVERSE");
      fireAndReturn();
      return;
    }

    Serial.println("False alarm -> continue forward");
  }

  Serial.println("Forward (PWM 230/255)");
  moveForward();

  delay(50);
}
