#include <string>

namespace std_msgs
{
namespace msg
{
class String
{
public:
  std::string getTypeName();
  std::string data;
  void copyToBuf(uint8_t *addrPtr)
  {
    uint32_t size = data.size();
    memcpy(addrPtr, &size, 4);
    addrPtr += 4;
    memcpy(addrPtr, data.c_str(),size);
    addrPtr += size;
    *addrPtr = 0;
    //buf_index += size;
  }
  uint8_t getTotalSize()
  {
    return (5 + data.size());
  }
private:
  std::string type_name = "std_msgs::msg::dds_::String";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::String*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::String_";
  }
};

}
