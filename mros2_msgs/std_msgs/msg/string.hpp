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
  uint8_t cntPub = 0;
  uint32_t pubSize;
  uint32_t subSize;
  void copyToBuf(uint8_t *addrPtr)
  {
    pubSize = data.size();
    memcpy(addrPtr, &pubSize, 4);
    addrPtr += 4;
    cntPub += 4 ;
    memcpy(addrPtr, data.c_str(),pubSize);
    addrPtr += pubSize;
    cntPub += pubSize;  
    
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    memcpy(&subSize, addrPtr, 4);
    addrPtr += 4;
    data.resize(subSize);
    memcpy(&data[0], addrPtr, subSize);

  }

   void memAlign(uint8_t *addrPtr){
    if (cntPub%4 > 0){
      addrPtr += cntPub;
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    return;
  }

  uint8_t getTotalSize()
  {
    return cntPub;
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
