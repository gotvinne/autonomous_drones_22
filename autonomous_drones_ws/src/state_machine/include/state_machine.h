// Copyright (c) 2022, Autonomous Drones Group 12

#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <ros/ros.h>
#include <ros/console.h>

#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
#include <mav_msgs/Actuators.h>
#include <nav_msgs/Odometry.h>
#include <trajectory_msgs/MultiDOFJointTrajectoryPoint.h>
#include <math.h>
#include <std_msgs/Float64.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include <eigen3/Eigen/Dense>

#define PI M_PI

// Constants
const tf::Vector3 zero_vec(0, 0, 0);

enum class State {
takeoff,
 hover,
 explore,
 landing
};

class StateMachineNode {
 private:
  ros::NodeHandle nh_;
  std::string robot_name_;
  
  // State machine interfaces
  ros::Subscriber cmd_vel_sub_, current_state_sub_;
  tf::TransformBroadcaster br;

  // Controller interface
  ros::Publisher desired_state_pub_;
  geometry_msgs::Twist cmd_twist_;

  // Loop logic
  ros::Time start_ = ros::Time::now();
  State state_ = State::takeoff;
  ros::Timer state_machine_timer_;

  // Drone state:
  Eigen::Vector3d pos_, vel_, omega_;
  tf::Quaternion quat_;
  double roll_ = 0.0, pitch_ = 0.0, yaw_ = 0.0;
  tf::Vector3 origin_;
  Eigen::Vector3d hover_pos_;
  
  // State machine constants
  const float takeoff_height_ = 5.0;
  const float sim_interval_ = 0.1;
  const double tol_ = 0.5;
  const float vel_to_pos_scale_ = 1.0;
  const float vel_to_quat_scale_ = 1.0;

  // Topics
  const std::string topic_ds_= "desired_state";
  const std::string topic_cs_= "current_state_est";
  const std::string topic_cv_= "cmd_vel";

 public:
  StateMachineNode();

  // Callbacks:
  void cs_callback(const nav_msgs::Odometry& current_state);
  void cv_callback(geometry_msgs::Twist cmd_vel);

  // Setting waypoint to controller
  void set_waypoint(tf::Vector3 pos, tf::Quaternion q,
   tf::Vector3 lin_vel = zero_vec, tf::Vector3 ang_vel = zero_vec,
    tf::Vector3 lin_acc = zero_vec);
  
  bool in_range(double low, double high, double x);
  void set_hover_pos();
  tf::Vector3 twist_to_pos(geometry_msgs::Twist twist);
  tf::Quaternion twist_to_quat(geometry_msgs::Twist twist);
  void rotate_z(tf::Vector3& vec, const double yaw);

  // Task functions:
  void state_machine_loop(const ros::TimerEvent& t);
  void takeoff();
  void hover();
  void landing();
  void explore();
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

#endif  //  STATE_MACHINE_H
