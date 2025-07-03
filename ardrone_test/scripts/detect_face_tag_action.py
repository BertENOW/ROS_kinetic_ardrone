#!/usr/bin/env python
#This script will detect faces and aruco tags using opencv and perform an action
import rospy
import cv2 as cv
from cv_bridge import CvBridge as cvb
from ardrone_test.srv import *
from sensor_msgs.msg import Image

br = cvb()
image_topic = "/ardrone/front/image_raw"

# cascade classifiers setup to detect frontal face
frontalface_default = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_default.xml"
face_cascade = cv.CascadeClassifier(frontalface_default)

#setup to detect aruco tags. we aim to detect the original aruco tags
aruco_dict = cv.aruco.Dictionary_get(cv.aruco.DICT_ARUCO_ORIGINAL)
aruco_params = cv.aruco.DetectorParameters_create()
aruco_params.adaptiveThreshWinSizeStep =1


#action when a face is detected
def face_detect_action():
    pass

#action when an aruco tag is detected. We'll land the drone
def tag_detect_action(request):
    rospy.wait_for_service("toff_land_service")
    print("sending request to server")
    try:
        land_drone = rospy.ServiceProxy("toff_land_service", TakeoffLandService)
        response  = land_drone(request)
        return response.success
    except rospy.ServiceException as e:
        print("Service call failed: %s" %e)
    

def detect_face_tag(imgmsg):
    tag_located= False
    request=0
    #convert ros sensor image to an oepn cv bgr image
    img = br.imgmsg_to_cv2(imgmsg, "bgr8")
    img_gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    
    #detect face and draw rectangle around it
    faces = face_cascade.detectMultiScale(img_gray, 1.2, 5)
    if faces is not None:
        for (x, y, w, h) in faces:
            cv.rectangle(img, (x, y), (x+w, y+h), (0,255,0), 2)
            cv.putText(img, "Face detected", (x, y-10), cv.FONT_HERSHEY_SIMPLEX, .35, (0, 0, 255), 1)
        face_detect_action()
    
    #detect aruco tags and draw markers    
    corners, ids, rejected = cv.aruco.detectMarkers(img_gray, aruco_dict, parameters=aruco_params)
    if ids is not None:
        cv.aruco.drawDetectedMarkers(img, corners, ids)
        #call the land service. if completed successfully it return a boolean true
        tag_located=True        
        
    cv.imshow("face and tag Detect Stream", img)
    if(tag_located):
        if(tag_detect_action(request)):
            print("drone land completed successfully.")
    #delay 10 ms and when q is pressed shutdown the node
    if cv.waitKey(10) & 0xFF==ord('q'):
        rospy.signal_shutdown("End node")
    
if __name__=="__main__":
        rospy.init_node("detect_face_tag_action")
        rospy.Subscriber(image_topic, Image, detect_face_tag)
        rospy.spin()
        