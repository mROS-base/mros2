#include "mros2.h"
#include <string>

namespace std_msgs
{
namespace msg
{
class Char
{
public:
  std::string getTypeName();
  char data;
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
  std::string type_name = "std_msgs::msg::dds_::Char";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Char*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Char_";
  }
};

}

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Char>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Char*));
template void mros2::Publisher::publish(std_msgs::msg::Char &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Char>(void *callee, const rtps::ReaderCacheChange &cacheChange);
