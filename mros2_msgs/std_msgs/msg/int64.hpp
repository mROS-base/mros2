#include "mros2.h"
#include <string>

namespace std_msgs
{
namespace msg
{
class Int64
{
public:
  std::string getTypeName();
  int64_t data;
  void copyToBuf(uint8_t *addrPtr)
  {
    memcpy(addrPtr, &data, 8);
    addrPtr += 8;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    memcpy(&data, addrPtr, 8);
    addrPtr += 8;
  }

  uint8_t getTotalSize()
  {
    return 8;
  }
private:
  std::string type_name = "std_msgs::msg::dds_::Int64";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Int64*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Int64_";
  }
};

}

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Int64>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Int64*));
template void mros2::Publisher::publish(std_msgs::msg::Int64 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Int64>(void *callee, const rtps::ReaderCacheChange &cacheChange);