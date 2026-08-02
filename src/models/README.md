# Trained Models

Place the trained gesture-classification model here as `modele_mots.pkl`.

This file is loaded by `src/gesture_recognition/handgestures.py`:

```python
MODEL_FILE = "modele_mots.pkl"
```

> **Note:** the trained model binary is not bundled in this repository —
> train your own using [`src/training/collect_dataset.py`](../training/collect_dataset.py)
> to build a dataset, then add the resulting `modele_mots.pkl` here.
> Consider tracking it with [Git LFS](https://git-lfs.com/) once added,
> since trained model files are typically binary and can be large.
