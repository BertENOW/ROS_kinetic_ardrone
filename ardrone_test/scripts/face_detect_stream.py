#!/usr/bin/env python
import cv2 as cv

#detec frontal face
frontalface_default = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"
face = cv.CascadeClassifier(frontalface_default)

# capture object, captures video (image stream) from default cam on device
cap = cv.VideoCapture(0)

while True:
    success, img = cap.read()
    img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    
    #detect face in each video frame
    faces = face.detectMultiScale(img_gray, 1.2, 5)
    
    #draw rectangle around each detected face
    for (x,y,w,h) in faces:
        cv.rectangle(img, (x,y), (x+w, y+h), (0,255,0), 2)
        cv.putText(img, "Face detected", (x, y-10), cv.FONT_HERSHEY_SIMPLEX, .5, (0, 0, 255), 2)
        
    #display the video and exit when space is pressed
    cv.imshow("Video Face detect", img)
    if cv.waitKey(1) & 0xFF==ord(' '):
        break