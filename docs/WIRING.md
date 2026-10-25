# Wiring and Calibration Record

This file records the team's current physical wiring and the values used by the Arduino code.

## Team's actual wiring

| Function | Arduino pin | Confirmed? | Notes |
|---|---:|---|---|
| HC-SR04 TRIG | D9 | Yes | Team TinkerCAD / wiring |
| HC-SR04 ECHO | D10 | Yes | Team TinkerCAD / wiring |
| Left motor IN1 | D5 | Yes | L293D pin 2 |
| Left motor IN2 | D6 | Yes | L293D pin 7 |
| Right motor IN3 | D7 | Yes | L293D pin 10 |
| Right motor IN4 | D8 | Yes | L293D pin 15 |
| Servo signal | D3 | Yes | Catapult servo |
| L293D 1,2EN | 5V | Yes | Enable tied HIGH |
| L293D 3,4EN | 5V | Yes | Enable tied HIGH |

All Arduino/L293D/battery grounds must share a common ground.

## Power

- Arduino logic can be powered by USB during programming/testing.
- The DC motors need their motor battery supply connected to the L293D motor-power input.
- Do not rely on the Arduino 5V pin to power the DC motors.

## Current calibration values

| Parameter | Current value | Status |
|---|---:|---|
| Stop distance | 15 cm | Starting value for closer wall approach; tune on course |
| Servo rest pulse | 660 us | Current rest command |
| Servo fire pulse | 2500 us | Extended beyond the previous 2400 us maximum |
| Settling delay before firing | 500 ms | Tune if needed |
| Servo fire hold | 500 ms | Tune if needed |

The catapult now uses `Servo.writeMicroseconds()` instead of `Servo.write(angle)`.
This allows direct pulse-width calibration beyond the previous 180-degree command mapping.

Do not keep increasing the pulse if the servo hits a mechanical stop, stalls, buzzes continuously, or becomes hot.

## Motor direction

Latest physical test showed that LOW/HIGH drives the robot backwards.

Current forward command:

| Motor | First input | Second input |
|---|---:|---:|
| Left (D5/D6) | HIGH | LOW |
| Right (D7/D8) | HIGH | LOW |

Current stop command:

| Motor | First input | Second input |
|---|---:|---:|
| Left | LOW | LOW |
| Right | LOW | LOW |

If the robot spins instead of moving straight, test each side independently and reverse only the motor that is physically backwards.

## Final-course calibration checklist

Before the graded run:

1. Verify both wheels drive the robot forward.
2. Attach the ultrasonic sensor rigidly and point it at the final wall.
3. Test the stopping threshold at 20 cm, 15 cm, and 10 cm if necessary.
4. Keep the largest threshold that stops reliably without touching the wall.
5. Test the servo at 2500 us.
6. If more travel is still needed, increase the pulse only in small steps and stop immediately if the servo reaches its mechanical limit or stalls.
7. Power-cycle the Arduino and run the full sequence several times.
