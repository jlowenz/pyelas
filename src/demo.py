#!/usr/bin/env python

from elas import *
import numpy as np
import cv2
from skimage.io import imread
import pathlib as pl
import sys
import matplotlib.pyplot as plt

if len(sys.argv) < 3:
    print 'Usage ./demo.py image1 image2'
    sys.exit(0)

image1 = pl.Path(sys.argv[1])
image2 = pl.Path(sys.argv[2])
assert image1.exists() and image2.exists(), "Image files don't exist"

im1 = imread(str(image1))
im2 = imread(str(image2))

d1 = np.empty_like(im1, dtype=np.float32)
d2 = np.empty_like(im2, dtype=np.float32)

params = Elas_parameters()
params.postprocess_only_left = False
elas = Elas(params)
elas.process_stereo(im1, im2, d1, d2)

scaled_d1 = (d1 / np.amax(d1) * 255.0).astype(np.uint8)

plt.figure()
plt.imshow(scaled_d1)
plt.show()
