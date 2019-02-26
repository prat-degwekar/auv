import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread( 'gate_try1.jpeg', 0)

#edges = cv2.Canny(img, 250, 250)

lower_thresh = 100
upper_thresh = 200
apSize = 3 #make 5 or 7 for increasing sensitivity

edges = cv2.Canny(img, lower_thresh, upper_thresh, apertureSize = apSize)

plt.subplot(121), plt.imshow(img, cmap = 'gray')
plt.title('Original Image'), plt.xticks([]), plt.yticks([])

plt.subplot(122), plt.imshow(edges, cmap = 'gray')
plt.title('Edge Image'), plt.xticks([]), plt.yticks([])

plt.show()

#cv2.imshow('image', img)
#cv2.waitKey(0)
#cv2.destroyAllWindows()
