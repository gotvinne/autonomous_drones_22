// Copyright (c) Autonomous drone team 12 2022
#include <math.h>

#include <ros/ros.h>
#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/PoseStamped.h>
#include <mav_msgs/Actuators.h>
#include <fla_utils/param_utils.h>

#include "libsocket/inetclientdgram.hpp"
#include "libsocket/exception.hpp"

mav_msgs::Actuators w_msg;
float Arr[4];

class UDPPoseStreamer {
  public:
  
  UDPPoseStreamer(const std::string & udp_address,
                  const std::string & udp_port, 
                  const float x_offset, 
                  const float y_offset) 
  : dgram_client_(LIBSOCKET_IPv4), 
    ip_address_(udp_address), 
    port_(udp_port), 
    nh_("~"),
    x_shift_(x_offset),
    y_shift_(y_offset) {
    global_frame_ = "true_body";
    tf_listener_ptr_ = std::unique_ptr<tf2_ros::TransformListener>(new tf2_ros::TransformListener(tf_buffer_));
    sub_ = nh_.subscribe("pose_topic", 1, &UDPPoseStreamer::PublishPose, this);
  }
  
  virtual ~UDPPoseStreamer() { dgram_client_.destroy(); }
  
  void PublishPose(const mav_msgs::Actuators& msg) {

    float w[4] = {
      static_cast<float>(Arr[0]),
      static_cast<float>(Arr[1]),
      static_cast<float>(Arr[2]),
      static_cast<float>(Arr[3]),
    };
    
    bool accept = true;
    for (uint i=0;i<4;i++) {
      if (std::isnan(w[i])) {
          accept=false;
          break;
      }
    }

    if (accept) {
        static const size_t int32_size = sizeof(uint32_t);
        static const size_t pose_size = sizeof(float) * 4;
        static const size_t packet_size = pose_size;

        uint8_t packet_data[packet_size];
        memcpy(packet_data , &w, pose_size);
        dgram_client_.sndto(&packet_data, packet_size, ip_address_, port_);
    } else {
        std::cout <<"Received nans, not sending! \n";
    }
  }
  ros::Subscriber sub_;
  libsocket::inet_dgram_client dgram_client_;
  tf2_ros::Buffer tf_buffer_;
  std::unique_ptr<tf2_ros::TransformListener> tf_listener_ptr_;

  std::string ip_address_, port_, global_frame_;
  float x_shift_, y_shift_;
  ros::NodeHandle nh_;
};

void wCallback(const mav_msgs::Actuators& cmd) {
  //streamer.PublishPose(msg);
  // print all the remaining numbers
  Arr[0]=cmd.angular_velocities[0];
  Arr[1]=cmd.angular_velocities[1];
  Arr[2]=cmd.angular_velocities[2];
  Arr[3]=cmd.angular_velocities[3];
  
  //std::cout <<"Message received: "<< Arr[0] << " "  << Arr[1] << " "<< Arr [2] << " "  << Arr[3] << " " << "\n";
  return;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "w_to_unity");
  ros::NodeHandle n;
  ros::NodeHandle pnh("~");
  std::string robot_name, unity_port, ip_address;
	fla_utils::StringGetParam(pnh, "robot_name", robot_name);
  fla_utils::StringGetParam(pnh, "unity_port", unity_port);

  ros::Rate loop_rate(1000);

  ip_address="127.0.0.1";  //128.30.10.229";
  float offset_x = 0;
  float offset_y = 0;
  std::cout << "This node enables send communication to Unity\n";
  UDPPoseStreamer streamer(ip_address, unity_port, offset_x, offset_y);

  float counter = 0;
  ros::Subscriber sub = n.subscribe("rotor_speed_cmds", 1, wCallback);

  while (ros::ok()) {
      streamer.PublishPose(w_msg);
      ros::spinOnce();
      loop_rate.sleep();
    }
  return 0;
}
