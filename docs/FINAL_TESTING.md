# Final Calibration and Robot Testing (Issue #6)

This checklist is for the final hardware stage after Issues #1-#5 are integrated into `dev` and the physical robot is assembled.

## Preconditions

- [ ] Latest `dev` contains the tested ultrasonic, motor and catapult code
- [ ] TinkerCAD/breadboard pin mapping matches the real robot
- [ ] Motor direction has been verified on the actual L293D wiring
- [ ] Servo rest/fire positions have been mechanically verified
- [ ] Wheels, chassis, batteries, ultrasonic sensor and catapult are fully mounted

## 1. Motor and direction check

- [ ] Lift the driven wheels off the table for the first test
- [ ] Confirm both wheels rotate in the direction required for forward movement
- [ ] Confirm the stop command stops both motors reliably
- [ ] If a wheel runs backward, correct only that motor's direction states in code

## 2. Ultrasonic check

- [ ] Open Serial Monitor at 9600 baud
- [ ] Check that the measured distance changes when an obstacle is moved
- [ ] Check for unstable/no-echo readings at the intended approach distance
- [ ] Record the approximate distance at which the robot should stop

## 3. Stop-distance calibration

Start conservatively and adjust only after repeated tests.

- [ ] Run the robot toward the wall at low-risk distance
- [ ] Record the actual stopping position
- [ ] Adjust `STOP_DISTANCE_CM` if required
- [ ] Repeat at least 3 times
- [ ] Choose a threshold that stops consistently without touching the wall

Final value:

`STOP_DISTANCE_CM = ______ cm`

## 4. Servo/catapult calibration

- [ ] Confirm the servo starts at the safe resting position
- [ ] Confirm the firing movement triggers the catapult
- [ ] Confirm the servo does not repeatedly fire in `loop()`
- [ ] Adjust rest/fire angles only in small increments
- [ ] Check whether the mechanism needs a return movement after firing

Final values:

- Rest angle: `______ deg`
- Fire angle: `______ deg`
- Settling delay before firing: `______ ms`
- Return angle/delay if used: `______`

## 5. Full autonomous sequence

Expected sequence:

1. Robot starts autonomously
2. Robot moves forward
3. HC-SR04 continuously measures distance
4. Robot stops near the target wall distance
5. Robot waits for the selected settling delay
6. Catapult fires exactly once
7. Robot remains in the intended final state

Run log:

| Run | Reached wall correctly | Stopped safely | Fired once | Ball delivered | Notes |
| --- | --- | --- | --- | --- | --- |
| 1 | | | | | |
| 2 | | | | | |
| 3 | | | | | |
| 4 | | | | | |
| 5 | | | | | |

## 6. Mechanical/repeatability checks

- [ ] Wheels have enough traction
- [ ] Robot tracks straight enough for the course
- [ ] Batteries and breadboard do not move during a run
- [ ] Ultrasonic sensor remains pointed in the intended direction
- [ ] Catapult structure does not cause the robot to tip
- [ ] Wiring cannot enter the wheels or moving catapult mechanism

## 7. Ready for `main`

Only mark Issue #6 complete when:

- [ ] Issues #1-#5 are merged into `dev`
- [ ] Final real pin assignments are recorded in `docs/WIRING.md`
- [ ] Final calibration values are saved in code
- [ ] The complete robot sequence succeeds repeatedly on hardware
- [ ] No temporary/debug-only wiring assumptions remain
- [ ] `dev` is stable enough for the final `dev -> main` pull request

Do not merge to `main` based only on compilation or simulation. Issue #6 requires physical robot testing.
