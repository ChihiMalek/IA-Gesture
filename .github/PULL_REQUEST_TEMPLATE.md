## Description

<!-- Summarize what this PR changes and why. -->

Closes #<issue-number> <!-- if applicable -->

## Type of Change

- [ ] 🐛 Bug fix (non-breaking change that fixes an issue)
- [ ] ✨ New feature (non-breaking change that adds functionality)
- [ ] 💥 Breaking change (fix or feature that would change existing behavior)
- [ ] 📚 Documentation update
- [ ] 🧹 Refactor / code cleanup (no functional change)
- [ ] 🔧 CI / tooling change

## Component(s) Affected

- [ ] Python — gesture recognition (`src/gesture_recognition/`)
- [ ] Python — training / dataset (`src/training/`, `src/models/`)
- [ ] MQTT (`src/mqtt/`)
- [ ] Firmware (`firmware/`)
- [ ] Hardware design (`hardware/`)
- [ ] Documentation (`README.md`, `docs/`)
- [ ] Repository / DevOps (`.github/`, CI, templates)

## How Has This Been Tested?

<!-- Describe the tests you ran and how to reproduce them. -->

- [ ] Ran `src/gesture_recognition/handgestures.py` locally with a webcam
- [ ] Verified MQTT messages with MQTT Explorer / broker logs
- [ ] Compiled and flashed firmware to target board (ESP32/ESP8266)
- [ ] Verified on hardware bench (OLED, buzzer, ultrasonic sensor)
- [ ] N/A (documentation-only change)

## Screenshots / Recordings (if applicable)

<!-- Add before/after screenshots, MQTT traces, or a short video. -->

## Checklist

- [ ] My code follows the style guide described in [`CONTRIBUTING.md`](../CONTRIBUTING.md)
- [ ] I have not committed build artifacts, credentials, or files covered by `.gitignore`
- [ ] I have updated relevant documentation (`README.md`, `docs/architecture.md`, `CHANGELOG.md`)
- [ ] I have not modified the core recognition algorithm or firmware logic without prior discussion (see project scope in `README.md`)
- [ ] My changes generate no new warnings/errors

## Additional Notes

<!-- Anything else reviewers should know. -->
