#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

actionlib::SimpleClientGoalState intendedGoal(move_base_msgs::MoveBaseGoal goal){

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  // set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  // goal.target_pose.header.frame_id = "base_link";
  goal.target_pose.header.stamp = ros::Time::now();

   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  return ac.getState();
  
}




int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  // ros::init(argc, argv, "simple_navigation_goals");
  ros::NodeHandle n;

  move_base_msgs::MoveBaseGoal goal;


  // Define a position and orientation for the pickup point
  goal.target_pose.pose.position.x = 3.42;
  goal.target_pose.pose.position.y = 0;
  goal.target_pose.pose.position.z = 0;

  goal.target_pose.pose.orientation.x = 0;
  goal.target_pose.pose.orientation.y = 0;
  goal.target_pose.pose.orientation.z = -0.70;
  goal.target_pose.pose.orientation.w = 0.71;

  // setting parameter server object at the pickup
  n.setParam("objectAt", "pick");

  // Check if the robot reached PICKUP point
  if( intendedGoal(goal) == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("The base moved to the PICKUP point");
  else
    ROS_INFO("The base failed to move to the PICKUP point");
  
  // sleep after reaching pickup point, simulates object pickup
  sleep(4);//5
  // To delete the visual marker, simulates object has been picked up
  n.setParam("objectAt", "");
  sleep(1);

  // Define a position and orientation for the pickup point
  goal.target_pose.pose.position.x = -0.6;
  goal.target_pose.pose.position.y = -0.05;
  goal.target_pose.pose.position.z = 0;

  goal.target_pose.pose.orientation.x = 0;
  goal.target_pose.pose.orientation.y = 0;
  goal.target_pose.pose.orientation.z = -0.70;
  goal.target_pose.pose.orientation.w = 0.71;

  // Check if the robot reached DROP point
  if( intendedGoal(goal) == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("The base moved to the DROP point");
  else
    ROS_INFO("The base failed to move to the DROP point");
  
  sleep(3);//5
  n.setParam("objectAt", "drop");

  return 0;
}