//  Copyright (c) Autonomous drone group 12 

#include "ros/ros.h"
#include "sensor_msgs/PointCloud.h"
#include "sensor_msgs/PointCloud2.h"
#include "sensor_msgs/point_cloud_conversion.h"

#include "point_cloud_converter.h"

PointCloudConverter::PointCloudConverter() {
      ros::NodeHandle pnh("~");
      string_get_param(pnh, "pointcloud_topic_in", topic_sub_);
      string_get_param(pnh, "pointcloud_topic_out", topic_pub_);
    
      sub_ = n_.subscribe(topic_sub_, 1000, &PointCloudConverter::point_cloud_converter, this);
      pub_ = n_.advertise<sensor_msgs::PointCloud>(topic_pub_, 50);
    }

void PointCloudConverter::point_cloud_converter(const sensor_msgs::PointCloud2& pointcloud2) {
    sensor_msgs::PointCloud output;
    sensor_msgs::convertPointCloud2ToPointCloud(pointcloud2, output);
    pub_.publish(output);
    ROS_INFO("CONVERTED POINTCLOUD");
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "convert_from_pointcloud2_to_pointcloud");
    PointCloudConverter converter;
    ROS_INFO("Ready to convert point cloud.");
    ros::spin();
  return 0;
}

