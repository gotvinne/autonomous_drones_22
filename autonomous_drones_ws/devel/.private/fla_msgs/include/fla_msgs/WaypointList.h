// Generated by gencpp from file fla_msgs/WaypointList.msg
// DO NOT EDIT!


#ifndef FLA_MSGS_MESSAGE_WAYPOINTLIST_H
#define FLA_MSGS_MESSAGE_WAYPOINTLIST_H


#include <string>
#include <vector>
#include <map>

#include <ros/types.h>
#include <ros/serialization.h>
#include <ros/builtin_message_traits.h>
#include <ros/message_operations.h>

#include <std_msgs/Header.h>
#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Float64.h>

namespace fla_msgs
{
template <class ContainerAllocator>
struct WaypointList_
{
  typedef WaypointList_<ContainerAllocator> Type;

  WaypointList_()
    : header()
    , poses()
    , speeds()  {
    }
  WaypointList_(const ContainerAllocator& _alloc)
    : header(_alloc)
    , poses(_alloc)
    , speeds(_alloc)  {
  (void)_alloc;
    }



   typedef  ::std_msgs::Header_<ContainerAllocator>  _header_type;
  _header_type header;

   typedef std::vector< ::geometry_msgs::PoseStamped_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::other >  _poses_type;
  _poses_type poses;

   typedef std::vector< ::std_msgs::Float64_<ContainerAllocator> , typename ContainerAllocator::template rebind< ::std_msgs::Float64_<ContainerAllocator> >::other >  _speeds_type;
  _speeds_type speeds;





  typedef boost::shared_ptr< ::fla_msgs::WaypointList_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::fla_msgs::WaypointList_<ContainerAllocator> const> ConstPtr;

}; // struct WaypointList_

typedef ::fla_msgs::WaypointList_<std::allocator<void> > WaypointList;

typedef boost::shared_ptr< ::fla_msgs::WaypointList > WaypointListPtr;
typedef boost::shared_ptr< ::fla_msgs::WaypointList const> WaypointListConstPtr;

// constants requiring out of line definition



template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const ::fla_msgs::WaypointList_<ContainerAllocator> & v)
{
ros::message_operations::Printer< ::fla_msgs::WaypointList_<ContainerAllocator> >::stream(s, "", v);
return s;
}


template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator==(const ::fla_msgs::WaypointList_<ContainerAllocator1> & lhs, const ::fla_msgs::WaypointList_<ContainerAllocator2> & rhs)
{
  return lhs.header == rhs.header &&
    lhs.poses == rhs.poses &&
    lhs.speeds == rhs.speeds;
}

template<typename ContainerAllocator1, typename ContainerAllocator2>
bool operator!=(const ::fla_msgs::WaypointList_<ContainerAllocator1> & lhs, const ::fla_msgs::WaypointList_<ContainerAllocator2> & rhs)
{
  return !(lhs == rhs);
}


} // namespace fla_msgs

namespace ros
{
namespace message_traits
{





template <class ContainerAllocator>
struct IsMessage< ::fla_msgs::WaypointList_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct IsMessage< ::fla_msgs::WaypointList_<ContainerAllocator> const>
  : TrueType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::fla_msgs::WaypointList_<ContainerAllocator> >
  : FalseType
  { };

template <class ContainerAllocator>
struct IsFixedSize< ::fla_msgs::WaypointList_<ContainerAllocator> const>
  : FalseType
  { };

template <class ContainerAllocator>
struct HasHeader< ::fla_msgs::WaypointList_<ContainerAllocator> >
  : TrueType
  { };

template <class ContainerAllocator>
struct HasHeader< ::fla_msgs::WaypointList_<ContainerAllocator> const>
  : TrueType
  { };


template<class ContainerAllocator>
struct MD5Sum< ::fla_msgs::WaypointList_<ContainerAllocator> >
{
  static const char* value()
  {
    return "0d705e35e06b0f87f64099aeaa643811";
  }

  static const char* value(const ::fla_msgs::WaypointList_<ContainerAllocator>&) { return value(); }
  static const uint64_t static_value1 = 0x0d705e35e06b0f87ULL;
  static const uint64_t static_value2 = 0xf64099aeaa643811ULL;
};

template<class ContainerAllocator>
struct DataType< ::fla_msgs::WaypointList_<ContainerAllocator> >
{
  static const char* value()
  {
    return "fla_msgs/WaypointList";
  }

  static const char* value(const ::fla_msgs::WaypointList_<ContainerAllocator>&) { return value(); }
};

template<class ContainerAllocator>
struct Definition< ::fla_msgs::WaypointList_<ContainerAllocator> >
{
  static const char* value()
  {
    return "std_msgs/Header header\n"
"geometry_msgs/PoseStamped[] poses\n"
"std_msgs/Float64[] speeds\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Header\n"
"# Standard metadata for higher-level stamped data types.\n"
"# This is generally used to communicate timestamped data \n"
"# in a particular coordinate frame.\n"
"# \n"
"# sequence ID: consecutively increasing ID \n"
"uint32 seq\n"
"#Two-integer timestamp that is expressed as:\n"
"# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')\n"
"# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')\n"
"# time-handling sugar is provided by the client library\n"
"time stamp\n"
"#Frame this data is associated with\n"
"string frame_id\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/PoseStamped\n"
"# A Pose with reference coordinate frame and timestamp\n"
"Header header\n"
"Pose pose\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Pose\n"
"# A representation of pose in free space, composed of position and orientation. \n"
"Point position\n"
"Quaternion orientation\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Point\n"
"# This contains the position of a point in free space\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"\n"
"================================================================================\n"
"MSG: geometry_msgs/Quaternion\n"
"# This represents an orientation in free space in quaternion form.\n"
"\n"
"float64 x\n"
"float64 y\n"
"float64 z\n"
"float64 w\n"
"\n"
"================================================================================\n"
"MSG: std_msgs/Float64\n"
"float64 data\n"
;
  }

  static const char* value(const ::fla_msgs::WaypointList_<ContainerAllocator>&) { return value(); }
};

} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

  template<class ContainerAllocator> struct Serializer< ::fla_msgs::WaypointList_<ContainerAllocator> >
  {
    template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
    {
      stream.next(m.header);
      stream.next(m.poses);
      stream.next(m.speeds);
    }

    ROS_DECLARE_ALLINONE_SERIALIZER
  }; // struct WaypointList_

} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::fla_msgs::WaypointList_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const ::fla_msgs::WaypointList_<ContainerAllocator>& v)
  {
    s << indent << "header: ";
    s << std::endl;
    Printer< ::std_msgs::Header_<ContainerAllocator> >::stream(s, indent + "  ", v.header);
    s << indent << "poses[]" << std::endl;
    for (size_t i = 0; i < v.poses.size(); ++i)
    {
      s << indent << "  poses[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::geometry_msgs::PoseStamped_<ContainerAllocator> >::stream(s, indent + "    ", v.poses[i]);
    }
    s << indent << "speeds[]" << std::endl;
    for (size_t i = 0; i < v.speeds.size(); ++i)
    {
      s << indent << "  speeds[" << i << "]: ";
      s << std::endl;
      s << indent;
      Printer< ::std_msgs::Float64_<ContainerAllocator> >::stream(s, indent + "    ", v.speeds[i]);
    }
  }
};

} // namespace message_operations
} // namespace ros

#endif // FLA_MSGS_MESSAGE_WAYPOINTLIST_H
