// EG1311 Ultrasonic Sensor Test
// Team wiring: TRIG D9, ECHO D10

const int TRIG_PIN = 9;
const int ECHO_PIN = 10;
const float SOUND_SPEED_CM_PER_US = 0.0345;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long echoTimeUs = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (echoTimeUs == 0) {
    Serial.println("No echo");
  } else {
    float distanceCm = echoTimeUs * SOUND_SPEED_CM_PER_US / 2.0;

    Serial.print("Distance: ");
    Serial.print(distanceCm);
    Serial.println(" cm");
  }

  delay(100);
}
