#include <stdint.h>
#include <stdlib.h>  
#include <ros.h>
#include <std_msgs/Float32.h>
#include <sensor_msgs/Joy.h>
#include "geometry_msgs/Twist.h"
#include "p3dx_navigation/AdaNeopixel.h"


ros::NodeHandle  nh;

void lightLED(  const p3dx_navigation::AdaNeopixel & msg)
{    
  nh.loginfo("Things Accepted");
  L        = msg.ledcommand[0];
  R        = msg.ledcommand[1];
  
  digitalWrite(13,L);         
}

ros::Subscriber<p3dx_navigation::AdaNeopixel> sub("/LEDcontrol" , lightLED);

void setup()
{   
  pinMode(13, OUTPUT);
  nh.initNode();
  nh.subscribe(sub);
  delay(100);
      
}

void loop()   {
  
  nh.spinOnce();
  delay(1);
     
}


