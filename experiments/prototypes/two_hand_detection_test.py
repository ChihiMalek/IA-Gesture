import cv2
import mediapipe as mp

# === Initialisation de MediaPipe ===
mp_hands = mp.solutions.hands
mp_drawing = mp.solutions.drawing_utils
mp_drawing_styles = mp.solutions.drawing_styles  # pour des couleurs standard

# === Ouvre la caméra ===
cap = cv2.VideoCapture(0)  # 0 = webcam intégrée

# === Initialisation du détecteur de mains ===
with mp_hands.Hands(
    max_num_hands=2,               # ✅ détecter deux mains
    min_detection_confidence=0.7,
    min_tracking_confidence=0.7) as hands:

    while True:
        success, frame = cap.read()
        if not success:
            print("Erreur : caméra non détectée.")
            break

        # Conversion BGR -> RGB pour MediaPipe
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        results = hands.process(frame_rgb)
        frame = cv2.cvtColor(frame_rgb, cv2.COLOR_RGB2BGR)

        # === Si des mains sont détectées ===
        if results.multi_hand_landmarks and results.multi_handedness:
            for hand_idx, (hand_landmarks, hand_label) in enumerate(zip(results.multi_hand_landmarks, results.multi_handedness)):
               
                # Obtenir la main (Left ou Right)
                hand_type = hand_label.classification[0].label  # "Left" ou "Right"
                score = hand_label.classification[0].score       # niveau de confiance
               
                # Dessine les repères de la main
                mp_drawing.draw_landmarks(
                    frame,
                    hand_landmarks,
                    mp_hands.HAND_CONNECTIONS,
                    mp_drawing_styles.get_default_hand_landmarks_style(),
                    mp_drawing_styles.get_default_hand_connections_style())
               
                # Obtenir la position du poignet (repère 0)
                h, w, _ = frame.shape
                wrist = hand_landmarks.landmark[0]
                x, y = int(wrist.x * w), int(wrist.y * h)
               
                # Affiche le texte (main gauche/droite + confiance)
                cv2.putText(frame, f"{hand_type} ({score:.2f})",
                            (x - 50, y - 20),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.8, (0, 255, 0), 2)

            # Afficher le nombre de mains détectées
            cv2.putText(frame, f"Mains détectées : {len(results.multi_hand_landmarks)}",
                        (10, 30), cv2.FONT_HERSHEY_SIMPLEX,
                        1, (0, 255, 0), 2)

        # Afficher la vidéo
        cv2.imshow("Détection des deux mains (Left / Right) - Appuie sur Q pour quitter", frame)

        # Quitter avec la touche 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

# Libérer la caméra et fermer les fenêtres
cap.release()
cv2.destroyAllWindows()
