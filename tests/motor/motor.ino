// EG1311 Dual Motor Test
// Team wiring:
// Left motor  -> Arduino D5/D6 via L293D
// Right motor -> Arduino D7/D8 via L293D
//
// The robot was observed moving backwards with HIGH/LOW,
// so this test uses the reversed LOW/HIGH pair for forward.

const int LEFT_IN1_PIN = 5;
const int LEFT_IN2_PIN = 6;
const int RIGHT_IN3_PIN = 7;
const int RIGHT_IN4_PIN = 8;

void moveForward() {
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

void setup() {
  pinMode(LEFT_IN1_PIN, OUTPUT);
  pinMode(LEFT_IN2_PIN, OUTPUT);
  pinMode(RIGHT_IN3_PIN, OUTPUT);
  pinMode(RIGHT_IN4_PIN, OUTPUT);

  stopMotors();
}

void loop() {
  moveForward();
  delay(2000);

  stopMotors();
  delay(2000);
}
