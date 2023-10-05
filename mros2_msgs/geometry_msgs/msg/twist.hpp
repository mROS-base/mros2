#ifndef _GEOMETRY_MSGS_MSG_TWIST_H
#define _GEOMETRY_MSGS_MSG_TWIST_H

#include <iostream>
#include <string>
#include <cstring>
#include "geometry_msgs/msg/vector3.hpp"
#include "geometry_msgs/msg/vector3.hpp"

using namespace std;

namespace geometry_msgs
{
namespace msg
{
class Twist
{
public:
  uint32_t cntPub = 0;
  uint32_t cntSub = 0;
  uint32_t idxSerialized = 0;

  typedef std::pair<bool, uint32_t> FragCopyReturnType;

  template <class T>
  uint32_t copyPrimToFragBufLocal(uint8_t *&addrPtr,
                                  const uint32_t cntPub,
                                  const uint32_t size,
                                  const T &data)
  {
    uint32_t lenPad = (0 == (cntPub % sizeof(T))) ? 0 : (sizeof(T) - (cntPub % sizeof(T))); // this doesn't get along with float128.
    if (size < sizeof(T))
    {
      // There are no enough space.
      return 0;
    }
    // Put padding space
    for (int i = 0; i < lenPad; i++)
    {
      *addrPtr = 0;
      addrPtr += 1;
    }
    // Store serialzed value.
    memcpy(addrPtr, &data, sizeof(T));
    addrPtr += sizeof(T);

    return sizeof(T) + lenPad;
  }

  template <class T>
  FragCopyReturnType copyArrayToFragBufLocal(uint8_t *&addrPtr,
                                             const uint32_t size,
                                             T &data,
                                             uint32_t &cntPubMemberLocal)
  {
    uint32_t pubDataSize = data.size();
    uint32_t cntLocalFrag = 0;

    if (cntPubMemberLocal < sizeof(uint32_t))
    {
      if (size < sizeof(uint32_t))
      {
        return {false, 0};
      }
      memcpy(addrPtr, &pubDataSize, sizeof(uint32_t));
      addrPtr += sizeof(uint32_t);
      cntPubMemberLocal += sizeof(uint32_t);
      cntLocalFrag += sizeof(uint32_t);
    }

    uint32_t cntFrag = (cntPubMemberLocal - sizeof(uint32_t)); // cntPubMemberLocal > 4 here
    uint32_t tmp = std::min(pubDataSize - cntFrag, size - cntLocalFrag);
    if (0 < tmp)
    {
      memcpy(addrPtr, data.data() + cntFrag, tmp);
      addrPtr += tmp;
      cntPubMemberLocal += tmp;
      cntLocalFrag += tmp;
    }

    return {(cntPubMemberLocal - sizeof(uint32_t)) >= pubDataSize, cntLocalFrag};
  }

  
  geometry_msgs::msg::Vector3 linear;
  
  geometry_msgs::msg::Vector3 angular;
  

  uint32_t copyToBuf(uint8_t *addrPtr)
  {
    uint32_t tmpPub = 0;
    uint32_t arraySize;
    uint32_t stringSize;
    
    
    
    tmpPub = linear.copyToBuf(addrPtr);
    cntPub += tmpPub;
    addrPtr += tmpPub;
    
    
    
    
    
    tmpPub = angular.copyToBuf(addrPtr);
    cntPub += tmpPub;
    addrPtr += tmpPub;
    
    
    

    return cntPub;
  }

  uint32_t copyFromBuf(const uint8_t *addrPtr)
  {
    uint32_t tmpSub = 0;
    uint32_t arraySize;
    uint32_t stringSize;

    
    
    
    tmpSub = linear.copyFromBuf(addrPtr);
    cntSub += tmpSub;
    addrPtr += tmpSub;
    

    
    
    
    
    tmpSub = angular.copyFromBuf(addrPtr);
    cntSub += tmpSub;
    addrPtr += tmpSub;
    

    
    

    return cntSub;
  }

  void memAlign(uint8_t *addrPtr)
  {
    if (cntPub % 4 > 0)
    {
      addrPtr += cntPub;
      for (uint32_t i = 0; i < (4 - (cntPub % 4)); i++)
      {
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4 - (cntPub % 4);
    }
    return;
  }

  uint32_t getTotalSize()
  {
    uint32_t tmpCntPub = cntPub;
    cntPub = 0;
    return tmpCntPub;
  }

  uint32_t getPubCnt()
  {
    return cntPub;
  }

  uint32_t calcRawTotalSize()
  {
    // TODO: store template code here
    return 0;
  }

  uint32_t calcTotalSize()
  {
    uint32_t tmp;
    tmp = 4 + calcRawTotalSize();                  // CDR encoding version.
    tmp += (0 == (tmp % 4) ? 0 : (4 - (tmp % 4))); // Padding
    return tmp;
  }

  void resetCount()
  {
    cntPub = 0;
    cntSub = 0;
    idxSerialized = 0;
    // TODO: store template code here
    return;
  }

  FragCopyReturnType copyToFragBuf(uint8_t *addrPtr, uint32_t size)
  {
    // TODO: store template code here
    return {false, 0};
  }

private:
  std::string type_name = "geometry_msgs::msg::dds_::Twist";
};
};
}

namespace message_traits
{
template<>
struct TypeName<geometry_msgs::msg::Twist*> {
  static const char* value()
  {
    return "geometry_msgs::msg::dds_::Twist_";
  }
};
}

#endif