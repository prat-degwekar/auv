import cv2
import numpy as np
from matplotlib import pyplot as plt

img = cv2.imread( 'gate_try1.jpeg', 0)

#edges = cv2.Canny(img, 250, 250)

lower_thresh = 100
upper_thresh = 200
apSize = 3 #make 5 or 7 for increasing sensitivity

#Hough line settings

rho = 1
theta = np.pi/180
hough_thresh = 80
minLineLen = 10
maxLineGap = 30

edges = cv2.Canny(img, lower_thresh, upper_thresh, apertureSize = apSize)

lines = cv2.HoughLinesP( edges, rho, theta, hough_thresh, minLineLen, maxLineGap) 
l1 = lines[0][0]

print(l1)

print(lines)

cv2.line( img, ( l1[0], l1[1] ), ( l1[2], l1[3] ), (255, 0, 0), 5 )

for i in range(len(lines)):
    ll = lines[i][0]
    cv2.line( img, (ll[0], ll[1]), (ll[2], ll[3]), (255,0,0), 5 )
    #print(lines[i][1])

plt.subplot(121), plt.imshow(img, cmap = 'gray')
plt.title('Original Image'), plt.xticks([]), plt.yticks([])

plt.subplot(122), plt.imshow(edges, cmap = 'gray')
plt.title('Edge Image'), plt.xticks([]), plt.yticks([])

plt.show()

#cv2.imshow('image', img)
#cv2.waitKey(0)
#cv2.destroyAllWindows()
