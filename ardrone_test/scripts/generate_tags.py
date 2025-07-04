#!/usr/bin/env python
import cv2 as cv

# possible april and aruco tags that can be generated
    # "DICT_4X4_50": cv2.aruco.DICT_4X4_50,
	# "DICT_4X4_100": cv2.aruco.DICT_4X4_100,
	# "DICT_4X4_250": cv2.aruco.DICT_4X4_250,
	# "DICT_4X4_1000": cv2.aruco.DICT_4X4_1000,
	# "DICT_5X5_50": cv2.aruco.DICT_5X5_50,
	# "DICT_5X5_100": cv2.aruco.DICT_5X5_100,
	# "DICT_5X5_250": cv2.aruco.DICT_5X5_250,
	# "DICT_5X5_1000": cv2.aruco.DICT_5X5_1000,
	# "DICT_6X6_50": cv2.aruco.DICT_6X6_50,
	# "DICT_6X6_100": cv2.aruco.DICT_6X6_100,
	# "DICT_6X6_250": cv2.aruco.DICT_6X6_250,
	# "DICT_6X6_1000": cv2.aruco.DICT_6X6_1000,
	# "DICT_7X7_50": cv2.aruco.DICT_7X7_50,
	# "DICT_7X7_100": cv2.aruco.DICT_7X7_100,
	# "DICT_7X7_250": cv2.aruco.DICT_7X7_250,
	# "DICT_7X7_1000": cv2.aruco.DICT_7X7_1000,
	# "DICT_ARUCO_ORIGINAL": cv2.aruco.DICT_ARUCO_ORIGINAL,
	# "DICT_APRILTAG_16h5": cv2.aruco.DICT_APRILTAG_16h5,
	# "DICT_APRILTAG_25h9": cv2.aruco.DICT_APRILTAG_25h9,
	# "DICT_APRILTAG_36h10": cv2.aruco.DICT_APRILTAG_36h10,
	# "DICT_APRILTAG_36h11": cv2.aruco.DICT_APRILTAG_36h11

aruco_dict = cv.aruco.getPredefinedDictionary(cv.aruco.DICT_6X6_250)
# april_tag = cv.aruco.getPredefinedDictionary(cv.aruco.DICT_APRILTAG_36H11)

id =34
tag_size = 300 #pixel size

aruco_marker = cv.aruco.generateImageMarker()
# april_tag_marker = cv.generateImageMarker(april_tag, id, tag_size)

# cv.imshow("Aruco marker", aruco_marker)
# cv.imshow("April tag", april_tag)
# cv.waitkey(0)