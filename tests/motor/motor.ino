// EG1311 Issue #2 - Motor Control Test
// Purpose: prepare a safe L293D motor-control test before the team's final
// TinkerCAD/breadboard pin mapping is confirmed.
//
// IMPORTANT:
// 1. Replace the -1 placeholders below with the actual Arduino pins from the
//    team's wiring/TinkerCAD before uploading this sketch.
// 2. Confirm which HIGH/LOW combination makes the physical motor move forward.
// 3. Do not assume the direction until it has been tested on the real robot.

const int MOTOR_IN1_PIN = -1;
const int MOTOR_IN2_PIN = -1;
const int MOTOR_ENABLE_PIN = -1; // use -1 if L293D enable is tied directly HIGH

bool motorPinsConfigured() {
  return MOTOR_IN1_PIN >= 0 && MOTOR_IN2_PIN >= 0;
}

bool enablePinConfigured() {
  return MOTOR_ENABLE_PIN >= 0;
}

void enableMotorDriver() {
  if (enablePinConfigured()) {
    digitalWrite(MOTOR_ENABLE_PIN, HIGH);
  }
}

void moveForward() {
  if (!motorPinsConfigured()) return;

  // TODO: Verify these states with the team's actual L293D wiring.
  digitalWrite(MOTOR_IN1_PIN, HIGH);
  digitalWrite(MOTOR_IN2_PIN, LOW);
}

void stopMotor() {
  if (!motorPinsConfigured()) return;

  // Coast/stop starter state. Confirm preferred stop behaviour on hardware.
  digitalWrite(MOTOR_IN1_PIN, LOW);
  digitalWrite(MOTOR_IN2_PIN, LOW);
}

void setup() {
  Serial.begin(9600);

  if (!motorPinsConfigured()) {
    Serial.println("Motor pins are not configured yet.");
    Serial.println("Update MOTOR_IN1_PIN and MOTOR_IN2_PIN from TinkerCAD/wiring first.");
    return;
  }

  pinMode(MOTOR_IN1_PIN, OUTPUT);
  pinMode(MOTOR_IN2_PIN, OUTPUT);

  if (enablePinConfigured()) {
    pinMode(MOTOR_ENABLE_PIN, OUTPUT);
  }

  enableMotorDriver();
  stopMotor();

  Serial.println("Motor test ready.");
}

void loop() {
  if (!motorPinsConfigured()) {
    delay(1000);
    return;
  }

  Serial.println("Forward");
  moveForward();
  delay(2000);

  Serial.println("Stop");
  stopMotor();
  delay(2000);
}
