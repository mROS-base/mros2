#include <string>

namespace std_msgs
{
namespace msg
{
class WString
{
public:
  std::string getTypeName();
  std::u16string data;
  void copyToBuf(uint8_t *addrPtr)
  {
    uint32_t size = data.size();
    memcpy(addrPtr, &size, 4);
    addrPtr += 4;
    memcpy(addrPtr, data.c_str(),2*size);
    addrPtr += 2*size;
    *addrPtr = 0;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    uint32_t msg_size;
    memcpy(&msg_size, addrPtr, 4);
    addrPtr += 4;
    data.resize(2*msg_size);
    memcpy(&data[0], addrPtr, 2*msg_size);

  }

  uint8_t getTotalSize()
  {
    return (5 + 2*data.size());
  }
private:
  std::string type_name = "std_msgs::msg::dds_::WString";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::WString*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::WString_";
  }
};

}

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::WString>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(std_msgs::msg::WString*));
template void mros2::Publisher::publish(std_msgs::msg::WString &msg);
template void mros2::Subscriber::callback_handler<std_msgs::msg::WString>(void *callee, const rtps::ReaderCacheChange &cacheChange);