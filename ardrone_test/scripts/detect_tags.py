#!/usr/bin/env python
import cv2 as cv

#load color image
path = "/home/bert/arsim_ws/src/ardrone_test/resources/tags.jpg"
img = cv.imread(path)
img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

april_dict = cv.aruco.Dictionary_get(cv.aruco.DICT_6X6_1000)
arucoParams = cv.aruco.DetectorParameters_create()
arucoParams.adaptiveThreshWinSizeStep =1
corners, ids, rejected = cv.aruco.detectMarkers(img_gray, april_dict , parameters=arucoParams)


if ids is not None:
    print("true")
    cv.aruco.drawDetectedMarkers(img, corners, ids)
    cv.imshow("Detect April tags", img)
    cv.waitKey(0)
    cv.destroyAllWindows()