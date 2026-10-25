// EG1311 Servo Test
// Team wiring: servo signal D3

#include <Servo.h>

Servo servo;

const int SERVO_PIN = 3;
const int REST_PULSE_US = 660;
const int FIRE_PULSE_US = 2500;

void setup() {
  servo.attach(SERVO_PIN, REST_PULSE_US, FIRE_PULSE_US);
  servo.writeMicroseconds(REST_PULSE_US);
  delay(1000);
}

void loop() {
  servo.writeMicroseconds(FIRE_PULSE_US);
  delay(1000);

  servo.writeMicroseconds(REST_PULSE_US);
  delay(1000);
}
