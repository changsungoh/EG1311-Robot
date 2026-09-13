// EG1311 Catapult Sequence Starter
// Test the servo mechanism independently before integrating it with motor control.
// Change SERVO_PIN and the two angles to match the real robot.

#include <Servo.h>

Servo catapult;

const int SERVO_PIN = 2;
const int REST_ANGLE = 0;
const int FIRE_ANGLE = 90;

bool fired = false;

void setup() {
  catapult.attach(SERVO_PIN, 660, 2400);
  catapult.write(REST_ANGLE);
  delay(1000);
}

void loop() {
  if (!fired) {
    delay(500);
    catapult.write(FIRE_ANGLE);
    delay(500);
    catapult.write(REST_ANGLE);
    fired = true;
  }
}
