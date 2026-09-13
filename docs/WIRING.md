# Wiring and Calibration Record

Update this file whenever the physical wiring changes. Do not guess final pin assignments in `robot.ino`.

## Lecture example values

These are reference values from the EG1311 lecture examples, not necessarily the team's final wiring.

| Component | Reference value |
|---|---|
| HC-SR04 TRIG | Digital pin 13 |
| HC-SR04 ECHO | Digital pin 12 |
| Serial baud rate | 9600 |
| Sound speed constant | 0.0345 cm/us |
| Servo pulse range used in lecture | 660 to 2400 us |

## Team's actual wiring

Fill these in after checking the breadboard and Arduino physically.

| Function | Arduino pin | Confirmed? | Notes |
|---|---:|---|---|
| Ultrasonic TRIG | 13 | No | Currently using lecture example |
| Ultrasonic ECHO | 12 | No | Currently using lecture example |
| L293D motor IN1 | TBD | No | Must be checked |
| L293D motor IN2 | TBD | No | Must be checked |
| L293D enable / PWM | TBD | No | If used |
| Servo signal | TBD | No | Must be checked |

## Calibration values

| Parameter | Current value | Confirmed? |
|---|---:|---|
| Stop distance | 30 cm starter value | No |
| Servo rest angle | 0 degrees starter value | No |
| Servo fire angle | 90 degrees starter value | No |
| Settling delay before firing | 500 ms starter value | No |

## Motor direction test

After wiring is confirmed, record what each L293D input combination actually does on the robot.

| IN1 | IN2 | Observed result |
|---:|---:|---|
| LOW | LOW | TBD |
| HIGH | LOW | TBD |
| LOW | HIGH | TBD |
| HIGH | HIGH | TBD |

This table matters because the exact physical behavior depends on how the motor and driver are wired.
