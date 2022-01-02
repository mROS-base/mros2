#include <string>

namespace std_msgs
{
namespace msg
{
class Header
{
public:
  std::string getTypeName();
  int32_t sec;
  uint32_t nanosec;
  std::string frame_id;
  uint8_t cntPub = 0;
  uint32_t pubSize;
  uint32_t subSize;

  void copyToBuf(uint8_t *addrPtr)
  {
    memcpy(addrPtr, &sec, 4);
    addrPtr += 4;
    cntPub += 4;
    memcpy(addrPtr, &nanosec, 4);
    addrPtr += 4;
    cntPub += 4;
    pubSize = frame_id.size();
    memcpy(addrPtr, &pubSize, 4);
    addrPtr += 4;
    cntPub += 4;
    memcpy(addrPtr, frame_id.c_str(),pubSize);
    addrPtr += pubSize;
    cntPub += pubSize;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    memcpy(&sec, addrPtr, 4);
    addrPtr += 4;
    memcpy(&nanosec, addrPtr, 4);
    addrPtr += 4;
    memcpy(&subSize, addrPtr, 4);
    addrPtr += 4;
    frame_id.resize(subSize);
    memcpy(&frame_id[0], addrPtr, subSize);
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
