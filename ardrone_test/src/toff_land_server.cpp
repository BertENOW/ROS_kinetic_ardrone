#include <ros/ros.h>
#include "std_msgs/Empty.h"
#include "ardrone_test/TakeoffLandService.h"

bool takeoff_and(ardrone_test::TakeoffLandService::Request &req, 
                 ardrone_test::TakeoffLandService::Response &res){
    ros::NodeHandle n;
    ros::Publisher pub;
    std_msgs::Empty emp_msg;
    double start_time;
    float process_time=4;
    ros::Rate r(1);
    
    if(req.toff_land==1){
        start_time = ros::Time::now().toSec();
        ROS_INFO_STREAM("Starting drone takeoff");
        pub = n.advertise<std_msgs::Empty>("/ardrone/takeoff", 1);
        //publish takeoff command for 4 seconds
        while(ros::ok() && ros::Time::now().toSec()<start_time+process_time){
            pub.publish(emp_msg);
            ros::spinOnce();
            r.sleep();
        }
        res.success=true;
        ROS_INFO_STREAM("Takeoff complete");
        return true;
    }else if(req.toff_land==0){
        start_time = ros::Time::now().toSec();
        ROS_INFO_STREAM("Starting to land drone");
        pub = n.advertise<std_msgs::Empty>("/ardrone/land", 1);
        //publish takeoff command for 4 seconds
        while(ros::ok() && ros::Time::now().toSec()<start_time+process_time){
            pub.publish(emp_msg);
            ros::spinOnce();
            r.sleep();
        }
        res.success=true;
        ROS_INFO_STREAM("Land complete");
        return true;

    }

}

int main(int argc, char **argv){
    ros::init(argc, argv, "toff_land_server");
    ros::NodeHandle n;
    ros::ServiceServer service = n.advertiseService("toff_land_service", takeoff_and);
    ROS_INFO("Ready to takeoff or land");
    ros::spin();
    return 0;
}