
// Copyright (c) Autonomous Drone group 12
#include <ros/ros.h>
#include <string>
#include "sensor_msgs/PointCloud2.h"

class PointCloudMerger {
    private:
    ros::NodeHandle n_;
    ros::Subscriber drone_1_sub_;
    ros::Subscriber drone_2_sub_;
    ros::Publisher pub_;

    std::string topic_1_sub_ = "drone_1/camera/pointcloud";
    std::string topic_2_sub_ = "drone_2/camera/pointcloud";
    std::string topic_pub_ = "pointclouds";
    
    public:
    void pointcloud_merger(const sensor_msgs::PointCloud2& pointcloud);

    PointCloudMerger() {
        drone_1_sub_ = n_.subscribe(topic_1_sub_, 1000, &PointCloudMerger::pointcloud_merger, this);
        drone_2_sub_ = n_.subscribe(topic_2_sub_, 1000, &PointCloudMerger::pointcloud_merger, this);
        pub_ = n_.advertise<sensor_msgs::PointCloud2>(topic_pub_, 50);
    }
};  