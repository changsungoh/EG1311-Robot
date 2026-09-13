# EG1311 Robot

Arduino code and development notes for the EG1311 Design and Make robot project.

## Robot goal

The robot should operate autonomously after starting, travel through the course, approach the final wall, stop at a suitable distance, and use a servo-driven catapult mechanism to deliver the ping-pong ball over the wall.

## Branches

- `main` — final, tested code only
- `dev` — shared integration branch
- `issue-N-name` — temporary branch for one GitHub Issue

Do not develop directly on `main`.

## Current Issues

1. Ultrasonic distance sensor
2. Motor control
3. Servo catapult control
4. Sensor + motor integration
5. Catapult firing integration
6. Final calibration and robot testing

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

## Development order

Test hardware separately before integrating it:

1. Run `tests/ultrasonic/ultrasonic.ino` and verify distance readings in Serial Monitor.
2. Run `tests/motor/motor.ino` after confirming the real L293D wiring.
3. Run `tests/servo/servo.ino` and determine safe resting/firing angles.
4. Run the integration tests.
5. Only then update and run `robot.ino` on the complete robot.

## Important safety / setup note

The actual motor-driver and servo pins have not yet been confirmed. `robot.ino` intentionally uses `-1` for those unknown pins so it does not accidentally drive unconfirmed hardware. Update `docs/WIRING.md` first when the real wiring is known.

## Arduino IDE

Open the `.ino` file inside its matching sketch folder. For example:

```text
tests/ultrasonic/ultrasonic.ino
```

Then select the Arduino Uno and the correct COM port, Verify, and Upload.

## Git workflow

For each Issue:

```text
dev
 ↓
issue-N-name
 ↓ code + test
commit + push
 ↓
Pull Request -> dev
```

After the complete robot is tested successfully:

```text
dev -> main
```

See `docs/WORKFLOW.md` for the beginner step-by-step workflow.
