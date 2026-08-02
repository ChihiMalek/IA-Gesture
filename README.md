# Processed Dataset

This folder holds the processed landmark dataset — hand landmark
coordinates extracted via MediaPipe from the raw images in
[`../raw/`](../raw/) — used to train the gesture-classification model
stored in [`src/models/`](../../src/models/) as `modele_mots.pkl`.

Populate it by running your feature-extraction/training pipeline on the
raw dataset (e.g. exporting each sample's 63-value landmark vector plus
its gesture label to a CSV or NumPy array before training).
