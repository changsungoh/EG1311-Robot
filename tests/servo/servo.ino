// EG1311 Servo Test
// Based on the L3D PWM/Servo lecture example.
// Servo pin can be any suitable digital pin; change SERVO_PIN to match wiring.
// While using the Servo library, avoid relying on PWM output on pins 9 and 10.

#include <Servo.h>

Servo servo;
const int SERVO_PIN = 2;

void setup() {
  servo.attach(SERVO_PIN, 660, 2400);
}

void loop() {
  for (int angle = 0; angle <= 180; angle++) {
    servo.write(angle);
    delay(5);
  }

  for (int angle = 180; angle >= 0; angle--) {
    servo.write(angle);
    delay(5);
  }
}
