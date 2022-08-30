// Copyright (c) Autonomous Drone group 12
#include <ros/ros.h>
#include <string>
#include "sensor_msgs/PointCloud.h"

class PointCloudConverter {
    private:
    ros::NodeHandle n_;
    ros::Subscriber sub_;
    ros::Publisher pub_;

    std::string topic_sub_;
    std::string topic_pub_;
    
    public:
    void point_cloud_converter(const sensor_msgs::PointCloud2& pointcloud2);

    PointCloudConverter();
};  

bool string_get_param(ros::NodeHandle &nh,
                         std::string const& param_name, std::string& param_value) {
  int param_value_int;
  double param_value_double;
  bool param_value_bool;
  std::string param_value_string;
  
  if(nh.getParam(param_name, param_value_int)) {
  	param_value = std::to_string(param_value_int);
	return true;
  } else if(nh.getParam(param_name, param_value_double)) {
  	param_value = std::to_string(param_value_double);
	return true;
  } if(nh.getParam(param_name, param_value_bool)) {
  	param_value = param_value_bool ? "true" : "false";
	return true;
  } else if(nh.getParam(param_name, param_value_string)) {
  	param_value = param_value_string;
	return true;
  } else {
	ROS_ERROR("Failed to find parameter: %s", nh.resolveName(param_name, true).c_str());
	return false;
  }
}