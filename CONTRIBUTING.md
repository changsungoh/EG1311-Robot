# Contributing

This repository uses a simple team workflow so two people can work without overwriting each other.

## Rules

1. Do not code directly on `main`.
2. Start work from the latest `dev` branch.
3. Use one feature branch per Issue, for example `issue-1-ultrasonic`.
4. Commit small, understandable changes.
5. Push the feature branch and open a Pull Request into `dev`.
6. Test on the physical Arduino/robot before merging hardware-related changes.
7. Merge `dev` into `main` only when the full robot behavior has been tested.

## Suggested commit messages

```text
Test ultrasonic distance readings
Add motor forward and stop control
Calibrate servo firing angle
Integrate wall detection with motor stop
Fix repeated catapult firing
```

## Before merging a Pull Request

- Code compiles in Arduino IDE.
- Pin assignments match the actual wiring.
- The relevant hardware test was performed.
- No unrelated changes are included.
- Any new wiring or calibration value is recorded in `docs/WIRING.md`.
