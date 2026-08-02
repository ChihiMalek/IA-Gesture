# 🎬 Demo Walkthrough

This page describes the video demo referenced from the main
[`README.md`](../README.md#-demo) in more detail, so viewers know exactly
what to expect before watching.

## 📹 Video Demo

| | |
|---|---|
| File | `assets/demo.mp4` *(not yet added — coming in a future update)* |
| LinkedIn post | https://www.linkedin.com/posts/ugcPost-7426374563237818370-LGAR/?utm_source=share&utm_medium=member_desktop&rcm=ACoAAEyPdjUBMWvfSD5oRdK4eutkuw1UHI3semA |
| Length (placeholder) | *add duration once the final cut is exported, e.g. "1:45"* |

> Until `assets/demo.mp4` is added to the repository, watch the LinkedIn
> post above for a version of the demo with narration/captions.

## 👀 What You Will See in the Demo

The demo is structured to show the **full pipeline end-to-end**, from hand
gesture to embedded feedback:

1. **Setup shot** — the PC webcam, the ESP8266/ESP32 board with the OLED
   screen, buzzer, and HC-SR04 ultrasonic sensor wired on the breadboard
   (matches `assets/screenshots/hardware-montage.png`).
2. **Live gesture capture** — a hand performing a predefined sign (e.g.
   *Hello*, *Yes*, *No*, *Thanks*, *Help*) in front of the webcam, with
   MediaPipe's 21 hand landmarks drawn live over the video feed.
3. **Real-time classification** — the recognized gesture label appears as an
   on-screen overlay (as captured in
   `assets/screenshots/gesture-detection-demo.png`), including the
   temporal-smoothing effect (the label stabilizes after a few frames
   rather than flickering between predictions).
4. **MQTT message in transit** — a side-by-side view of
   [MQTT Explorer](https://mqtt-explorer.com/) showing the message being
   published on the `assist/gesture` topic and received in near real time
   (see `assets/screenshots/mqtt-explorer-topics.png` and
   `assets/screenshots/mqtt-explorer-messages.png`).
5. **Embedded feedback** — the OLED screen on the ESP32/ESP8266 updating
   with the translated message, followed by a **buzzer alert** demo when a
   danger/SOS gesture or a close-proximity ultrasonic reading is triggered.
6. **Mode switching** — a brief demonstration of the different embedded
   operating modes: *Non-Verbal*, *Aveugle* (visually-impaired assistance),
   and *SOS*.

## 🖼️ Supporting Screenshots

These stills are included directly in the repository (extracted from the
project report) and complement the video:

| Screenshot | Shows |
|---|---|
| `assets/screenshots/gesture-detection-demo.png` | Live gesture recognition overlay on the PC video feed |
| `assets/screenshots/hardware-montage.png` | Physical hardware setup (breadboard, sensors, OLED) |
| `assets/screenshots/mqtt-explorer-topics.png` | MQTT topic tree during a live session |
| `assets/screenshots/mqtt-explorer-messages.png` | MQTT message payloads exchanged between PC and board |

## 🔁 Reproducing the Demo Yourself

```bash
pip install -r requirements.txt
cd src/gesture_recognition
python handgestures.py
```

Then flash `firmware/gesture_assistant/gesture_assistant.ino` to your board
(see [`README.md → Installation`](../README.md#️-installation)) and watch
the OLED update as you perform gestures in front of the webcam.
