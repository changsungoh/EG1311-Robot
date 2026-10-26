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

## Current calibration values

| Parameter | Current value |
|---|---:|
| Stop distance | 15 cm |
| Servo rest pulse | 660 us |
| Servo fire pulse | 2500 us |
| Settling delay before firing | 500 ms |
| Servo fire hold | 500 ms |
| Reverse time after firing | 3000 ms |

## Motor direction

Forward:

| Motor | First input | Second input |
|---|---:|---:|
| Left (D5/D6) | LOW | HIGH |
| Right (D7/D8) | LOW | HIGH |

Backward:

| Motor | First input | Second input |
|---|---:|---:|
| Left (D5/D6) | HIGH | LOW |
| Right (D7/D8) | HIGH | LOW |

Stop:

| Motor | First input | Second input |
|---|---:|---:|
| Left | LOW | LOW |
| Right | LOW | LOW |

## Autonomous sequence

1. Move forward.
2. Stop when the ultrasonic sensor reaches the stop threshold.
3. Fire the catapult.
4. Reverse for `BACKUP_TIME_MS`.
5. Stop permanently.

Adjust `BACKUP_TIME_MS` after measuring how far the robot needs to return on the real course.
