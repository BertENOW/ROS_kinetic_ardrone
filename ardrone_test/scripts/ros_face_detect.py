#!/usr/bin/env python
import cv2 as cv
from sensor_msgs.msg import Image
from cv_bridge import CvBridge as cvb
import rospy

image_topic = "/ardrone/front/image_raw"

#detec frontal face
frontalface_default = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"
face_cascade = cv.CascadeClassifier(frontalface_default)

br = cvb()

#function to be implemented later (end of month).
#I was thnking maybe stop current action and update enviroment map
def face_detect_action():
    pass

def convert_detect(imgmag):
    img = br.imgmsg_to_cv2(imgmag, "bgr8")
    img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    faces = face_cascade.detectMultiScale(img_gray, 1.2,5)
    
    if faces is not None:
        for (x, y, w, h) in faces:
            cv.rectangle(img, (x, y), (x+w, y+h), (0,255,0), 2)
            cv.putText(img, "Face detected", (x, y-10), cv.FONT_HERSHEY_SIMPLEX, .5, (0, 0, 255), 2)
        face_detect_action()
    
    cv.imshow("ROS Face detect", img)
    
    #delay 10 ms and when q is pressed shutdown the node
    if cv.waitKey(10) & 0xFF==ord('q'):
        rospy.signal_shutdown("End node")
    
if __name__=='__main__':
    rospy.init_node("ROS_face_detect")
    rospy.Subscriber(image_topic, Image,convert_detect)
    rospy.spin()