// EG1311 Sensor + Motor Integration Starter
// Based on the lecture-style ultrasonic + motor example.
// IMPORTANT: MOTOR_PIN = 2 is only a starter/reference value.
// Confirm the real L293D wiring before using this on the final robot.

const int MOTOR_PIN = 2;
const int TRIG_PIN = 13;
const int ECHO_PIN = 12;
const float SOUND_SPEED = 0.0345; // cm/microsecond
const float STOP_DISTANCE_CM = 30.0;

float readDistanceCm() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long microsecs = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (microsecs == 0) {
    return -1.0;
  }

  return microsecs * SOUND_SPEED / 2.0;
}

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  digitalWrite(TRIG_PIN, LOW);
  digitalWrite(MOTOR_PIN, LOW);

  Serial.begin(9600);
}

void loop() {
  float distanceCm = readDistanceCm();

  Serial.print("Distance: ");
  Serial.print(distanceCm);
  Serial.println(" cm");

  if (distanceCm < 0 || distanceCm < STOP_DISTANCE_CM) {
    digitalWrite(MOTOR_PIN, LOW);
  } else {
    digitalWrite(MOTOR_PIN, HIGH);
  }

  delay(100);
}
