// EG1311 Catapult Sequence Test
// Team wiring: servo signal D3

#include <Servo.h>

Servo catapult;

const int SERVO_PIN = 3;
const int REST_PULSE_US = 660;
const int FIRE_PULSE_US = 2500;

bool fired = false;

void setup() {
  catapult.attach(SERVO_PIN, REST_PULSE_US, FIRE_PULSE_US);
  catapult.writeMicroseconds(REST_PULSE_US);
  delay(1000);
}

void loop() {
  if (!fired) {
    delay(500);
    catapult.writeMicroseconds(FIRE_PULSE_US);
    delay(500);
    catapult.writeMicroseconds(REST_PULSE_US);
    fired = true;
  }
}
