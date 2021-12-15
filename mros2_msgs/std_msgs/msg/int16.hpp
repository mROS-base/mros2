#include <string>

namespace std_msgs
{
namespace msg
{
class Int16
{
public:
  std::string getTypeName();
  int16_t data;

  void copyToBuf(uint8_t *addrPtr)
  {
    memcpy(addrPtr, &data, 2);
    addrPtr += 2;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    memcpy(&data, addrPtr, 2);
    addrPtr += 2;
  }

  uint8_t getTotalSize()
  {
    return 2;
  }
private:
  std::string type_name = "std_msgs::msg::dds_::Int16";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Int16*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Int16_";
  }
};

}

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Int16>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription<std_msgs::msg::Int16>(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Int16*));
template void mros2::Publisher::publish(std_msgs::msg::Int16 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Int16>(void *callee, const rtps::ReaderCacheChange &cacheChange);