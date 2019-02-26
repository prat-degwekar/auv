import cv2
import numpy as np

img = cv2.imread( '''path of image''', 0)

cv2.imshow('image', img)
cv2.waitkey(0)
cv2.destroyAllWindows()
