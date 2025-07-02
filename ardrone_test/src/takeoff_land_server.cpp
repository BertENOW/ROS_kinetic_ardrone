#include <ros/ros.h>
#include "std_msgs/Empty.h"
#include "geometry_msgs/Twist.h"
#include "actionlib/server/simple_action_server.h"
#include "ardrone_test/TakeoffLandAction.h"

class TakeoffLandAction{
protected:
    ros::NodeHandle n;
    actionlib::SimpleActionServer<ardrone_test::TakeoffLandAction> as;
    std::string action_name;
    std_msgs::Empty empty_msg;
    geometry_msgs::Twist geo_msg;
    ardrone_test::TakeoffLandFeedback feedback;
    ardrone_test::TakeoffLandResult result;

public:
    TakeoffLandAction(std::string name):as(n, name, boost::bind(&TakeoffLandAction::executeCB, this, _1), false),
    action_name(name){
        as.start();
    } 
    ~TakeoffLandAction(void){}
    void executeCB(const ardrone_test::TakeoffLandGoalConstPtr &goal);

};

void TakeoffLandAction::executeCB(const ardrone_test::TakeoffLandGoalConstPtr &goal){
    ros::NodeHandle n;
    ros::Publisher pub;
    ros::Rate r(1);
    double start_time=ros::Time::now().toSec();
    float process_time=4;
    geo_msg.linear.x=geo_msg.linear.y=geo_msg.linear.z=0;
    geo_msg.angular.x=geo_msg.angular.y=geo_msg.angular.z=0;
    bool success=true;

    ROS_INFO_STREAM(action_name<<": Executing takeoff or land");
    if(goal->takeoff_land==1){
        ROS_INFO("Starting take drone off");
        pub=n.advertise<std_msgs::Empty>("/ardrone/takeoff", 1);
        while(ros::Time::now().toSec()<start_time+process_time){ 
            if(as.isPreemptRequested() || !ros::ok()){              //
            ROS_INFO_STREAM(action_name<<": Preempted");
            as.setPreempted();
            success=false;
            break;
            }
            pub.publish(empty_msg);
            feedback.progress=true;
            as.publishFeedback(feedback);
            ros::spinOnce();
            r.sleep();
        }
        ROS_INFO("Drone takeoff completed");
    }else if(goal->takeoff_land==0){
        ROS_INFO("Starting to land drone");
        pub=n.advertise<std_msgs::Empty>("/ardrone/land", 1);
        while(ros::Time::now().toSec()<start_time+process_time){ 
            if(as.isPreemptRequested() || !ros::ok()){              //
            ROS_INFO_STREAM(action_name<<": Preempted");
            as.setPreempted();
            success=false;
            break;
            }
            pub.publish(empty_msg);
            feedback.progress=true;
            as.publishFeedback(feedback);
            ros::spinOnce();
            r.sleep();
        }
        ROS_INFO("Drone landing completed");

    }else{
        ROS_INFO("Action server usage: 0=land drone, 1=takeoff drone");
    }

    if(success){
        result.done=true;
        ROS_INFO_STREAM(action_name<<"Successful");
        as.setSucceeded(result);
    }else{
        result.done=false;
        ROS_INFO_STREAM(action_name<<"Failed");
        as.setSucceeded(result);
    }

}

int main(int argc, char **argv){
    ros::init(argc, argv, "takeoff_land_server");
    TakeoffLandAction("takeoff_land");
    ROS_INFO("Server started");
    ros::spin();
    return 0;
}