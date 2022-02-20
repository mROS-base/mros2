#include <string>

namespace std_msgs
{
namespace msg
{
class Int8
{
public:
  std::string getTypeName();
  int8_t data;
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

  void memAlign(uint8_t *addrPtr){
    return;
  }

  uint8_t getTotalSize()
  {
    return 1;
  }
private:
  std::string type_name = "std_msgs::msg::dds_::Int8";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Int8*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Int8_";
  }
};

}