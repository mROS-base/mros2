#include <string>

namespace std_msgs
{
namespace msg
{
class UInt64
{
public:
  std::string getTypeName();
  uint64_t data;
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

  void memAlign(uint8_t *addrPtr){
    return;
  }

  uint8_t getTotalSize()
  {
    return 8;
  }
private:
  std::string type_name = "std_msgs::msg::dds_::UInt64";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::UInt64*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::UInt64_";
  }
};

}
