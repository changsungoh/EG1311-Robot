// EG1311 Issue #4: Ultrasonic + Motor Integration
// This branch prepares the integration logic without guessing the team's final wiring.
// Replace all -1 motor placeholders after the TinkerCAD/breadboard pin map is confirmed.
// Lecture/default HC-SR04 pins are TRIG=13 and ECHO=12; update them if the team uses different pins.

const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const float SOUND_SPEED_CM_PER_US = 0.0345;
const float STOP_DISTANCE_CM = 30.0; // tune during Issue #6

// L293D placeholders. Fill these in from the team's actual wiring.
const int LEFT_IN1_PIN = -1;
const int LEFT_IN2_PIN = -1;
const int LEFT_ENABLE_PIN = -1;   // keep -1 if enable is tied HIGH externally
const int RIGHT_IN1_PIN = -1;
const int RIGHT_IN2_PIN = -1;
const int RIGHT_ENABLE_PIN = -1;  // keep -1 if enable is tied HIGH externally

bool motorPinsConfigured() {
  return LEFT_IN1_PIN >= 0 && LEFT_IN2_PIN >= 0 &&
         RIGHT_IN1_PIN >= 0 && RIGHT_IN2_PIN >= 0;
}

void enableMotors() {
  if (LEFT_ENABLE_PIN >= 0) digitalWrite(LEFT_ENABLE_PIN, HIGH);
  if (RIGHT_ENABLE_PIN >= 0) digitalWrite(RIGHT_ENABLE_PIN, HIGH);
}

void stopMotors() {
  if (!motorPinsConfigured()) return;

  // Default coast/stop command. Confirm final stop/brake behavior on the real L293D wiring.
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, LOW);
  digitalWrite(RIGHT_IN1_PIN, LOW);
  digitalWrite(RIGHT_IN2_PIN, LOW);
}

void moveForward() {
  if (!motorPinsConfigured()) return;

  enableMotors();

  // These states are placeholders for the common case only.
  // If either wheel turns backward, swap that motor's HIGH/LOW states after hardware testing.
  digitalWrite(LEFT_IN1_PIN, HIGH);
  digitalWrite(LEFT_IN2_PIN, LOW);
  digitalWrite(RIGHT_IN1_PIN, HIGH);
  digitalWrite(RIGHT_IN2_PIN, LOW);
}

float readDistanceCm() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long durationUs = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (durationUs == 0) return -1.0;

  return durationUs * SOUND_SPEED_CM_PER_US / 2.0;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  if (motorPinsConfigured()) {
    pinMode(LEFT_IN1_PIN, OUTPUT);
    pinMode(LEFT_IN2_PIN, OUTPUT);
    pinMode(RIGHT_IN1_PIN, OUTPUT);
    pinMode(RIGHT_IN2_PIN, OUTPUT);

    if (LEFT_ENABLE_PIN >= 0) pinMode(LEFT_ENABLE_PIN, OUTPUT);
    if (RIGHT_ENABLE_PIN >= 0) pinMode(RIGHT_ENABLE_PIN, OUTPUT);

    stopMotors();
  }

  Serial.begin(9600);
  Serial.println("Issue #4 sensor + motor integration test started.");

  if (!motorPinsConfigured()) {
    Serial.println("Motor pins are not configured yet. Waiting for TinkerCAD/breadboard wiring.");
  }
}

void loop() {
  float distanceCm = readDistanceCm();

  Serial.print("Distance: ");
  if (distanceCm < 0) {
    Serial.println("no echo");
    stopMotors();
  } else {
    Serial.print(distanceCm);
    Serial.println(" cm");

    if (distanceCm > STOP_DISTANCE_CM) {
      moveForward();
      Serial.println("Command: FORWARD");
    } else {
      stopMotors();
      Serial.println("Command: STOP");
    }
  }

  delay(100);
}
