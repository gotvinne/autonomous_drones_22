// Copyright (c) 2022, Autonomous Drones Group 12
#include <state_machine.h>

#include <ros/ros.h>
#include <ros/console.h>

#include <tf/transform_datatypes.h>
#include <tf_conversions/tf_eigen.h>
#include <tf/transform_broadcaster.h>
#include <eigen_conversions/eigen_msg.h>
#include <mav_msgs/Actuators.h>
#include <nav_msgs/Odometry.h>
#include <trajectory_msgs/MultiDOFJointTrajectoryPoint.h>
#include <math.h>
#include <std_msgs/Float64.h>

#include <eigen3/Eigen/Dense>

StateMachineNode::StateMachineNode() {
    ros::NodeHandle pnh("~");

    string_get_param(pnh, "robot_name", robot_name_);

    std::string initial_x, initial_y, initial_z;
    double x, y, z;
    string_get_param(pnh, "initial_x", initial_x);
    string_get_param(pnh, "initial_y", initial_y);
    string_get_param(pnh, "initial_z", initial_z);

    x = std::stoi(initial_x);
    y = std::stoi(initial_y);
    z = std::stoi(initial_z);

    origin_ = tf::Vector3(x, y, z);
    
    // Define topic to interface controller
    desired_state_pub_ = nh_.advertise<trajectory_msgs::MultiDOFJointTrajectoryPoint>(topic_ds_, 1);
    current_state_sub_ = nh_.subscribe(topic_cs_, 1, &StateMachineNode::cs_callback, this);
    cmd_vel_sub_ = nh_.subscribe(topic_cv_, 1000, &StateMachineNode::cv_callback, this);
                                  
    state_machine_timer_ = nh_.createTimer(ros::Duration(sim_interval_),
    &StateMachineNode::state_machine_loop, this);
  }

void StateMachineNode::state_machine_loop(const ros::TimerEvent& t) {
    if (state_ == State::takeoff) { takeoff(); }
    else if (state_ == State::hover) { hover(); }
    else if (state_ == State::explore) { explore();}
    else if (state_ == State::landing) { landing();}
}

void StateMachineNode::takeoff() {
  ROS_INFO_ONCE("Status update--> 1- I am taking off drone %s", robot_name_.c_str());
  tf::Vector3 pos(origin_.getX(), origin_.getY(), takeoff_height_);
  tf::Quaternion q;
  q.setRPY(0, 0, 0);
  set_waypoint(pos, q);

  if (in_range(takeoff_height_-tol_, takeoff_height_+tol_, pos_[2])) { 
    state_ = State::hover;
    set_hover_pos();
  }
}

void StateMachineNode::hover() {
    ROS_INFO_ONCE("Status update--> 2- Hovering drone %s", robot_name_.c_str());
    tf::Vector3 pos(hover_pos_[0], hover_pos_[1], hover_pos_[2]);
    tf::Quaternion q;
    q.setRPY(0, 0, 0);

    set_waypoint(pos, q);

    if (ros::Duration(5.0).sleep()) {
      state_ = State::explore;
    } // Sleep for 3 seconds before starting to explore
}

void StateMachineNode::landing() { // enter hover state before we can land
    ROS_INFO_ONCE("Status update--> 4- Landing drone %s", robot_name_.c_str());
    tf::Vector3 pos(hover_pos_[0], hover_pos_[1], 0); 
    tf::Quaternion q;
    q.setRPY(0, 0, 0);
    set_waypoint(pos, q);

    if (in_range(-tol_, tol_, pos_[2])) { 
      state_ = State::hover;
      set_hover_pos();
    }
}

void StateMachineNode::explore() {
  ROS_INFO_ONCE("Status update--> 3- Starting to explore drone %s", robot_name_.c_str());
  tf::Vector3 pos = twist_to_pos(cmd_twist_);
  tf::Quaternion q = twist_to_quat(cmd_twist_);
  
  tf::Vector3 vel_lin(cmd_twist_.linear.x, cmd_twist_.linear.y, cmd_twist_.linear.z);
  tf::Vector3 vel_ang(cmd_twist_.angular.x, cmd_twist_.angular.y, cmd_twist_.angular.z);

  // Need to transform for controller
  tf::Transform body_to_world_tf(tf::Transform::getIdentity());
  body_to_world_tf.setRotation(quat_);
  vel_lin = body_to_world_tf * vel_lin;

  set_waypoint(pos, q, vel_lin, vel_ang);
}  

tf::Vector3 StateMachineNode::twist_to_pos(geometry_msgs::Twist twist) {
  tf::Vector3 current_pos = tf::Vector3(pos_[0], pos_[1], takeoff_height_);
  tf::Vector3 delta_pos = tf::Vector3(sim_interval_ * vel_to_pos_scale_ * twist.linear.x, 
                         sim_interval_ * vel_to_pos_scale_ * twist.linear.y, 0);

  tf::Transform body_to_world_tf(tf::Transform::getIdentity());
  body_to_world_tf.setRotation(quat_);

  delta_pos = body_to_world_tf * delta_pos;

  return current_pos + delta_pos;
}

