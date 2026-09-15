// EG1311 Robot - Integration Skeleton
// Branch policy: feature branch -> dev -> main
//
// Confirmed from the team's TinkerCAD / wiring notes:
// - HC-SR04: TRIG D9, ECHO D10
// - Left motor:  D5 -> L293D pin 2 (IN1), D6 -> pin 7 (IN2)
// - Right motor: D7 -> L293D pin 10 (IN3), D8 -> pin 15 (IN4)
// - Servo signal: D3
// - L293D enable pins 1 and 9 are tied to 5V, so no Arduino enable pins are required.
//
// Still NOT confirmed:
// - Which HIGH/LOW combinations make both physical wheels move the robot forward
// - Servo resting/firing angles
// - Final stopping distance and timing on the real course

#include <Servo.h>

// ---------- Confirmed wiring ----------
const int TRIG_PIN = 9;
const int ECHO_PIN = 10;

const int LEFT_IN1_PIN = 5;   // L293D pin 2
const int LEFT_IN2_PIN = 6;   // L293D pin 7
const int RIGHT_IN3_PIN = 7;  // L293D pin 10
const int RIGHT_IN4_PIN = 8;  // L293D pin 15

const int SERVO_PIN = 3;

const float SOUND_SPEED_CM_PER_US = 0.0345;

// ---------- Must be calibrated / physically verified ----------
const float STOP_DISTANCE_CM = 30.0; // TODO: calibrate on the real course

// Leave these as -1 until the physical motor direction is tested.
// Set each value to HIGH or LOW only after confirming the real wheel direction.
const int LEFT_FORWARD_IN1_LEVEL = -1;
const int LEFT_FORWARD_IN2_LEVEL = -1;
const int RIGHT_FORWARD_IN3_LEVEL = -1;
const int RIGHT_FORWARD_IN4_LEVEL = -1;

// Leave these as -1 until the catapult mechanism is physically calibrated.
const int SERVO_REST_ANGLE = -1;
const int SERVO_FIRE_ANGLE = -1;

Servo catapultServo;
bool catapultFired = false;
bool servoReady = false;
bool motorDirectionReady = false;

bool validDigitalLevel(int value) {
  return value == LOW || value == HIGH;
}

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long microseconds = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (microseconds == 0) {
    return -1.0; // no echo / timeout
  }

  return microseconds * SOUND_SPEED_CM_PER_US / 2.0;
}

void stopMotors() {
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, LOW);
  digitalWrite(RIGHT_IN3_PIN, LOW);
  digitalWrite(RIGHT_IN4_PIN, LOW);
}

void moveForward() {
  if (!motorDirectionReady) {
    stopMotors();
    return;
  }

  digitalWrite(LEFT_IN1_PIN, LEFT_FORWARD_IN1_LEVEL);
  digitalWrite(LEFT_IN2_PIN, LEFT_FORWARD_IN2_LEVEL);
  digitalWrite(RIGHT_IN3_PIN, RIGHT_FORWARD_IN3_LEVEL);
  digitalWrite(RIGHT_IN4_PIN, RIGHT_FORWARD_IN4_LEVEL);
}

void fireCatapultOnce() {
  if (catapultFired || !servoReady) {
    return;
  }

  stopMotors();
  delay(500); // TODO: tune settling delay on the real robot

  catapultServo.write(SERVO_FIRE_ANGLE);
  delay(500); // TODO: tune firing movement timing
  catapultServo.write(SERVO_REST_ANGLE);

  catapultFired = true;
}

void setup() {
  Serial.begin(9600);

  // HC-SR04
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  // L293D motor inputs. Enable pins 1 and 9 are permanently tied to 5V.
  pinMode(LEFT_IN1_PIN, OUTPUT);
  pinMode(LEFT_IN2_PIN, OUTPUT);
  pinMode(RIGHT_IN3_PIN, OUTPUT);
  pinMode(RIGHT_IN4_PIN, OUTPUT);
  stopMotors();

  motorDirectionReady =
      validDigitalLevel(LEFT_FORWARD_IN1_LEVEL) &&
      validDigitalLevel(LEFT_FORWARD_IN2_LEVEL) &&
      validDigitalLevel(RIGHT_FORWARD_IN3_LEVEL) &&
      validDigitalLevel(RIGHT_FORWARD_IN4_LEVEL);

  if (!motorDirectionReady) {
    Serial.println("MOTOR SETUP REQUIRED: confirm forward HIGH/LOW levels on the physical robot.");
  }

  // Do not move the servo until its safe angles have been physically confirmed.
  if (SERVO_REST_ANGLE >= 0 && SERVO_REST_ANGLE <= 180 &&
      SERVO_FIRE_ANGLE >= 0 && SERVO_FIRE_ANGLE <= 180) {
    catapultServo.attach(SERVO_PIN, 660, 2400);
    catapultServo.write(SERVO_REST_ANGLE);
    servoReady = true;
  } else {
    Serial.println("SERVO SETUP REQUIRED: calibrate resting and firing angles first.");
  }
}

void loop() {
  float distanceCm = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  // Ultrasonic testing works now, but autonomous movement stays disabled
  // until the physical motor direction has been confirmed.
  if (!motorDirectionReady) {
    stopMotors();
    delay(200);
    return;
  }

  if (distanceCm < 0) {
    stopMotors();
  } else if (distanceCm >= STOP_DISTANCE_CM && !catapultFired) {
    moveForward();
  } else {
    stopMotors();

    // Firing remains disabled until the servo angles are calibrated.
    if (servoReady) {
      fireCatapultOnce();
    }
  }

  delay(50);
}
