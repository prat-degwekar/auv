import cv2
import numpy as np
import math
import colorsys
#import imutils
#import constant
import time
#import constant

def changeToCartesian(location):
    location_c = []
    if not(location == [] or location is None ):
        location_c= (-int((constant.resizeWidth/2) - location[0]),int((constant.resizeHeight/2) - location[1]))
        return location_c
    return location

def changeToPosCoordinate(location):
    location_c = []
    if not(location == [] or location is None ):
        location_c = (int(location[0]+(constant.resizeWidth/2)),int((constant.resizeHeight/2) - location[1]))
        return location_c
    return location

class gateDetect:

    def __init__(self):
        self.vSlopeLimit = 10
        self.hSlopeLimit = 1
        self.gap = 10
        self.sideRatio = 0.5
        self.aspectRatioTarget = 1
        self.aspectRatioTolerance = 0.3
        self.cannyThreshold = 1000
        self.angleDifference = 5 #degree
        self.vlineMax = 50
        self.hlineMax = 50
        self.centerPoint = None
        self.cPointLogSize = 50
        self.boxLogSize = 50
        self.cPointLog = []
        self.boxLog = []

    def line_intersect(self,line1, line2):
        xdiff = (line1[0] - line1[2], line2[0] - line2[2])
        ydiff = (line1[1] - line1[3], line2[1] - line2[3])
        def det(a, b):
            return a[0] * b[1] - a[1] * b[0]

        div = det(xdiff, ydiff)
        if div == 0:
           return False, False
        else:
            d = (det(*((line1[0],line1[2]), (line1[1],line1[3]))), det(*((line2[0],line2[2]), (line2[1],line2[3]))))
            x = det(d, xdiff) / div
            y = det(d, ydiff) / div
            if( ((line1[0]<=x<=line1[2]) or (line1[2]<=x<=line1[0])) and ((line2[0]<=x<=line2[2]) or (line2[2]<=x<=line2[0])) and (line1[1]<=y<=line1[3]) or (line1[3]<=y<=line1[1]) and ((line2[1]<=y<=line2[3]) or (line2[3]<=y<=line2[1]))):
                return x, y
            else:
                if(self.lineLength((line1[0],line1[1],line2[0],line2[1]))<self.gap) or (self.lineLength((line1[2],line1[3],line2[2],line2[3]))<self.gap) or (self.lineLength((line1[0],line1[1],line2[2],line2[3]))<self.gap) or (self.lineLength((line1[2],line1[3],line2[0],line2[1]))<self.gap):
                    return x, y
                return False, False

    def midpoint(self,p1, p2):
        return ((abs(p1[0]+p2[0])/2,abs(p1[1]+p2[1])/2))

    def findTop(self,line):
        if(line[1]<line[3]):
            return (line[0],line[1])
        else:
            return (line[2],line[3])

    def findBottom(self,line):
        if(line[1]>line[3]):
            return (line[0],line[1])
        else:
            return (line[2],line[3])

    def lineLength(self,line):
        length = math.sqrt((line[0] - line[2])**2 + (line[1] - line[3])**2)
        return length

    def verticalLink(self,vLine1,hLine1,vLine2):

        midpoint_x, midpoint_y = self.midpoint((hLine1[0],hLine1[1]),(hLine1[2],hLine1[3]))
        min_x = min(vLine1[0],vLine1[2],vLine2[0],vLine2[2])
        max_x = max(vLine1[0],vLine1[2],vLine2[0],vLine2[2])
        if(min_x<=midpoint_x<=max_x):
            return True
        else:
            return False

    def overlap(self,vLine1,hLine1,vLine2):

        overlap1 = self.line_intersect(vLine1,hLine1)
        overlap2 = self.line_intersect(vLine2,hLine1)
        if not(overlap1[0] and overlap1[1] and overlap2[0] and overlap2[1]):
            return False
        else:
            return True

    def vLineOnTop(self,vLine1,hLine1,vLine2):
        vLine1Intersect_y = self.line_intersect(vLine1,hLine1)[1]
        vLine2Intersect_y = self.line_intersect(vLine2,hLine1)[1]
        if((self.findTop(vLine1)[1]+(abs(vLine1[1]-vLine1[3])*0.2))>=vLine1Intersect_y>=self.findTop(vLine1)[1]) and ((self.findTop(vLine2)[1]+(abs(vLine2[1]-vLine2[3])*0.2))>=vLine2Intersect_y>=self.findTop(vLine2)[1]):
            return True
        return False

    def hLineOnSide(self,vLine1,hLine1,vLine2):
        if(self.sideRatio<=(abs(self.line_intersect(vLine1,hLine1)[0]-self.line_intersect(vLine2,hLine1)[0])/self.lineLength(hLine1))<(1+self.sideRatio)):
            return True
        else:
            return False

    def aspectRatio(self,vLine1,hLine1,vLine2):
        return (self.lineLength(hLine1)/((self.lineLength(vLine1)+self.lineLength(vLine2))*0.5))

    def find_nearest(self,array, value):
        array = np.asarray(array)
        idx = (np.abs(array - value)).argmin()
        return idx,array[idx]

    def findCenterPoint(self,vLine1,hLine1,vLine2):

        vLine1Intersect = self.line_intersect(vLine1,hLine1)
        vLine2Intersect = self.line_intersect(vLine2,hLine1)
        if(vLine1Intersect):
            pt1=(int(vLine1Intersect[0]),int(vLine1Intersect[1]))
        else:
            pt1 = (int(self.findTop(vLine1)[0]),int(self.findTop(vLine1)[1]))
        pt3 = (int(self.findBottom(vLine1)[0]),int(self.findBottom(vLine1)[1]))
        if(vLine2Intersect):
            pt2 = (int(vLine2Intersect[0]),int(vLine2Intersect[1]))
        else:
            pt2 = (int(self.findTop(vLine2)[0]),int(self.findTop(vLine2)[1]))
        pt4 = (int(self.findBottom(vLine2)[0]),int(self.findBottom(vLine2)[1]))

        centerPoint = (int((pt1[0]+pt2[0]+pt3[0]+pt4[0])/4),int((pt1[1]+pt2[1]+pt3[1]+pt4[1])/4))

        return centerPoint

    def findvAngle(self,l):
        slope = (l[1]-l[3])/(l[0]-l[2])
        radian = math.atan(slope)
        angle = radian*180/math.pi
        return angle

    def findhAngle(self,l):
        slope = (l[0]-l[2])/(l[1]-l[3])
        radian = math.atan(slope)
        angle = radian*180/math.pi
        return angle

    def angleDiff(self,l1,l2):
        sumAngle = l1+l2
        if(sumAngle>90):
            return(abs(l1-l2))
        elif(sumAngle<-90):
            return (l1+l2+180)
        else:
            return(l1+l2)
    def findBox(self,vLine1,hLine1,vLine2):

        vLine1Intersect = self.line_intersect(vLine1,hLine1)
        vLine2Intersect = self.line_intersect(vLine2,hLine1)
        if(vLine1Intersect):
            pt1=(int(vLine1Intersect[0]),int(vLine1Intersect[1]))
        else:
            pt1 = (int(self.findTop(vLine1)[0]),int(self.findTop(vLine1)[1]))
        pt3 = (int(self.findBottom(vLine1)[0]),int(self.findBottom(vLine1)[1]))
        if(vLine2Intersect):
            pt2 = (int(vLine2Intersect[0]),int(vLine2Intersect[1]))
        else:
            pt2 = (int(self.findTop(vLine2)[0]),int(self.findTop(vLine2)[1]))
        pt4 = (int(self.findBottom(vLine2)[0]),int(self.findBottom(vLine2)[1]))

        if(pt1[0]<pt2[0]):
            x1 = pt1[0]
            y1 = pt1[1]
            x2 = pt4[0]
            y2 = pt4[1]
        else:
            x1 = pt2[0]
            y1 = pt2[1]
            x2 = pt3[0]
            y2 = pt3[1]
        return [x1,y1,x2,y2]

    def findArea(box):
        return(box[2]*box[3])

    def cPointLogger(self,cPoint):
        if not (cPoint == [] or cPoint is None):
            self.cPointLog.append([cPoint[0],cPoint[1]])
            if len(self.cPointLog)>self.cPointLogSize:
                del self.cPointLog[0]

    def getcPointLog(self):
        return self.cPointLog

    def boxLogger(self,box):
        if not (box == [] or box is None):
            self.boxLog.append(box)
            if len(self.boxLog)>self.boxLogSize:
                del self.boxLog[0]

    def getcPointLog(self):
        return self.cPointLog

    def getBoxLog(self):
        return self.boxLog

    def gateImage(self,img):
        location,gate_img,gate_edges = self.gateDetection(img)
        return gate_img,gate_edges

    def gateLocation(self,img):
        return self.gateDetection(img)[0]

    def gateDetection(self,img):
        vLine = []
        hLine = []
        line_combination = []
        aspectRatioArray = []
        #img = imutils.resize(img, width=constant.resizeWidth, height = constant.resizeHeight)
        # img = cv2.fastNlMeansDenoisingColored(img,None,10,10,3,9)
	img = imread( 'gate_img1.jpg', 1)
        edges = cv2.Canny(img,self.cannyThreshold,self.cannyThreshold,apertureSize = 5)
        lines = cv2.HoughLinesP(edges,1.1,np.pi/180,50,minLineLength = 10,maxLineGap =30)
        if lines is not None:
            for i in range(0, len(lines)):

                l = lines[i][0]
                cv2.line(img, (l[0], l[1]), (l[2], l[3]), (0,255,255), 1)
                if not (l[0]-l[2]) ==0:
                    slope = abs((l[1]-l[3])/(l[0]-l[2]))
                else:
                    slope = math.inf
                if slope > self.vSlopeLimit:
                    vLine.append(l)
                    cv2.line(img, (l[0], l[1]), (l[2], l[3]), (0,0,255), 1)
                elif slope < self.hSlopeLimit:
                    hLine.append(l)
                    cv2.line(img, (l[0], l[1]), (l[2], l[3]), (0,0,255), 1)
        filtered_line_combination = []
        # print(len(vLine),len(hLine))
        if not (len(vLine)>self.vlineMax or len(hLine) > self.hlineMax):
            for j in hLine:
                for idx_i,i in enumerate(vLine):
                    for idx_k,k in enumerate(vLine):
                        if(idx_k>idx_i):
                            if(self.verticalLink(i,j,k)):
                                # cv2.line(img,(i[0], i[1]), (i[2], i[3]),(0,255,255),1)
                                # cv2.line(img,(j[0], j[1]), (j[2], j[3]),(0,255,255),1)
                                # cv2.line(img,(k[0], k[1]), (k[2], k[3]),(0,255,255),1)
                                # line_combination.append([i,j,k])
                                if self.overlap(i,j,k):
                                    # cv2.line(img,(i[0], i[1]), (i[2], i[3]),(0,0,255),1)
                                    # cv2.line(img,(j[0], j[1]), (j[2], j[3]),(0,0,255),1)
                                    # cv2.line(img,(k[0], k[1]), (k[2], k[3]),(0,0,255),1)
                                    if self.vLineOnTop(i,j,k):
                                        # cv2.line(img,(i[0], i[1]), (i[2], i[3]),(0,0,255),1)
                                        # cv2.line(img,(j[0], j[1]), (j[2], j[3]),(0,0,255),1)
                                        # cv2.line(img,(k[0], k[1]), (k[2], k[3]),(0,0,255),1)
                                        if self.hLineOnSide(i,j,k):
                                            # cv2.line(org_img,(i[0], i[1]), (i[2], i[3]),(0,255,255),1)
                                            # cv2.line(org_img,(j[0], j[1]), (j[2], j[3]),(0,255,255),1)
                                            # cv2.line(org_img,(k[0], k[1]), (k[2], k[3]),(0,255,255),1)
                                            if self.angleDiff(self.findvAngle(i),self.findhAngle(j))<self.angleDifference and self.angleDiff(self.findvAngle(k),self.findhAngle(j))<self.angleDifference:
                                                # cv2.line(img,(i[0], i[1]), (i[2], i[3]),(0,255,255),1)
                                                # cv2.line(img,(j[0], j[1]), (j[2], j[3]),(0,255,255),1)
                                                # cv2.line(img,(k[0], k[1]), (k[2], k[3]),(0,255,255),1)
                                                filtered_line_combination.append([i,j,k])
                                                aspectRatioArray.append(self.aspectRatio(i,j,k))
            if not aspectRatioArray == []:
                i,j,k = filtered_line_combination[self.find_nearest(aspectRatioArray,self.aspectRatioTarget)[0]]
                # print(self.find_nearest(aspectRatioArray,self.aspectRatioTarget)[1])
                if((self.aspectRatioTarget-self.aspectRatioTolerance)<=self.find_nearest(aspectRatioArray,self.aspectRatioTarget)[1]<=(self.aspectRatioTarget+self.aspectRatioTolerance)):
                    cv2.line(img,(i[0], i[1]), (i[2], i[3]),(0,255,255),1)
                    cv2.line(img,(j[0], j[1]), (j[2], j[3]),(0,255,255),1)
                    cv2.line(img,(k[0], k[1]), (k[2], k[3]),(0,255,255),1)
                    centerPoint = self.findCenterPoint(i,j,k)
                    self.cPointLogger(centerPoint)
                    # print(self.cPointLog)
                    # print("Center of gate: ", centerPoint)
                    self.boxLogger(self.findBox(i,j,k))
                    # print(self.boxLog)
                    return centerPoint,img,edges
        return None,img,edges


if __name__ == "__main__":
    gateDetect = gateDetect()
    org_img = cv2.imread('image/Gate4.png')
    # org_img = cv2.imread('image/Capture5.jpg')
    # org_img = cv2.imread('image/gate.jpeg')
    # org_img = cv2.imread('image/ate1.png')
    # org_img = cv2.imread('image/2.jpg')
    location, img,edges = gateDetect.gateLocation()
    print(location)
    print(changeToPosCoordinate(location))
    cv2.circle(img,changeToPosCoordinate(location), 10, (255, 0, 0), -1)
    cv2.imshow('Gate',img)
    cv2.imshow('Edge',edges)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
