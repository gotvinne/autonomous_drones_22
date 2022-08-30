//  Copyright (c) Introduction to ROS 2022 TUM
#include <ros/ros.h>
#include <std_msgs/String.h>

#include <vector>
#include <string>
#include <memory>

#include "unity_stream_parser.h"
#include "rgb_camera_parser.h"
#include "depth_camera_parser.h"
#include "fisheye_camera_parser.h"
#include "imu_parser.h"
#include "true_state_parser.h"
#include "unity_command_stream.h"

#include <fla_utils/param_utils.h>

/*
This ROS node defines the communication from Unity to ros through an IP port UDP
*/

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "unity_ros");
  ros::NodeHandle n;
  
  ros::NodeHandle pnh("~");
  std::string robot_name, unity_port;
	fla_utils::StringGetParam(pnh, "robot_name", robot_name);
  fla_utils::StringGetParam(pnh, "unity_port", unity_port);

  ROS_INFO("Starting TCPStreamReader");
  TCPStreamReader stream_reader("127.0.0.1", unity_port);
  ROS_INFO("Waiting for connection for drone ...");
  stream_reader.WaitConnect();
  ROS_INFO("Got a connection to drone...");

  IMUParser imu_parser;
  //UnityCommandStream command_stream("127.0.0.1", "9999");

  std::vector<std::shared_ptr<UnityStreamParser>> stream_parsers(UnityMessageType::MESSAGE_TYPE_COUNT);

  stream_parsers[UnityMessageType::UNITY_STATE] = std::make_shared<TrueStateParser>();
  stream_parsers[UnityMessageType::UNITY_IMU] = std::make_shared<IMUParser>();
  stream_parsers[UnityMessageType::UNITY_CAMERA] = std::make_shared<RGBCameraParser>();
  stream_parsers[UnityMessageType::UNITY_DEPTH] = std::make_shared<DepthCameraParser>();
  stream_parsers[UnityMessageType::UNITY_FISHEYE] = std::make_shared<FisheyeCameraParser>();

  while (stream_reader.Good() && ros::ok()) { 
    uint32_t magic = stream_reader.ReadUInt();

    if(magic == 0xDEADC0DE) {
      double ros_time = ros::Time::now().toSec();

      UnityHeader header;
      header.type = static_cast<UnityMessageType>(stream_reader.ReadUInt());
      uint64_t timestamp_raw = stream_reader.ReadUInt64();
      header.timestamp = static_cast<double>(timestamp_raw) * 1e-7;
      header.name =   stream_reader.ReadString();
      //ROS_ERROR("HEADER 1: %s", header_1.name.c_str());

      if(header.type < UnityMessageType::MESSAGE_TYPE_COUNT) {
        stream_parsers[header.type]->ParseMessage(header, stream_reader);
      }

    } else {
      ROS_ERROR("Stream 1 corrupted, could not parse unity message");
    }

    ros::spinOnce();
  }

  return 0;
}
