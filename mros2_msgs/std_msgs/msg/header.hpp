#include <string>

namespace std_msgs
{
namespace msg
{
class Header
{
public:
  std::string getTypeName();
  std::string frame_id;
  void copyToBuf(uint8_t *addrPtr)
  {
    uint32_t size = frame_id.size();
    memcpy(addrPtr, &size, 4);
    addrPtr += 4;
    memcpy(addrPtr, frame_id.c_str(),size);
    addrPtr += size;
    *addrPtr = 0;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    uint32_t msg_size;
    memcpy(&msg_size, addrPtr, 4);
    addrPtr += 4;
    frame_id.resize(msg_size);
    memcpy(&frame_id[0], addrPtr, msg_size);

  }

  uint8_t getTotalSize()
  {
    return (5 + frame_id.size());
  }
private:
  std::string type_name = "std_msgs::msg::dds_::Header";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Header*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Header_";
  }
};

}
