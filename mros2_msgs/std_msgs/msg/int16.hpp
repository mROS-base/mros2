#include <string>

namespace std_msgs
{
namespace msg
{
class Int16
{
public:
  typedef std::pair<bool, uint32_t> FragCopyReturnType;

  std::string getTypeName();
  int16_t data;
  uint32_t cntPub = 0;

  void copyToBuf(uint8_t *addrPtr)
  {
    memcpy(addrPtr, &data, 2);
    addrPtr += 2;
    cntPub += 2;
  }

  void copyFromBuf(const uint8_t *addrPtr)
  {
    memcpy(&data, addrPtr, 2);
    addrPtr += 2;
  }

  void memAlign(uint8_t *addrPtr){
    return;
  }

  uint32_t getTotalSize()
  {
    uint32_t tmpCntPub = cntPub;
    cntPub = 0;
    return tmpCntPub ;
  }

  uint32_t getPubCnt()
  {
    return cntPub;
  }

  void resetCount()
  {
    cntPub = 0;
    return;
  }

  uint32_t calcRawTotalSize()
  {
    return 2;
  }

  uint32_t calcTotalSize()
  {
    uint32_t tmp;
    tmp = 4 // CDR encoding version.
          + calcRawTotalSize();
    tmp += ( 0 == (tmp % 4) ? // Padding
	     0 : (4 - (tmp % 4)) );
    return tmp;
  }

  FragCopyReturnType copyToFragBuf(uint8_t *addrPtr, uint32_t size)
  {
    // Nothing to be done because the message template
    // has own primitive types in it so that
    // this message type won't be used as a part of
    // fragmented messages.
    return {false, 0};
  }
private:
  std::string type_name = "std_msgs::msg::dds_::Int16";
};
}//namspace msg
}//namespace std_msgs

namespace message_traits
{

template<>
struct TypeName<std_msgs::msg::Int16*> {
  static const char* value()
  {
    return "std_msgs::msg::dds_::Int16_";
  }
};

}
