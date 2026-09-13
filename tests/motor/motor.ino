// EG1311 Basic Motor Output Test
// This is only a starter test based on the simple lecture-style motor control.
// IMPORTANT: The final motor code depends on the team's actual L293D wiring.
// Replace MOTOR_PIN and control logic after confirming the real circuit.

const int MOTOR_PIN = 2;

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
}

void loop() {
  // Motor/control output ON
  digitalWrite(MOTOR_PIN, HIGH);
  delay(2000);

  // Motor/control output OFF
  digitalWrite(MOTOR_PIN, LOW);
  delay(2000);
}
