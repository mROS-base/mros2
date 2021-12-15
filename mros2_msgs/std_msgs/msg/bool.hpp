#include "mros2.h"
#include <string>

namespace std_msgs
{
namespace msg
{
class Bool
{
public:
  std::string getTypeName();
  bool data;
  void copyToBuf(uint8_t *addrPtr)
  {
    memcpy(addrPtr, &data, 1);
    addrPtr += 1;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    memcpy(&data, addrPtr, 1);
    addrPtr += 1;
  }

  uint8_t getTotalSize()
  {
    return 1;
  }
private:
  std::string type_name = "std_msgs::msg::dds_::Bool";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Bool*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Bool_";
  }
};

}

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Bool>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Bool*));
template void mros2::Publisher::publish(std_msgs::msg::Bool &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Bool>(void *callee, const rtps::ReaderCacheChange &cacheChange);
