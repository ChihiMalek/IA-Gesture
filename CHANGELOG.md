# Changelog

All notable changes to **IA Gesture** are documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Planned
- Smartphone camera integration (remove PC dependency)
- Dynamic (motion-based) gesture support
- Cloud-based inference option
- GPS module for user safety tracking
- Dedicated custom PCB (replacing breadboard prototype)
- Standalone `src/mqtt/` and `src/utils/` modules (refactor, no behavior change)
- Quantitative benchmarking (accuracy, latency) and CI test coverage

See [`README.md → Future Improvements`](README.md#-future-improvements) and
[`docs/rapport_IA_Gesture.pdf`](docs/rapport_IA_Gesture.pdf) (Chapter 6) for
full details.

---

## [1.0.0] — 2026-08-01

### Summary
Initial public release of IA Gesture — a real-time hand-gesture recognition
system with an MQTT-connected embedded assistant, built as a graduation
project at ENIG.

### Added
- **Computer vision pipeline**: real-time hand landmark extraction using
  MediaPipe Hands (`src/gesture_recognition/handgestures.py`).
- **Gesture classification**: scikit-learn model inference on a 63-value
  landmark feature vector, with `predict_proba` confidence scoring.
- **Temporal smoothing**: majority-vote filtering over the last 5
  predictions to reduce single-frame jitter.
- **MQTT communication layer**: PC-side publisher and ESP32/ESP8266
  subscriber over `broker.emqx.io` (topics `assist/gesture`,
  `assist/object`).
- **Embedded firmware** (`firmware/gesture_assistant/gesture_assistant.ino`):
  OLED (SSD1306) message display, buzzer alerts, HC-SR04 ultrasonic
  distance sensing, and multiple operating modes (*Non-Verbal*, *Aveugle*,
  *SOS*).
- **Dataset collection tool** (`src/training/collect_dataset.py`) for
  building labeled gesture datasets from webcam captures.
- **Hardware design assets**: Proteus circuit schematic
  (`hardware/proteus/`) and enclosure design renders (`hardware/3d/`).
- **Functional analysis documentation**: bête à cornes, diagramme pieuvre,
  and use-case diagrams (`docs/diagrams/`).
- **Full project report** (`docs/rapport_IA_Gesture.pdf`) covering
  requirements analysis, technology comparison, software/hardware
  realization, validation, and future perspectives.
- **Exploratory prototypes** preserved for transparency
  (`experiments/prototypes/`): a TensorFlow/Keras ASL-alphabet CNN
  approach and a convexity-defects finger-counting approach.
- Professional open-source repository scaffolding: `README.md`,
  `LICENSE` (MIT), `CONTRIBUTING.md`, `CODE_OF_CONDUCT.md`,
  `SECURITY.md`, `CITATION.cff`, GitHub issue/PR templates, and a CI
  workflow.

### Known Limitations
- Recognition accuracy is sensitive to lighting conditions and fast hand
  motion (see report §4.11).
- The system depends on a PC for inference and an active internet
  connection for the MQTT broker.
- The default MQTT broker (`broker.emqx.io`) is public and
  unauthenticated — see [`SECURITY.md`](SECURITY.md) before any
  production use.
- The trained model file (`modele_mots.pkl`) is not bundled in this
  repository and must be supplied separately (see
  `src/models/README.md`).
- No automated accuracy/latency benchmarks are published yet (planned —
  see Unreleased section above).

[Unreleased]: https://github.com/YOUR-USERNAME/IA-Gesture/compare/v1.0.0...HEAD
[1.0.0]: https://github.com/YOUR-USERNAME/IA-Gesture/releases/tag/v1.0.0
