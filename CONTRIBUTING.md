# Contributing to IA Gesture

Thank you for considering a contribution to **IA Gesture** — an accessibility-focused
computer vision + IoT project. This guide explains how to propose changes in a way
that's easy to review and keeps the project stable.

## 📋 Before You Start

- Check existing [Issues](../../issues) and [Pull Requests](../../pulls) to avoid duplicate work.
- For substantial changes (new features, architecture changes), please open an issue
  first to discuss the approach before investing significant time.
- This is an academic/portfolio project — the core recognition pipeline and firmware
  logic documented in `docs/rapport_IA_Gesture.pdf` should be treated as reference
  behavior. Please explain the *why* behind any behavioral change.

## 🍴 1. Fork the Repository

Click **Fork** on GitHub, then clone your fork locally:

```bash
git clone https://github.com/YOUR-USERNAME/IA-Gesture.git
cd IA-Gesture
```

## 🌿 2. Create a Branch

Use a descriptive branch name prefixed by the change type:

```bash
git checkout -b feat/add-dynamic-gesture-support
git checkout -b fix/mqtt-reconnect-loop
git checkout -b docs/improve-hardware-section
```

Common prefixes: `feat/`, `fix/`, `docs/`, `refactor/`, `test/`, `chore/`.

## 💻 3. Make Your Changes

- **Python (`src/`, `experiments/`)** — follow [PEP 8](https://peps.python.org/pep-0008/).
  Use clear variable names, keep functions focused, and add docstrings for new
  functions/classes.
- **Arduino / C++ (`firmware/`)** — match the existing style in
  `firmware/gesture_assistant/gesture_assistant.ino` (naming, indentation,
  comment style). Keep pin definitions and MQTT topic names consistent with the
  documented architecture (`docs/architecture.md`).
- **Documentation (`docs/`, `README.md`)** — use clear Markdown, keep tables
  aligned, and update the table of contents if you add a new section.
- Do not commit generated build artifacts, `__pycache__/`, trained model
  binaries, or IDE-specific files — check `.gitignore` first.

## ✅ 4. Commit Your Changes

Write clear, atomic commits using [Conventional Commits](https://www.conventionalcommits.org/) style where possible:

```bash
git add .
git commit -m "feat: add support for dynamic (motion-based) gestures"
```

Examples of good prefixes: `feat:`, `fix:`, `docs:`, `refactor:`, `test:`, `chore:`.

## 🔀 5. Push and Open a Pull Request

```bash
git push origin feat/add-dynamic-gesture-support
```

Then open a Pull Request against `main` using the
[Pull Request template](.github/PULL_REQUEST_TEMPLATE.md). In your PR description:

- Explain **what** changed and **why**.
- Reference any related issue (`Closes #12`).
- Include screenshots/GIFs for UI-visible or hardware-visible changes when possible.
- List how the change was tested (webcam test, MQTT trace, hardware bench test, etc.).

## 🎨 Coding Style Summary

| Area | Style |
|---|---|
| Python | PEP 8, snake_case, type hints encouraged for new code |
| Arduino/C++ | Match existing `firmware/` conventions, UPPER_CASE for `#define` pins/constants |
| Commit messages | Conventional Commits (`feat:`, `fix:`, `docs:`, ...) |
| Branch names | `type/short-description` |
| Markdown | ATX headers (`#`), tables aligned, one sentence per line for long prose is welcome but not required |

## 🧪 Testing Your Changes

- **Python:** run the relevant script manually (`python src/gesture_recognition/handgestures.py`) and confirm no import/runtime errors. The CI workflow (`.github/workflows/ci.yml`) will also verify dependency installation and basic import checks.
- **Firmware:** compile in the Arduino IDE for the target board (ESP32/ESP8266) before submitting.

## 🙋 Questions?

Open a [Question issue](.github/ISSUE_TEMPLATE/question.md) or start a
[Discussion](../../discussions) if enabled. We're happy to help you get started.

By contributing, you agree that your contributions will be licensed under the
project's [MIT License](LICENSE).
