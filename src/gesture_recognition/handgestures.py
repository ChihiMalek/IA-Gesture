import cv2
import mediapipe as mp
import pickle
import numpy as np
import os
import time
import paho.mqtt.publish as publish

# ===== MQTT CONFIG =====
BROKER = "broker.emqx.io"      
TOPIC = "assist/gesture"

last_sent = ""
last_time = 0
SEND_INTERVAL = 1.0   

# ===== Vérification du modèle =====
MODEL_FILE = "modele_mots.pkl"
if not os.path.exists(MODEL_FILE):
    raise SystemExit("Le modèle n'existe pas.")

with open(MODEL_FILE, "rb") as f:
    model = pickle.load(f)

# ===== MediaPipe =====
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils

cap = cv2.VideoCapture(0)

pred_history = []
HISTORY_LENGTH = 5

with mp_hands.Hands(max_num_hands=1,
                    min_detection_confidence=0.7,
                    min_tracking_confidence=0.7) as hands:

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = hands.process(frame_rgb)
        frame = cv2.cvtColor(frame_rgb, cv2.COLOR_RGB2BGR)

        mot_pred = ""
        confidence = 0.0

        if results.multi_hand_landmarks:
            landmarks = results.multi_hand_landmarks[0]
            points = []

            for lm in landmarks.landmark:
                points.extend([lm.x, lm.y, lm.z])

            try:
                proba = model.predict_proba([points])[0]
                mot_pred = model.classes_[np.argmax(proba)]
                confidence = np.max(proba)
            except:
                pass

            # === Filtre temporel ===
            pred_history.append(mot_pred)
            if len(pred_history) > HISTORY_LENGTH:
                pred_history.pop(0)

            if pred_history:
                mot_pred = max(set(pred_history), key=pred_history.count)

            mp_drawing.draw_landmarks(frame, landmarks, mp_hands.HAND_CONNECTIONS)

        # ===== MQTT SEND =====
        current_time = time.time()
        if mot_pred != "" and mot_pred != last_sent:
            if current_time - last_time > SEND_INTERVAL:
                publish.single(TOPIC, mot_pred, hostname=BROKER, port=1883)
                print("📡 MQTT envoyé :", mot_pred)

                last_sent = mot_pred
                last_time = current_time

        # ===== Display =====
        cv2.putText(frame, f"Mot: {mot_pred}", (10, 50),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

        cv2.imshow("Reconnaissance + MQTT", frame)

        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

cap.release()
cv2.destroyAllWindows()