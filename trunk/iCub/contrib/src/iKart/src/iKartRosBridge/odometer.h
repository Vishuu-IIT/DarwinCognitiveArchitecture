/* Auto-generated by genmsg_cpp for file /home/user/randaz/ikart_ros_bridge/msg/odometer.msg */
#ifndef IKART_ROS_BRIDGE_MESSAGE_ODOMETER_H
#define IKART_ROS_BRIDGE_MESSAGE_ODOMETER_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace ikart_ros_bridge
{
template <class ContainerAllocator>
struct odometer_ {
  typedef odometer_<ContainerAllocator> Type;

  odometer_()
  : distance(0.0)
  , angle(0.0)
  {
  }

  odometer_(const ContainerAllocator& _alloc)
  : distance(0.0)
  , angle(0.0)
  {
  }

  typedef double _distance_type;
  double distance;

  typedef double _angle_type;
  double angle;


private:
  static const char* __s_getDataType_() { return "ikart_ros_bridge/odometer"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "1f1d53743f4592ee455aa3eaf9019457"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "float64 distance #total distance traveled (meters)\n float64 angle #total angle traveled (radians)\n "; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, distance);
    ros::serialization::serialize(stream, angle);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, distance);
    ros::serialization::deserialize(stream, angle);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(distance);
    size += ros::serialization::serializationLength(angle);
    return size;
  }

  typedef boost::shared_ptr< ::ikart_ros_bridge::odometer_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::ikart_ros_bridge::odometer_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct odometer
typedef  ::ikart_ros_bridge::odometer_<std::allocator<void> > odometer;

typedef boost::shared_ptr< ::ikart_ros_bridge::odometer> odometerPtr;
typedef boost::shared_ptr< ::ikart_ros_bridge::odometer const> odometerConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::ikart_ros_bridge::odometer_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::ikart_ros_bridge::odometer_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace ikart_ros_bridge

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::ikart_ros_bridge::odometer_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::ikart_ros_bridge::odometer_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::ikart_ros_bridge::odometer_<ContainerAllocator> > {
  static const char* value() 
  {
    return "1f1d53743f4592ee455aa3eaf9019457";
  }

  static const char* value(const  ::ikart_ros_bridge::odometer_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x1f1d53743f4592eeULL;
  static const uint64_t static_value2 = 0x455aa3eaf9019457ULL;
};

template<class ContainerAllocator>
struct DataType< ::ikart_ros_bridge::odometer_<ContainerAllocator> > {
  static const char* value() 
  {
    return "ikart_ros_bridge/odometer";
  }

  static const char* value(const  ::ikart_ros_bridge::odometer_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::ikart_ros_bridge::odometer_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64 distance #total distance traveled (meters)\nfloat64 angle #total angle traveled (radians)\n";
  }

  static const char* value(const  ::ikart_ros_bridge::odometer_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::ikart_ros_bridge::odometer_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::ikart_ros_bridge::odometer_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.distance);
    stream.next(m.angle);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct odometer_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::ikart_ros_bridge::odometer_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::ikart_ros_bridge::odometer_<ContainerAllocator> & v) 
  {
    s << indent << "distance: ";
    Printer<double>::stream(s, indent + "  ", v.distance);
    s << indent << "angle: ";
    Printer<double>::stream(s, indent + "  ", v.angle);
  }
};


} // namespace message_operations
} // namespace ros

#endif // IKART_ROS_BRIDGE_MESSAGE_ODOMETER_H
