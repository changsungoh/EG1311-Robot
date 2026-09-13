// EG1311 Robot - Integration Skeleton
// Branch policy: feature branch -> dev -> main
//
// IMPORTANT:
// - This is a SAFE STARTER, not the final wiring.
// - Confirm the team's real L293D and servo wiring before enabling motor/servo control.
// - Ultrasonic defaults below follow the L3C lecture example: TRIG 13, ECHO 12.

#include <Servo.h>

// ---------- Known lecture-example values ----------
const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const float SOUND_SPEED_CM_PER_US = 0.0345;

// ---------- Must be confirmed from the real robot ----------
const int MOTOR_IN1_PIN = -1;   // TODO: replace after L293D wiring is confirmed
const int MOTOR_IN2_PIN = -1;   // TODO: replace after L293D wiring is confirmed
const int SERVO_PIN = -1;       // TODO: replace after servo wiring is confirmed

const float STOP_DISTANCE_CM = 30.0; // TODO: calibrate on the real course
const int SERVO_REST_ANGLE = 0;      // TODO: calibrate
const int SERVO_FIRE_ANGLE = 90;     // TODO: calibrate

Servo catapultServo;
bool catapultFired = false;
bool hardwareReady = false;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long microseconds = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (microseconds == 0) {
    return -1.0; // no echo / timeout
  }

  return microseconds * SOUND_SPEED_CM_PER_US / 2.0;
}

void moveForward() {
  // TODO: Confirm the exact L293D truth table for the team's wiring.
  // Do not guess this on the physical robot.
  digitalWrite(MOTOR_IN1_PIN, HIGH);
  digitalWrite(MOTOR_IN2_PIN, LOW);
}

void stopMotors() {
  digitalWrite(MOTOR_IN1_PIN, LOW);
  digitalWrite(MOTOR_IN2_PIN, LOW);
}

void fireCatapultOnce() {
  if (catapultFired) {
    return;
  }

  stopMotors();
  delay(500);
  catapultServo.write(SERVO_FIRE_ANGLE);
  delay(500);
  catapultServo.write(SERVO_REST_ANGLE);
  catapultFired = true;
}

void setup() {
  Serial.begin(9600);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  // Negative pins intentionally keep the starter code from driving
  // unconfirmed hardware. Replace them only after wiring is known.
  if (MOTOR_IN1_PIN < 0 || MOTOR_IN2_PIN < 0 || SERVO_PIN < 0) {
    Serial.println("SETUP REQUIRED: confirm motor and servo pin assignments first.");
    hardwareReady = false;
    return;
  }

  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);
  stopMotors();

  catapultServo.attach(SERVO_PIN, 660, 2400);
  catapultServo.write(SERVO_REST_ANGLE);

  hardwareReady = true;
}

void loop() {
  if (!hardwareReady) {
    delay(1000);
    return;
  }

  float distanceCm = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  if (distanceCm < 0) {
    stopMotors();
  } else if (distanceCm >= STOP_DISTANCE_CM && !catapultFired) {
    moveForward();
  } else {
    fireCatapultOnce();
  }

  delay(50);
}
