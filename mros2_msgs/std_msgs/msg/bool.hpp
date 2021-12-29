#include <string>

namespace std_msgs
{
namespace msg
{
class Bool
{
public:
  std::string getTypeName();
  bool data;
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
  std::string type_name = "std_msgs::msg::dds_::Bool";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Bool*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Bool_";
  }
};

}
