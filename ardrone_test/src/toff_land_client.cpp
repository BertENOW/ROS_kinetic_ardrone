#include <ros/ros.h>
#include "ardrone_test/TakeoffLandService.h"
#include <cstdlib>

int main(int argc, char **argv){
    ros::init(argc, argv, "takeoff_land_client");
    if(argc !=2){
        ROS_INFO_STREAM("Usage: toff_land_client X");
        return 1;
    }
    ros::NodeHandle n;
    ros::ServiceClient client = n.serviceClient<ardrone_test::TakeoffLandService>("toff_land_service");
    ardrone_test::TakeoffLandService srv;
    srv.request.toff_land = atoi(argv[1]);
    
    if(client.call(srv)){
        ROS_INFO_STREAM("Result: "<<srv.response.success);
    }else{
        ROS_ERROR("Failed to call service add_two_ints");
    }
}