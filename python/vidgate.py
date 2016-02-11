import cv2
import numpy as np
from matplotlib import pyplot as plt

#img = cv2.imread( 'gate_img1.jpg', 1)
cap = cv2.VideoCapture('video.mp4')

#edges = cv2.Canny(img, 250, 250)

lower_thresh = 200
upper_thresh = 200
apSize = 5 #make 5 or 7 for increasing sensitivity

#Hough line settings

rho = 1.0
theta = np.pi/180
hough_thresh = 10
minLineLen = 10
maxLineGap = 60

while( cap.isOpened() ):
    ret, frame = cap.read()

    edges = cv2.Canny(frame, lower_thresh, upper_thresh, apertureSize = apSize)

    lines = cv2.HoughLinesP( edges, rho, theta, hough_thresh, minLineLen, maxLineGap) 
    #l1 = lines[0][0]

    #print(l1)

    print(lines)

    #cv2.line( img, ( l1[0], l1[1] ), ( l1[2], l1[3] ), (255, 0, 0), 5 )
    
    #cv2.imshow('frame', frame)    

    if lines is None:
        print("No lines found")

    else:
        for i in range(len(lines)):
            ll = lines[i][0]
            cv2.line( frame, (ll[0], ll[1]), (ll[2], ll[3]), (255,255,0), 5 )
            #print(lines[i][1])

        plt.subplot(121), plt.imshow(frame, cmap = 'gray')
        plt.title('Original Image')#, plt.xticks([]), plt.yticks([])

        plt.subplot(122), plt.imshow(edges, cmap = 'gray')
        plt.title('Edge Image')#, plt.xticks([]), plt.yticks([])

        plt.show()

    if cv2.waitKey(1) & 0xFF == ord('q'):
	break

cap.release()
cv2.destroyAllWindows()

#cv2.imshow('image', img)
#print(img)
#cv2.waitKey(0)
#cv2.destroyAllWindows()
