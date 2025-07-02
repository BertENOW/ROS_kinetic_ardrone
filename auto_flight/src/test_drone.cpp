#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <ctime>


std_msgs::Empty emp_msg;
geometry_msgs::Twist g_msg;
bool done_takeoff=false;
double start_time;
enum takeoff_land{takeoff=0, land};
enum move_dir{left=0, right, up, down};
enum turn{t_left=0, t_right};


// Turn the drone using the cmd_vel topic
void turnLeftOrRight(enum turn l_o_r, ros::Publisher &pub, ros::Rate &r){
    g_msg.linear.x=0.0; g_msg.linear.y=0.0; g_msg.linear.z=0.0;g_msg.angular.x=0.0;
    g_msg.angular.y=0.0; 
    double start = ros::Time::now().toSec();
    float turn_time = 1.0;

    if(l_o_r==left){
        g_msg.angular.z = 2.0;

        while(ros::Time::now().toSec()<start+turn_time){
            
            pub.publish(g_msg);
            ros::spinOnce();
            r.sleep();

        }
    }else if(l_o_r==right){
        g_msg.angular.z = -1.0;
        while(ros::Time::now().toSec()<start+turn_time){
            
            pub.publish(g_msg);
            ros::spinOnce();
            r.sleep();
        }
    }
}

void takeOffLand(enum takeoff_land torl,ros::Publisher &pub, ros::Rate &r){    
    g_msg.linear.x=0.0;
    g_msg.linear.y=0.0;
    g_msg.linear.z=0.0;
    g_msg.angular.x=0.0;
    g_msg.angular.y=0.0;
    g_msg.angular.z=0.0;
    double start=ros::Time::now().toSec();
    float take_off_time=3, hover_time=2, land_time=5;
 
    if(torl==takeoff ){

        ROS_INFO("Taking Off");       
        while(ros::Time::now().toSec()<start+take_off_time ){;
            pub.publish(emp_msg);
            ros::spinOnce();
            r.sleep();
        }
        
              
    }else{
        ROS_INFO("Landing now"); 
        start=(double)ros::Time::now().toSec();
        while(ros::Time::now().toSec()<start+land_time){
            pub.publish(emp_msg);
            ros::spinOnce();
            r.sleep();
        }
    }
}

void move(enum move_dir dir, ros::NodeHandle &n, ros::Publisher &pub, ros::Rate &r){
    g_msg.linear.x=0.0;
    g_msg.linear.y=0.0;
    g_msg.linear.z=0.0;
    g_msg.angular.x=0.0;
    g_msg.angular.y=0.0;
    g_msg.angular.z=0.0;
    switch(dir){
        case left:{
            g_msg.linear.y=+2.0;
            ROS_INFO("Flyin up");
            while(ros::Time::now().toSec()<start_time+3.0){
                pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
                pub.publish(g_msg);
                ros::spinOnce();
                r.sleep();
            }
            break;
        }
        case right:{
            g_msg.linear.y=-2.0;
            ROS_INFO("Going right");
            while(ros::Time::now().toSec()<start_time+3.0){
                pub.publish(g_msg);
                pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
                pub.publish(g_msg);
                ros::spinOnce();
                r.sleep();
            }
            break;
            
        }
        case up:{
            g_msg.linear.z=+2.0;
            ROS_INFO("Going up");
            while(ros::Time::now().toSec()<start_time+3.0){
                pub.publish(g_msg);
                pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
                pub.publish(g_msg);
                ros::spinOnce();
                r.sleep();
            }
            break;
        }
        case down:{
            g_msg.linear.z = -2.0;
            ROS_INFO("Going Down");
            while(ros::Time::now().toSec()<start_time+3.0){
                pub.publish(g_msg);
                pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 10);
                pub.publish(g_msg);
                ros::spinOnce();
                r.sleep();
            }
            break;
        }

    }
}

void hover(ros::Publisher &pub, ros::Rate &r){
    g_msg.linear.x=0.0;
    g_msg.linear.y=0.0;
    g_msg.linear.z=0.0;
    g_msg.angular.x=0.0;
    g_msg.angular.y=0.0;
    g_msg.angular.z=0.0;
    double start=ros::Time::now().toSec();
    float hover_time=1;
    ROS_INFO("Hovering");
    while(ros::Time::now().toSec()<start+hover_time){
        pub.publish(g_msg);
        ros::spinOnce();
        r.sleep();
    }    
}

int main(int argc, char**argv){
    ros::init(argc, argv, "test_drone");
    ros::NodeHandle n;
    ros::Rate rate(1);
    ros::Publisher toff_pub= n.advertise<std_msgs::Empty>("/ardrone/takeoff", 1);
    ros::Publisher land_pub= n.advertise<std_msgs::Empty>("/ardrone/land", 1);
    ros::Publisher twist_pub  = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
    int do_exit = 0;
    
    while(ros::ok()){
        //last=now;
        takeOffLand(takeoff, toff_pub, rate);
        turnLeftOrRight(t_left, twist_pub, rate);
        hover(twist_pub, rate);

        if(do_exit){
            ROS_INFO("Exiting");
            exit(0);
        }else do_exit++;
        //done_takeoff=true;
        //move(up, n, p, rate);
        //move(left, n, p, rate);
        //move(right, n, p, rate);
        //move(up, n, p, rate);
        //move(down, n, p, rate);
        //takeOffLand(land, land_pub, rate);
    } 
    

}