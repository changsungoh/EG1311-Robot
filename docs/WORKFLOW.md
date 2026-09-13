# Team Workflow: GitHub Desktop + Arduino IDE

Use this process for every Issue.

## 1. Get the newest shared code

In GitHub Desktop:

1. Select `EG1311-Robot`.
2. Switch to the `dev` branch.
3. Click `Fetch origin`.
4. If a `Pull origin` button appears, click it.

Now the local folder contains the latest shared code.

## 2. Create a branch for the Issue

Create a branch from `dev` using the Issue number, for example:

```text
issue-1-ultrasonic
issue-2-motor
issue-3-servo
```

Do not reuse another Issue's branch.

## 3. Work in Arduino IDE

Open the relevant `.ino` sketch from the cloned repository folder.

For an isolated hardware test, use the matching file in `tests/` first. Only edit `robot.ino` when integrating tested parts.

Typical Arduino IDE flow:

```text
Open sketch -> Select Arduino Uno -> Select COM port -> Verify -> Upload -> Test hardware
```

## 4. Save and commit

After a useful working change:

1. Save in Arduino IDE.
2. Go to GitHub Desktop.
3. Review the changed files.
4. Write a short commit message.
5. Commit to the Issue branch.
6. Push origin.

## 5. Merge into dev

On GitHub, open a Pull Request:

```text
base: dev
compare: issue-N-name
```

Check that the code compiles and the hardware test passes before merging.

## 6. Teammate continues from the new dev

The teammate switches to `dev` in GitHub Desktop and pulls again. They now receive the merged code and can create the next Issue branch.

## Final release

Only after the complete robot has been tested successfully, open a Pull Request:

```text
base: main
compare: dev
```

This keeps `main` as the stable final version.

## Conflict prevention

- Pull `dev` before starting new work.
- Do not both edit the same lines of `robot.ino` at the same time unless necessary.
- Prefer separate test sketches while working on separate hardware components.
- Merge completed work into `dev` before the next dependent Issue starts.
