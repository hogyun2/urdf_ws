#include "ros/ros.h" // Basic ros header file
#include "test_pkg/test_msg.h"  // Header of Message file. Automatically generate after the build.

int main(int argc, char **argv)
{
	ros::init(argc, argv, "talker"); // Initialization of node name
	ros::NodeHandle nh; // Node handle for communication of ros system

	// declare publisher
	// leverage test_msg.msg defined in test_pkg
	// If you use standard ros message, accordingly use the message
	// topic name: chatter, queue_size = 100
	ros::Publsher chatter_pub = nh.advertise<test_pkg::test_msg>("/chatter",100);

	// set frequency of loop to 10hz, transmit the message, while taking the loop 10 times a second.	
