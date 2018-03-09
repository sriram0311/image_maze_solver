import cv2
import numpy as np
from matplotlib import pyplot as plt
import math
import matplotlib.path as mplPath
from math import atan2, degrees, pi
import pprint


cap = cv2.VideoCapture(0)

for i in range(50):
    _, frame = cap.read()

def cam_read():
    _, frame = cap.read()
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    ret,thresh1 = cv2.threshold(gray,127,255,cv2.THRESH_BINARY)
    cv2.imshow('frame',gray)

def nothing(x):
    pass

def color_detection():
    cv2.namedWindow('image')
    img = cv2.imread('/home/anush_sr/Downloads/arrow.jpg')

    cv2.createTrackbar('lower_R','image',0,255,nothing)
    cv2.createTrackbar('low_G','image',0,255,nothing)
    cv2.createTrackbar('low_B','image',0,255,nothing)


    cv2.createTrackbar('high_R','image',0,255,nothing)
    cv2.createTrackbar('h_G','image',0,255,nothing)
    cv2.createTrackbar('h_B','image',0,255,nothing)
    while 1:
        k = cv2.waitKey(1) & 0xFF
        if k == 27:
            break

        l_r = cv2.getTrackbarPos('lower_R','image')
        l_g = cv2.getTrackbarPos('low_G','image')
        l_b = cv2.getTrackbarPos('low_B','image')

        h_r = cv2.getTrackbarPos('high_R','image')
        h_b = cv2.getTrackbarPos('h_G','image')
        h_g = cv2.getTrackbarPos('h_B','image')


        lower_red = np.array([l_r,l_g,l_b])
        upper_red = np.array([h_r,h_g,h_b])

        #convert BGR to HSV
        imgHSV= cv2.cvtColor(img,cv2.COLOR_BGR2HSV)
        # create the MaskHSV,lower_red,upper_red)
        mask=cv2.inRange(imgHSV,lower_red,upper_red)



        print lower_red, upper_red


        res = cv2.bitwise_and(img,img, mask= mask)

        cv2.imshow('image',res)
        cv2.imshow('mas',mask)
        cv2.imwrite('test_res.jpg',res)


def direction2():
    img = cv2.imread('test_res.jpg')
    edges = cv2.Canny(img,500,600,apertureSize = 3)
    cv2.imshow('edges',edges)
    """_a, cnts,s = cv2.findContours(edges, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    cnts = sorted(cnts, key = cv2.contourArea, reverse = True)[:10]

    for c in cnts:
	# approximate the contour
        peri = cv2.arcLength(c, True)
        approx = cv2.approxPolyDP(c, 0.05 * peri, True)
        if cv2.contourArea(c) > 1500:
	# if our approximated contour has four points, then
	# we can assume that we have found our screen
            screenCnt = approx
            print len(screenCnt)
            cv2.drawContours(img, [screenCnt], -1, (0, 255, 0), 3)
    cv2.imshow("Game Boy Screen", img)"""

    minLineLength = 1
    maxLineGap = 5
    lines = cv2.HoughLinesP(edges, 1, np.pi / 180, 150, None, minLineLength, maxLineGap)
    print lines
    for x1, y1, x2, y2 in lines[0]:
        cv2.line(img, (x1, y1), (x2, y2), (0, 255, 0), 2)

    cv2.imshow('final',img)

    k = cv2.waitKey(0)
    if k == 27:
        cv2.destroyAllWindows();

def process_img():
    img = cv2.imread('junction30.jpg')

    img = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)



    pts1 = np.float32([[14,16],[605,16],[14,436],[605,436]])
    pts2 = np.float32([[0,0],[300,0],[0,300],[300,300]])

    M = cv2.getPerspectiveTransform(pts1,pts2)

    dst = cv2.warpPerspective(img,M,(300,300))

    ret,thresh1 = cv2.threshold(dst,127,255,cv2.THRESH_BINARY)

    edges = cv2.Canny(thresh1,500,600,apertureSize = 3)

    right_line = dst[126:272,250:300]

    left_line = dst[121:276,0:40]

    top_line = dst[46:120,29:251]

    def right(right_line):
        line = 0
        ret,thres = cv2.threshold(right_line,127,255,cv2.THRESH_BINARY)
        for j in range(len(thres)):
            for  i in range(40):
                if thres[j,i] == 255:
                    line = line + 1

        if line > 1000:
            return True
        else:
            return False

    def left(left_line):
        line = 0
        ret,thres = cv2.threshold(left_line,127,255,cv2.THRESH_BINARY)
        for j in range(len(thres)):
            for  i in range(40):
                if thres[j,i] == 255:
                    line = line + 1

        if line > 1000:
            return True
        else:
            return False

    def straight(top_line):
        line = 0
        ret,thres = cv2.threshold(top_line,127,255,cv2.THRESH_BINARY)
        for j in range(len(thres)):
            for  i in range(40):
                if thres[j,i] == 255:
                    line = line + 1

        if line > 1000:
            return True
        else:
            return False

    if right(right_line) == True and left(left_line) == True and straight(top_line) == True:
        return 1
    elif  right(right_line) == True and left(left_line) == False and straight(top_line) == False:
        return 2
    elif  right(right_line) == False and left(left_line) == False and straight(top_line) == True:
        return 3

    elif  right(right_line) == False and left(left_line) == True and straight(top_line) == True:
        return 4
    elif  right(right_line) == False and left(left_line) == True and straight(top_line) == False:
        return 5
    elif  right(right_line) == True and left(left_line) == True and straight(top_line) == False:
        return 6

    k = cv2.waitKey(0)
    if k == 27:
        cv2.destroyAllWindows();







if __name__ == '__main__':
    color_detection()
