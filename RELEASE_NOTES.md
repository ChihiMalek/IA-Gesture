# Release Notes

## 🚀 v1.0.0 — Initial Release (2026-08-01)

### Summary

**IA Gesture v1.0.0** is the first public release of an accessibility-focused
hand-gesture recognition system that bridges **computer vision**, **machine
learning**, **IoT messaging (MQTT)**, and **embedded systems (ESP32/ESP8266)**
into a single working pipeline: a webcam gesture is recognized on a PC and
translated into a message displayed on an OLED screen carried by the user,
with safety alerts via buzzer and ultrasonic sensing.

This release corresponds to the finalized graduation project delivered at
École Nationale d'Ingénieurs de Gabès (ENIG), Département Génie Électrique
et Automatique, 2025/2026.

### ✨ Features

- Real-time hand tracking with **MediaPipe Hands** (21 landmarks / hand).
- Gesture classification via a **scikit-learn** model on a 63-value feature
  vector, with confidence scoring (`predict_proba`).
- **Majority-vote temporal smoothing** across the last 5 predictions.
- **MQTT** publish/subscribe communication between the PC and the embedded
  board (`broker.emqx.io`, topics `assist/gesture` / `assist/object`).
- **ESP32/ESP8266 firmware** with OLED (SSD1306) display, buzzer alerts,
  and HC-SR04 ultrasonic distance sensing.
- Three embedded **operating modes**: *Non-Verbal*, *Aveugle* (visually
  impaired assistance), and *SOS*.
- **Dataset collection tool** for building custom gesture datasets.
- **Proteus circuit schematic** and enclosure design renders.
- Full **project report** (French) covering requirements analysis,
  platform comparison, and validation methodology.

### 🌟 Highlights

- End-to-end pipeline validated: webcam → landmarks → classification → MQTT
  → OLED/buzzer, confirmed via MQTT Explorer traces.
- Clear engineering trade-off analysis behind the hardware choice (PC camera
  + ESP32/ESP8266 selected over ESP32-CAM and Raspberry Pi + USB camera).
- Transparent development history: early prototypes (TensorFlow/Keras ASL
  CNN, finger-counting via convexity defects) preserved in `experiments/`.
- Professional open-source packaging: MIT license, contribution guidelines,
  Code of Conduct, security policy, citation metadata, issue/PR templates,
  and a CI workflow for dependency/import verification.

### ⚠️ Known Limitations

- Recognition accuracy is sensitive to **lighting conditions** and **fast
  hand motion**.
- The system currently **depends on a PC** for inference and on an active
  **internet connection** for the MQTT broker.
- The default MQTT broker (`broker.emqx.io`) is **public and
  unauthenticated** — not suitable for production/safety-critical use
  without hardening (see [`SECURITY.md`](SECURITY.md)).
- The trained model file (`modele_mots.pkl`) is **not included** in this
  release and must be supplied separately.
- No automated/quantitative accuracy or latency benchmarks are published in
  this release (planned for a future version — see
  [`CHANGELOG.md`](CHANGELOG.md)).

### 📦 Assets in This Release

- Source code (`src/`) and firmware (`firmware/gesture_assistant/`)
- Hardware design files (`hardware/`)
- Full project report (`docs/rapport_IA_Gesture.pdf`)
- Repository documentation (`README.md`, `docs/architecture.md`, `docs/DEMO.md`)

### 🔗 Links

- Full changelog: [`CHANGELOG.md`](CHANGELOG.md)
- Architecture overview: [`docs/architecture.md`](docs/architecture.md)
- Demo walkthrough: [`docs/DEMO.md`](docs/DEMO.md)
- LinkedIn demo post: https://www.linkedin.com/posts/ugcPost-7426374563237818370-LGAR/?utm_source=share&utm_medium=member_desktop&rcm=ACoAAEyPdjUBMWvfSD5oRdK4eutkuw1UHI3semA

---

*For older/upcoming changes, see [`CHANGELOG.md`](CHANGELOG.md).*
