#include <string>

namespace std_msgs
{
namespace msg
{
class Byte
{
public:
  std::string getTypeName();
  uint8_t data;
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
  std::string type_name = "std_msgs::msg::dds_::Byte";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Byte*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Byte_";
  }
};

}

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Byte>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Byte*));
template void mros2::Publisher::publish(std_msgs::msg::Byte &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Byte>(void *callee, const rtps::ReaderCacheChange &cacheChange);