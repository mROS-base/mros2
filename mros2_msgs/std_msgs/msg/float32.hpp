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

  void memAlign(uint8_t *addrPtr){
    return;
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