tf::Quaternion StateMachineNode::
twist_to_quat(geometry_msgs::Twist twist) {
  tf::Quaternion rot;
  // Set desired rotation
  // Only Yaw is important for the controller
  rot.setRPY(0, 0, yaw_ + (twist.angular.z * sim_interval_ * vel_to_quat_scale_));
  return rot.normalize();
}

void StateMachineNode::cv_callback(geometry_msgs::Twist cmd_vel) {
  cmd_twist_.angular.x = cmd_vel.angular.x;
  cmd_twist_.angular.y = cmd_vel.angular.y;
  cmd_twist_.angular.z = cmd_vel.angular.z;

  cmd_twist_.linear.x = cmd_vel.linear.x;
  cmd_twist_.linear.y = cmd_vel.linear.y;
  cmd_twist_.linear.z = cmd_vel.linear.z;
}

void StateMachineNode::cs_callback(
    const nav_msgs::Odometry& cur_state) {

    pos_ << cur_state.pose.pose.position.x,
        cur_state.pose.pose.position.y,
        cur_state.pose.pose.position.z;
    vel_ << cur_state.twist.twist.linear.x,
         cur_state.twist.twist.linear.y,
         cur_state.twist.twist.linear.z;
    omega_ << cur_state.twist.twist.angular.x,
             cur_state.twist.twist.angular.y,
             cur_state.twist.twist.angular.z;

    tf::quaternionMsgToTF(cur_state.pose.pose.orientation, quat_);
    yaw_ = tf::getYaw(quat_);
}

void StateMachineNode::set_waypoint(tf::Vector3 pos, tf::Quaternion q,
 tf::Vector3 lin_vel, tf::Vector3 ang_vel, tf::Vector3 lin_acc) {
  tf::Transform desired_pos(tf::Transform::getIdentity());
  geometry_msgs::Twist vel;
  geometry_msgs::Twist acc;

  // WAYPOINT INITIALIZATION. 
  // Setting desired position and orientation
  desired_pos.setOrigin(pos);  //  Setting desired point
  desired_pos.setRotation(q);

   // Defining angular and linear velocity
  vel.linear.x = lin_vel.getX();
  vel.linear.y = lin_vel.getY();
  vel.linear.z = lin_vel.getZ();

  vel.angular.x = ang_vel.getX();
  vel.angular.y = ang_vel.getY();
  vel.angular.z = ang_vel.getZ();

  // Defining linear acceleration
  acc.linear.x = lin_acc.getX();
  acc.linear.y = lin_acc.getY();
  acc.linear.z = lin_acc.getZ();

  //  Making a message to send to rotors
  trajectory_msgs::MultiDOFJointTrajectoryPoint msg;
  msg.transforms.resize(1);
  msg.transforms[0].translation.x = desired_pos.getOrigin().x();
  msg.transforms[0].translation.y = desired_pos.getOrigin().y();
  msg.transforms[0].translation.z = desired_pos.getOrigin().z();
  msg.transforms[0].rotation.x = desired_pos.getRotation().getX();
  msg.transforms[0].rotation.y = desired_pos.getRotation().getY();
  msg.transforms[0].rotation.z = desired_pos.getRotation().getZ();
  msg.transforms[0].rotation.w = desired_pos.getRotation().getW();

  msg.velocities.resize(1);
  msg.velocities[0] = vel;
  msg.accelerations.resize(1);
  msg.accelerations[0] = acc;

  desired_state_pub_.publish(msg);

  br.sendTransform(tf::StampedTransform(desired_pos, ros::Time::now(),
                                        "world", robot_name_ + "/av-desired"));

  // Make a transform of current pose without pitch and roll to use for the local costmap
  tf::Transform local_costmap_pos(tf::Transform::getIdentity());
  tf::Quaternion rot;
  tf::Vector3 position = tf::Vector3(pos_[0], pos_[1], pos_[2]);
  rot.setRPY(0.0, 0.0, yaw_);
  rot.normalize();
  
  local_costmap_pos.setOrigin(position);
  local_costmap_pos.setRotation(rot);

  br.sendTransform(tf::StampedTransform(local_costmap_pos, ros::Time::now(),
                                        "world", robot_name_ + "/local_costmap_pos"));

}

bool StateMachineNode::in_range(double low, double high, double x) { 
  return ((x-high)*(x-low) <= 0);
}

void StateMachineNode::set_hover_pos() {
  hover_pos_ << pos_[0], pos_[1], pos_[2];
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "state_machine");
    ROS_INFO_ONCE("State machine spawned.");
    StateMachineNode smn;
    ros::spin();
}
