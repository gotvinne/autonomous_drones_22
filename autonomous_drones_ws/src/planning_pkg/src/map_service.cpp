#include "ros/ros.h"
#include "nav_msgs/GetMap.h"
#include "nav_msgs/OccupancyGrid.h"

nav_msgs::OccupancyGrid current_grid;

bool getMap(nav_msgs::GetMap::Request &req,
         nav_msgs::GetMap::Response &res) {
  res.map = current_grid;
  return true;
}

void mapUpdater(const nav_msgs::OccupancyGrid& occupancy_msg) {
    current_grid.data = occupancy_msg.data;
    current_grid.header  = occupancy_msg.header;
    current_grid.info = occupancy_msg.info;

    ROS_INFO("Pose updated");
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "add_two_ints_server");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("map", 1000, mapUpdater);
  ros::ServiceServer service = n.advertiseService("getMap", getMap);
  ROS_INFO("Ready to provide map.");
  ros::spin();
  return 0;
}