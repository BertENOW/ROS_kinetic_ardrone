#include <ros/ros.h>
#include "actionlib/client/simple_action_client.h"
#include "actionlib/client/terminal_state.h"
#include "ardrone_test/TakeoffLandAction.h"
#include <cstdlib>

int main(int argc, char**argv){
    if(argc==2){
        ros::init(argc, argv, "takeoff_land_client");
        actionlib::SimpleActionClient<ardrone_test::TakeoffLandAction> ac("takeoff_land", true);
        ROS_INFO("Waiting for server to start");
        ac.waitForServer();
        ROS_INFO("Action started sending goal");
        ardrone_test::TakeoffLandGoal goal;
        goal.takeoff_land = atoi(argv[1]);
        ac.sendGoal(goal);
        bool finished_before_timeout = ac.waitForResult(ros::Duration(20.0));
        if(finished_before_timeout){
            actionlib::SimpleClientGoalState state = ac.getState();
            ROS_INFO_STREAM("Action finished: "<<state.toString());
        }else{
            ROS_INFO("Action did not finish before the time out");
            ac.cancelGoal();
        }
    }else{
        ROS_INFO("Action server usage: 0=land drone, 1=takeoff drone");
    }
}
