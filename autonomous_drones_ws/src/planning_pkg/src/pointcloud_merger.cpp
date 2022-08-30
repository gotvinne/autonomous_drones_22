//  Copyright (c) Autonomous drone group 12 

#include "ros/ros.h"
#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/point_cloud_conversion.h"

#include "pointcloud_merger.h"

void PointCloudMerger::pointcloud_merger(const sensor_msgs::PointCloud2& pointcloud) {
    pub_.publish(pointcloud);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "merge_pointclouds");
    PointCloudMerger merger;
    ROS_INFO("Ready to merge pointclouds.");
    ros::spin();
  return 0;
}