// EG1311 Servo Test
// Team wiring: servo signal D3

#include <Servo.h>

Servo servo;

const int SERVO_PIN = 3;
const int REST_ANGLE = 0;
const int FIRE_ANGLE = 180;

void setup() {
  servo.attach(SERVO_PIN, 660, 2400);
  servo.write(REST_ANGLE);
  delay(1000);
}

void loop() {
  servo.write(FIRE_ANGLE);
  delay(1000);

  servo.write(REST_ANGLE);
  delay(1000);
}
