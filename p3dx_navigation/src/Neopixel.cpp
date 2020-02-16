#include<ros/ros.h>
#include<tf/transform_broadcaster.h>
#include<nav_msgs/Odometry.h>
#include<geometry_msgs/Twist.h>   
#include<geometry_msgs/PoseWithCovarianceStamped.h>
#include<math.h>
#include<stdio.h>
#include<vector>
#include<iostream>
#include<sensor_msgs/Joy.h>
#include "p3dx_navigation/AdaNeopixel.h"
#include <chrono>
#include <thread>

using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

ros::Subscriber sub;
ros::Publisher pub;
int x;

nav_msgs::Odometry odom;
boost::shared_ptr<tf::TransformBroadcaster> odom_broadcaster;
geometry_msgs::TransformStamped odom_trans;

geometry_msgs::Twist cmdvel;
ros::Time odom_stamp;

ros::Time current_time, last_time;

p3dx_navigation::AdaNeopixel LEDmsg;

void controlLED(const geometry_msgs::Twist & msg){  
    
    current_time = ros::Time::now();
    
    if(msg.angular.z<0){
      LEDmsg.ledcommand = {1,0};
    }
    else if(msg.angular.z>0){
      //turn right
      LEDmsg.ledcommand = {0,1};
    }
    else if(msg.linear.x>0){
      //go straight
      LEDmsg.ledcommand = {1,1};
    }
    else if(msg.linear.x==0 && msg.angular.z==0){
      //warning
      LEDmsg.ledcommand = {0,0};
    }

    x=LEDmsg.ledcommand[0];
    ROS_INFO("LEDmsg %i",x);
    
    pub.publish(LEDmsg);
    last_time = ros::Time::now();
    
}


int main(int argc,char **argv) {

  ros::init(argc, argv, "Neopixel");
  ros::NodeHandle prv_nh;
  sub = prv_nh.subscribe("/cmd_vel", 50, &controlLED);
  pub =prv_nh.advertise<p3dx_navigation::AdaNeopixel>("LEDcontrol", 100);
  ros::Rate r(10.0);
  while(ros::ok())
    {  
       ros::spinOnce();    
       r.sleep();
    }
}
