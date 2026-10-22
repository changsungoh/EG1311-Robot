# EG1311 Robot

Arduino code and development notes for the EG1311 Design and Make robot project.

## Robot goal

The robot should operate autonomously after starting, travel through the obstacle course, approach the final wall, stop at a suitable distance, and use a servo-driven catapult mechanism to deliver the ping-pong ball over the wall.

## Branches

- `main` — final, tested code only
- `dev` — shared integration branch
- feature branches — temporary branches for changes before merging into `dev`

Do not develop directly on `main`.

## Confirmed wiring

| Component | Arduino pin(s) |
|---|---|
| HC-SR04 | TRIG D9, ECHO D10 |
| Left motor via L293D | D5, D6 |
| Right motor via L293D | D7, D8 |
| Servo signal | D3 |

The L293D enable pins are tied HIGH to 5V.

See `docs/WIRING.md` for the full wiring and calibration record.

## Current integrated behaviour

`robot.ino` now:

1. Reads the HC-SR04 distance continuously.
2. Drives both motors forward using the direction confirmed from physical testing.
3. Stops when the robot reaches the current stop threshold.
4. Stops safely if the ultrasonic sensor returns no echo.
5. Fires the catapult servo once.
6. Keeps the robot stopped after firing.

Current stop threshold:

```text
15 cm
```

This is a calibration starting point, not a guaranteed final value. Tune it on the real course because braking distance depends on wheel traction, sensor placement, robot speed, and ramp behaviour.

## Repository structure

```text
EG1311-Robot/
├── robot.ino
├── README.md
├── CONTRIBUTING.md
├── docs/
│   ├── WIRING.md
│   └── WORKFLOW.md
└── tests/
    ├── ultrasonic/ultrasonic.ino
    ├── motor/motor.ino
    ├── servo/servo.ino
    ├── sensor_motor/sensor_motor.ino
    └── catapult_sequence/catapult_sequence.ino
```

## Recommended test order

Before a full run:

1. Run `tests/motor/motor.ino` and confirm the robot moves forward.
2. Run `tests/ultrasonic/ultrasonic.ino` and verify stable distance readings.
3. Run `tests/sensor_motor/sensor_motor.ino` and calibrate the stop distance.
4. Run `tests/servo/servo.ino` and verify safe servo angles.
5. Run `tests/catapult_sequence/catapult_sequence.ino`.
6. Upload `robot.ino` and test the complete autonomous sequence.

## Arduino upload

Open the sketch, then:

```text
Select Arduino Uno -> Select COM port -> Verify -> Upload
```

After upload, the compiled program remains in the Arduino's flash memory. The laptop and Arduino IDE are not required during the actual autonomous run as long as the robot has the correct battery power.

## Final test priorities

- Confirm sensor is firmly attached and faces the wall.
- Confirm both motors move the robot in the intended direction.
- Calibrate the stop distance so the robot gets close without touching the wall.
- Verify the robot remains stable over the bump and ramp.
- Verify the catapult fires exactly once.
- Repeat the complete run several times before merging `dev` into `main`.

## Git workflow

Use a feature branch, then merge through `dev`:

```text
feature branch -> Pull Request -> dev
```

Only after the complete robot has passed physical testing:

```text
dev -> main
```
