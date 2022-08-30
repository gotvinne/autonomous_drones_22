// Copyright Introduction to ROS TUM 2022

#include <ros/ros.h>
#include <ros/console.h>

#include <tf/transform_datatypes.h>
#include <tf_conversions/tf_eigen.h>
#include <eigen_conversions/eigen_msg.h>
#include <mav_msgs/Actuators.h>
#include <nav_msgs/Odometry.h>
#include <trajectory_msgs/MultiDOFJointTrajectoryPoint.h>
#include <math.h>
#include <std_msgs/Float64.h>


#define PI M_PI

#include <eigen3/Eigen/Dense>
/*
Node defining a geometric controller for a drone
*/

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

class controllerNode{
  ros::NodeHandle nh;

  ros::Subscriber desired_state, current_state;
  ros::Publisher prop_speeds;
  ros::Timer timer;
  std::string robot_name_;

  // Topics
  const std::string topic_ds_ = "desired_state";
  const std::string topic_cs_ ="current_state_est";
  std::string topic_rsc_;

  // Controller parameters
  double kx, kv, kr, komega; 
  double m, g, d;        // mass, gravity, distance from center to propeller
  double cf, cd;             // Propeller coefficients
    
  Eigen::Matrix3d J;     // Inertia Matrix
  Eigen::Vector3d e3;    // [0,0,1]
  Eigen::MatrixXd F2W;   // Wrench-rotor speeds map

  // Current state
  Eigen::Vector3d x;     // current position of the UAV's c.o.m. in the world frame
  Eigen::Vector3d v;     // current velocity of the UAV's c.o.m. in the world frame
  Eigen::Matrix3d R;     // current orientation of the UAV
  Eigen::Vector3d omega; // current angular velocity of the UAV's c.o.m. in the *body* frame

  // Desired state
  Eigen::Vector3d xd;    // desired position of the UAV's c.o.m. in the world frame
  Eigen::Vector3d vd;    // desired velocity of the UAV's c.o.m. in the world frame
  Eigen::Vector3d ad;    // desired acceleration of the UAV's c.o.m. in the world frame
  double yawd;           // desired yaw angle

  double hz;             // frequency of the main control loop

  static Eigen::Vector3d Vee(const Eigen::Matrix3d& in) {
    Eigen::Vector3d out;
    out << in(2, 1), in(0, 2), in(1, 0);
    return out;
  }

  static double signed_sqrt(double val) {
    return val > 0?sqrt(val):-sqrt(-val);
  }

 public:
  controllerNode() : e3(0, 0, 1), F2W(4, 4), hz(1000.0) {
      ros::NodeHandle pnh("~");
      string_get_param(pnh, "robot_name", robot_name_);
      topic_rsc_ = "rotor_speed_cmds";
 
      desired_state = nh.subscribe(topic_ds_, 1, &controllerNode::onDesiredState, this);
      current_state = nh.subscribe(topic_cs_, 1, &controllerNode::onCurrentState, this);
      prop_speeds = nh.advertise<mav_msgs::Actuators>(topic_rsc_, 1);
  

      ROS_INFO_ONCE("Initialized controller for %s", robot_name_.c_str());
      timer = nh.createTimer(ros::Rate(hz), &controllerNode::controlLoop, this);
      
      // Controller gains
      kx = 12.7;
      kv = 5.8;
      kr = 8.8;
      komega = 1.15;

      // Initialize constants
      m = 1.0;
      cd = 1e-5;
      cf = 1e-3;
      g = 9.81;
      d = 0.3;
      J << 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0;
  }

  void onDesiredState(const trajectory_msgs::MultiDOFJointTrajectoryPoint& des_state) {
      geometry_msgs::Vector3 t = des_state.transforms[0].translation;
      xd << t.x, t.y, t.z;
      // ROS_INFO_NAMED("onDesiredState", "POS: %f %f %f", t.x, t.y, t.z);

      geometry_msgs::Vector3 v = des_state.velocities[0].linear;
      vd << v.x, v.y, v.z;
      // ROS_INFO_NAMED("onDesiredState", "VEL: %f %f %f", v.x, v.y, v.z);

      geometry_msgs::Vector3 a = des_state.accelerations[0].linear;
      ad << a.x, a.y, a.z;
      // ROS_INFO_NAMED("onDesiredState", "ACC: %f %f %f", a.x, a.y, a.z);

      tf::Quaternion q;
      tf::quaternionMsgToTF(des_state.transforms[0].rotation , q);
      yawd = tf::getYaw(q);
      // ROS_INFO_NAMED("onDesiredState", "YAW: %f", yawd);
  }

  void onCurrentState(const nav_msgs::Odometry& cur_state) {
      x << cur_state.pose.pose.position.x,cur_state.pose.pose.position.y,cur_state.pose.pose.position.z;
      v << cur_state.twist.twist.linear.x,cur_state.twist.twist.linear.y,cur_state.twist.twist.linear.z;
      omega << cur_state.twist.twist.angular.x,cur_state.twist.twist.angular.y,cur_state.twist.twist.angular.z;
      Eigen::Quaterniond q;
      tf::quaternionMsgToEigen(cur_state.pose.pose.orientation, q);
      R = q.toRotationMatrix();

      // Rotate omega
      omega = R.transpose()*omega;
  }

  void controlLoop(const ros::TimerEvent& t) {
    Eigen::Vector3d ex, ev, er, eomega;
    ex = x - xd;
    ev = v - vd;

    Eigen::Vector3d b_3d = -kx*ex - kv*ev + m*g*e3 + m*ad;
    b_3d.normalize();

    Eigen::Vector3d b_1d(cos(yawd), sin(yawd), 0);
    Eigen::Vector3d b_2d = b_3d.cross(b_1d);
    b_2d.normalize();
    Eigen::Vector3d b_1d_true(b_2d.cross(b_3d));
    b_1d_true.normalize();

    Eigen::Matrix3d Rd;
    Rd << b_1d_true, b_2d, b_3d;
   
    er = 0.5 * Vee(Rd.transpose()*R - R.transpose()*Rd);
    eomega = -omega;
   
    Eigen::Vector3d errs = -kx*ex - kv*ev + m*g*e3 + m*ad;

    double f = errs.dot(R*e3);
    Eigen::Vector3d torques = -kr*er -komega*eomega + omega.cross(J*omega);
    Eigen::Vector4d wrench(f, torques.x(), torques.y(), torques.z());
   
    double d_hat = d/sqrt(2);
    Eigen::Matrix4d F;

    F << cf, cf, cf, cf,
        cf*d_hat, cf*d_hat, -cf*d_hat, -cf*d_hat,
        -cf*d_hat, cf*d_hat, cf*d_hat, -cf*d_hat,
        cd, -cd, cd, -cd;

    Eigen::Vector4d props = F.inverse()*wrench;

    mav_msgs::Actuators msg;
    msg.angular_velocities.resize(4);
    msg.angular_velocities[0] = signed_sqrt(props[0]);
    msg.angular_velocities[1] = signed_sqrt(props[1]);
    msg.angular_velocities[2] = signed_sqrt(props[2]);
    msg.angular_velocities[3] = signed_sqrt(props[3]);
    prop_speeds.publish(msg);
  }
};

int main(int argc, char** argv) {
  ros::init(argc, argv, "controller_node");
  ROS_INFO_ONCE("Controller started.");
  controllerNode n;
  ros::spin();
}
