# Assumes you have a trained Keras model 'asl_model.h5'
import cv2
import numpy as np
import tkinter as tk
from PIL import Image, ImageTk
from tensorflow.keras.models import load_model

model = load_model('asl_model.h5')  # Pre-trained model for ASL alphabet
class_names = ["A", "B", "C", "D", ..., "Z"]  # List of sign language letters

def preprocess(roi):
    # Resize and normalize for the model (adjust as your model needs)
    roi = cv2.resize(roi, (64, 64))  # Typical input size, check your model!
    roi = roi.astype('float32') / 255.0
    roi = np.expand_dims(roi, axis=0)
    return roi

class App:
    def __init__(self, window, window_title):
        self.window = window
        self.window.title(window_title)
        self.video_source = 0
        self.vid = cv2.VideoCapture(self.video_source)
        self.frame_label = tk.Label(window)
        self.frame_label.pack(side=tk.LEFT)
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
            cv2.rectangle(frame, (100, 100), (400, 400), (0,255,0), 2)
            roi = frame[100:400, 100:400]
            img_color = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            img = Image.fromarray(img_color)
            imgtk = ImageTk.PhotoImage(image=img)
            self.frame_label.imgtk = imgtk
            self.frame_label.configure(image=imgtk)
            
            # Predict letter
            preprocessed = preprocess(roi)
            pred = model.predict(preprocessed)
            letter = class_names[np.argmax(pred)]
            self.letter_label.config(text=f'Lettre : {letter}')
        self.window.after(20, self.update)

    def close(self):
        self.running = False
        if self.vid.isOpened():
            self.vid.release()
        self.window.destroy()

App(tk.Tk(), "IHM Détection Alphabet Langue des Signes")
