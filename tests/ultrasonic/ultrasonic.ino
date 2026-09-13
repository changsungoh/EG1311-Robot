// EG1311 Ultrasonic Sensor Test
// Based on the L3C Driver/Sensor lecture example.
// Default lecture wiring: TRIG = 13, ECHO = 12.
// Change these pins if the team's actual wiring is different.

const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const float SOUND_SPEED = 0.0345; // cm/microsecond

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long microsecs = pulseIn(ECHO_PIN, HIGH);
  float distanceCm = microsecs * SOUND_SPEED / 2.0;

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  delay(100);
}
