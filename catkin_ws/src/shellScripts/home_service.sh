#!/bin/sh
xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=/home/workspace/catkin_ws/src/world/my_wall.world " &
sleep 5
xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=/home/workspace/catkin_ws/src/world/wall_map2.yaml" &
sleep 5
xterm  -e  " roslaunch view_navigation.launch" &
sleep 8
xterm  -e  " rosrun add_markers add_markers" &
sleep 3
xterm  -e  " rosrun pick_objects pick_objects"