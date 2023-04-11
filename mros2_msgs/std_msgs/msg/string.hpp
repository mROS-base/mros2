#include <string>

namespace std_msgs
{
namespace msg
{
class String
{
public:
  typedef std::pair<bool, uint32_t> FragCopyReturnType;

  std::string getTypeName();
  std::string data;
  uint32_t cntPub = 0;
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
  }

  uint32_t calcRawTotalSize()
  {
    uint32_t tmp;
    tmp = sizeof(uint32_t) + data.size();
    return tmp;
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
    uint32_t pubStrSize = data.size();
    uint32_t cntLocalFrag = 0; // Countor of locallly fragmented data.

    if (cntPub < sizeof(uint32_t)) {
      if (size < sizeof(uint32_t)) {
        return {false, 0};
      }
      memcpy(addrPtr, &pubStrSize, sizeof(uint32_t));
      addrPtr += 4;
      cntPub += 4 ;
      cntLocalFrag += 4;
    }

    uint32_t cntFrag = (cntPub - sizeof(uint32_t));
    uint32_t tmp = std::min(pubStrSize - cntFrag,
			    size - cntLocalFrag);
    if (0 < tmp) {
      memcpy(addrPtr, data.c_str() + cntFrag, tmp);
      addrPtr += tmp;
      cntPub += tmp;
      cntLocalFrag += tmp;
    }

    return {(cntPub - sizeof(uint32_t)) >= pubStrSize, cntLocalFrag};
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
