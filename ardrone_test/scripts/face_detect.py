#!/usr/bin/env python
import cv2 as cv

#different cascade files for detecting different facial and body features
#detec frontal face
frontalface_default = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"

#fronotal face al tree
frontalface_alt_tree = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt_tree.xml"


#load defaults frontal face classifier
face = cv.CascadeClassifier(frontalface_default)

#load color image
path = "/home/bert/arsim_ws/src/ardrone_test/resources/faces.jpeg"
img = cv.imread(path)

#convert image from 3 color space to 1 (gray)
img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

#detect faces in image 
faces = face.detectMultiScale(img_gray, 1.05, 2)

#draw green boc around found faces
for (x,y,w,h) in faces:
    cv.rectangle(img, (x,y), (x+w, y+h), (0,255,0), 1)
    
cv.imshow("Face detect", img)
cv.waitKey(0)