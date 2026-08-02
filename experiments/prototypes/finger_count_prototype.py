import cv2
import numpy as np
import tkinter as tk
from PIL import Image, ImageTk

# Simple mapping: you can expand this for more letters!
FINGER_TO_LETTER = {1: "A", 2: "B", 3: "C", 4: "D", 5: "E"}

def detect_fingers_and_mask(frame):
    roi = frame[100:400, 100:400]
    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    lower_skin = np.array([0, 20, 70], dtype=np.uint8)
    upper_skin = np.array([20, 255, 255], dtype=np.uint8)
    mask = cv2.inRange(hsv, lower_skin, upper_skin)
    kernel = np.ones((3, 3), np.uint8)
    mask = cv2.dilate(mask, kernel, iterations=4)
    mask = cv2.GaussianBlur(mask, (5,5), 100)
    contours, _ = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    fingers = 0
    if contours:
        cnt = max(contours, key=cv2.contourArea)
        hull_indices = cv2.convexHull(cnt, returnPoints=False)
        if hull_indices is not None and len(hull_indices) > 3:
            defects = cv2.convexityDefects(cnt, hull_indices)
            if defects is not None:
                for i in range(defects.shape[0]):
                    s,e,f,d = defects[i,0]
                    start = tuple(cnt[s][0])
                    end = tuple(cnt[e][0])
                    far = tuple(cnt[f][0])
                    a = np.linalg.norm(np.array(end) - np.array(start))
                    b = np.linalg.norm(np.array(far) - np.array(start))
                    c = np.linalg.norm(np.array(end) - np.array(far))
                    angle = np.arccos((b**2 + c**2 - a**2)/(2*b*c))
                    if angle <= np.pi/2:
                        fingers += 1
    return fingers + 1 if fingers > 0 else 0, mask

class App:
    def __init__(self, window, window_title):
        self.window = window
        self.window.title(window_title)
        self.video_source = 0
        self.vid = cv2.VideoCapture(self.video_source)
        self.frame_label = tk.Label(window)
        self.frame_label.pack(side=tk.LEFT)
        self.mask_label = tk.Label(window)
        self.mask_label.pack(side=tk.LEFT)
        self.finger_label = tk.Label(window, text='Doigts : 0', font=("Arial", 20))
        self.finger_label.pack()
        self.letter_label = tk.Label(window, text='Lettre : ', font=("Arial", 22), fg="blue")
        self.letter_label.pack()
        self.close_button = tk.Button(window, text="Close", font=("Arial", 14), command=self.close)
        self.close_button.pack()
        self.running = True
        self.update()
        self.window.protocol("WM_DELETE_WINDOW", self.close)
        self.window.mainloop()

    def update(self):
        if not self.running:
            return
        ret, frame = self.vid.read()
        if ret:
            frame = cv2.flip(frame, 1)
            fingers, mask = detect_fingers_and_mask(frame)
            self.finger_label.config(text=f'Doigts : {fingers}')
            letter = FINGER_TO_LETTER.get(fingers, "")
            self.letter_label.config(text=f'Lettre : {letter}')
            cv2.rectangle(frame, (100, 100), (400, 400), (0,255,0), 2)
            img_color = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img = Image.fromarray(img_color)
            imgtk = ImageTk.PhotoImage(image=img)
            self.frame_label.imgtk = imgtk
            self.frame_label.configure(image=imgtk)
            mask_rgb = cv2.cvtColor(mask, cv2.COLOR_GRAY2RGB)
            mask_img = Image.fromarray(mask_rgb)
            mask_imgtk = ImageTk.PhotoImage(image=mask_img)
            self.mask_label.imgtk = mask_imgtk
            self.mask_label.configure(image=mask_imgtk)
        self.window.after(20, self.update)

    def close(self):
        self.running = False
        if self.vid.isOpened():
            self.vid.release()
        self.window.destroy()

App(tk.Tk(), "IHM Détection Doigts vers Alphabet")
