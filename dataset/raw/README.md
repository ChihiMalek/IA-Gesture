# Raw Dataset

This folder holds the raw images captured by
[`src/training/collect_dataset.py`](../../src/training/collect_dataset.py),
organized as one subfolder per gesture label (e.g. `hello/`, `thanks/`,
`yes/`, `no/`, `peace/`).

Run the collection script to populate it:

```bash
cd src/training
python collect_dataset.py
```

Add your own captured dataset here before training a model. Consider
excluding large raw-image sets from version control (e.g. via `.gitignore`
or Git LFS) if the dataset grows large.
