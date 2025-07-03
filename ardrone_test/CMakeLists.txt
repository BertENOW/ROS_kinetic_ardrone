cmake_minimum_required(VERSION 3.0.2)
project(ardrone_test)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  actionlib
  actionlib_msgs
  ardrone_autonomy
  geometry_msgs
  roscpp
  rospy
  std_msgs
  message_generation
)

## System dependencies are found with CMake's conventions
find_package(Boost REQUIRED COMPONENTS system)
find_package(OpenCV)


## Generate messages in the 'msg' folder
# add_message_files(
#   FILES
#   Message1.msg
#   Message2.msg
# )

## Generate services in the 'srv' folder
add_service_files(
  FILES
  TakeoffLandService.srv
)

## Generate actions in the 'action' folder
add_action_files(
  DIRECTORY action
  FILES TakeoffLand.action
)

## Generate added messages and services with any dependencies listed here
generate_messages(
  DEPENDENCIES
  actionlib_msgs   geometry_msgs   std_msgs
)



catkin_package(
  INCLUDE_DIRS include 
  LIBRARIES ardrone_test
  CATKIN_DEPENDS actionlib actionlib_msgs ardrone_autonomy geometry_msgs roscpp rospy std_msgs
#  DEPENDS system_lib
)


## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
include ${catkin_INCLUDE_DIRS} ${Boost_INCLUDE_DIR} ${OpenCV_INCLUDE_DIRS}
)

#Add python scripts here. Don't forget to make them executable with chmod
catkin_install_python( PROGRAMS scripts/face_detect.py scripts/img_process.py 
scripts/face_detect_stream.py scripts/convert_ros_cv.py scripts/ros_face_detect.py
scripts/generate_tags.py scripts/detect_tags.py scripts/detect_face_tag_action.py
DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

add_executable(takeoff_land_server src/takeoff_land_server.cpp)
target_link_libraries(takeoff_land_server ${catkin_LIBRARIES})
add_dependencies(takeoff_land_server ${ardrone_test_EXPORTED_TARGETS})

add_executable(takeoff_land_client src/takeoff_land_client.cpp)
target_link_libraries(takeoff_land_client ${catkin_LIBRARIES})
add_dependencies(takeoff_land_client ${ardrone_test_EXPORTED_TARGETS})

add_executable(toff_land_server src/toff_land_server.cpp)
target_link_libraries(toff_land_server ${catkin_LIBRARIES})
add_dependencies(toff_land_server ardrone_test_gencpp)

add_executable(toff_land_client src/toff_land_client.cpp)
target_link_libraries(toff_land_client ${catkin_LIBRARIES})
add_dependencies(toff_land_client ardrone_test_gencpp)