# MQTT Communication

MQTT publishing is currently implemented **inline** inside
[`src/gesture_recognition/handgestures.py`](../gesture_recognition/handgestures.py)
using `paho.mqtt.publish`, and is **not** a separate module in the current
codebase. This folder is reserved for a future refactor that extracts the
MQTT publish/subscribe logic into a standalone module
(e.g. `mqtt_client.py`) without changing its behavior.

Broker used by the project: `broker.emqx.io` (topic: `assist/gesture`).
