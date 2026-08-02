# Architecture

This document summarizes the system architecture described in detail in
[`rapport_IA_Gesture.pdf`](rapport_IA_Gesture.pdf) .

## Overview

![Software architecture](diagrams/architecture-logicielle.png)

The system is a hybrid PC + embedded architecture:

```
Camera (PC webcam)
      │  OpenCV (BGR → RGB)
      ▼
MediaPipe Hands  →  21 3D hand landmarks (63-value feature vector)
      ▼
ML classifier (scikit-learn, trained offline)  →  predicted gesture
      ▼
Temporal smoothing (majority vote over last 5 predictions)
      ▼
MQTT publish (topic: assist/gesture, broker: broker.emqx.io)
      ▼
ESP32 / ESP8266 (MQTT subscriber)
      ▼
OLED SSD1306 display  +  buzzer alert  +  HC-SR04 ultrasonic sensor
```

## Functional analysis

The functional needs were derived using standard requirements-engineering
tools:

| Diagram | Purpose | File |
|---|---|---|
| Bête à cornes | Who the system serves, what it acts on, and why | [`diagrams/bete-a-cornes.png`](diagrams/bete-a-cornes.png) |
| Diagramme pieuvre | Interactions between the system and its environment | [`diagrams/diagramme-pieuvre.png`](diagrams/diagramme-pieuvre.png) |
| Cas d'utilisation | End-to-end usage scenario | [`diagrams/cas-utilisation.png`](diagrams/cas-utilisation.png) |

## Software components

| Layer | Technology | Location in repo |
|---|---|---|
| Video capture & preprocessing | OpenCV | `src/gesture_recognition/handgestures.py` |
| Hand landmark extraction | MediaPipe Hands | `src/gesture_recognition/handgestures.py` |
| Gesture classification | scikit-learn model (`modele_mots.pkl`) | `src/models/` |
| Dataset collection | OpenCV | `src/training/collect_dataset.py` |
| Messaging | MQTT (`paho-mqtt`) | inline in `src/gesture_recognition/handgestures.py` — see `src/mqtt/README.md` |
| Embedded firmware | Arduino (ESP8266) | `firmware/gesture_assistant/gesture_assistant.ino` |
| Hardware schematic | Proteus | `hardware/proteus/gesture_assistant_schematic.pdsprj` |

## Hardware

| Component | Reference | Interface | Role |
|---|---|---|---|
| Microcontroller | ESP32 / ESP8266 | Wi-Fi / I²C | Processing, MQTT, sensor & actuator management |
| Display | OLED SSD1306 | I²C | Shows translated messages and alerts |
| Distance sensor | HC-SR04 (ultrasonic) | GPIO | Distance measurement / obstacle assistance |
| Buzzer | Active buzzer | GPIO | Audible danger/emergency alerts |

See `hardware/3d/` for enclosure renders and `hardware/proteus/` for the
circuit schematic.

## Alternatives considered

Two alternative platforms were evaluated before settling on the
PC-camera + ESP32/ESP8266 architecture (see report §2 for the full
comparison and trade-offs):

- **ESP32-CAM** — rejected due to flashing/upload instability, limited
  processing power, and insufficient image quality.
- **Raspberry Pi + USB camera** — rejected due to higher cost, power
  consumption, and setup complexity.
