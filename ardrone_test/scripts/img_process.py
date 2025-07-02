#!/usr/bin/env python
import cv2 as cv
#import numpy as np

path = "/home/bert/arsim_ws/src/ardrone_test/resources/"
img = cv.imread(path)
cv.imshow("img", img)
cv.waitKey(0)
# cv.destroyAllWindows()