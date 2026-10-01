// EG1311 Issue #2 - Two Motor Control Test
// Based on current TinkerCAD wiring:
//
// Left motor:
// D5 -> L293D Input 1
// D6 -> L293D Input 2
//
// Right motor:
// D7 -> L293D Input 3
// D8 -> L293D Input 4
//
// IMPORTANT:
// Confirm actual motor directions on the physical robot.
// If one motor spins backwards, reverse HIGH/LOW for that motor.

const int LEFT_IN1_PIN = 5;
const int LEFT_IN2_PIN = 6;

const int RIGHT_IN1_PIN = 7;
const int RIGHT_IN2_PIN = 8;

// Keep as -1 if L293D enable pins are tied directly HIGH/5V.
// If enable pins are connected to Arduino pins,
// replace these with the actual Arduino pin numbers.
const int LEFT_ENABLE_PIN = -1;
const int RIGHT_ENABLE_PIN = -1;

bool leftEnableConfigured() {
  return LEFT_ENABLE_PIN >= 0;
}

bool rightEnableConfigured() {
  return RIGHT_ENABLE_PIN >= 0;
}

void enableMotorDrivers() {
  if (leftEnableConfigured()) {
    digitalWrite(LEFT_ENABLE_PIN, HIGH);
  }

  if (rightEnableConfigured()) {
    digitalWrite(RIGHT_ENABLE_PIN, HIGH);
  }
}

void moveForward() {
  // Left motor
  digitalWrite(LEFT_IN1_PIN, HIGH);
  digitalWrite(LEFT_IN2_PIN, LOW);

  // Right motor
  digitalWrite(RIGHT_IN1_PIN, HIGH);
  digitalWrite(RIGHT_IN2_PIN, LOW);
}

void stopMotors() {
  // Left motor
  digitalWrite(LEFT_IN1_PIN, LOW);
  digitalWrite(LEFT_IN2_PIN, LOW);

  // Right motor
  digitalWrite(RIGHT_IN1_PIN, LOW);
  digitalWrite(RIGHT_IN2_PIN, LOW);
}

void setup() {
  Serial.begin(9600);

  pinMode(LEFT_IN1_PIN, OUTPUT);
  pinMode(LEFT_IN2_PIN, OUTPUT);

  pinMode(RIGHT_IN1_PIN, OUTPUT);
  pinMode(RIGHT_IN2_PIN, OUTPUT);

  if (leftEnableConfigured()) {
    pinMode(LEFT_ENABLE_PIN, OUTPUT);
  }

  if (rightEnableConfigured()) {
    pinMode(RIGHT_ENABLE_PIN, OUTPUT);
  }

  enableMotorDrivers();
  stopMotors();

  Serial.println("Two-motor test ready.");
}

void loop() {
  Serial.println("Forward");
  moveForward();
  delay(2000);

  Serial.println("Stop");
  stopMotors();
  delay(2000);
}
