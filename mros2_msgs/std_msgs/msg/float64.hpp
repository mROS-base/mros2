#include <string>

namespace std_msgs
{
namespace msg
{
class Float64
{
public:
  std::string getTypeName();
  double data;
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
  std::string type_name = "std_msgs::msg::dds_::Float64";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Float64*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Float64_";
  }
};

}