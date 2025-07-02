#!/usr/bin/env python
import cv2 as cv
import rospy
import sensor_msgs.msg
import cv_bridge as cvb
import numpy

#object to convert ros image to cv image
br = cvb.CvBridge()

image_topic = "/ardrone/front/image_raw"

#callback function for each frame 
def ros_img_to_cv(imgmsg):
    img = br.imgmsg_to_cv2(imgmsg, "bgr8")
    cv.imshow("Image", img)
    
    #wait 10 ms
    cv.waitKey(10)
    
if __name__=='__main__':
    rospy.init_node("ros_img_to_cv")
    rospy.Subscriber(image_topic, sensor_msgs.msg.Image, ros_img_to_cv)
    rospy.spin()