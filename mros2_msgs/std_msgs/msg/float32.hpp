#include <string>

namespace std_msgs
{
namespace msg
{
class Float32
{
public:
  std::string getTypeName();
  float data;
  void copyToBuf(uint8_t *addrPtr)
  {
    memcpy(addrPtr, &data, 4);
    addrPtr += 4;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    memcpy(&data, addrPtr, 4);
    addrPtr += 4;
  }
  uint8_t getTotalSize()
  {
    return 4;
  }
private:
  std::string type_name = "std_msgs::msg::dds_::Float32";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Float32*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Float32_";
  }
};

}

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::Float32>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::Float32*));
template void mros2::Publisher::publish(std_msgs::msg::Float32 &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::Float32>(void *callee, const rtps::ReaderCacheChange &cacheChange);