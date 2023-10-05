#ifndef _GEOMETRY_MSGS_MSG_POINT_H
#define _GEOMETRY_MSGS_MSG_POINT_H

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

namespace geometry_msgs
{
namespace msg
{
class Point
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

  
  double x;
  
  double y;
  
  double z;
  

  uint32_t copyToBuf(uint8_t *addrPtr)
  {
    uint32_t tmpPub = 0;
    uint32_t arraySize;
    uint32_t stringSize;
    
    
    
    if (cntPub % 8 > 0)
    {
      for (uint32_t i = 0; i < (8 - (cntPub % 8)); i++)
      {
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 8 - (cntPub % 8);
    }
    
    memcpy(addrPtr, &x, 8);
    addrPtr += 8;
    cntPub += 8;

    
    
    
    
    if (cntPub % 8 > 0)
    {
      for (uint32_t i = 0; i < (8 - (cntPub % 8)); i++)
      {
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 8 - (cntPub % 8);
    }
    
    memcpy(addrPtr, &y, 8);
    addrPtr += 8;
    cntPub += 8;

    
    
    
    
    if (cntPub % 8 > 0)
    {
      for (uint32_t i = 0; i < (8 - (cntPub % 8)); i++)
      {
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 8 - (cntPub % 8);
    }
    
    memcpy(addrPtr, &z, 8);
    addrPtr += 8;
    cntPub += 8;

    
    

    return cntPub;
  }

  uint32_t copyFromBuf(const uint8_t *addrPtr)
  {
    uint32_t tmpSub = 0;
    uint32_t arraySize;
    uint32_t stringSize;

    
    
    
    if (cntSub % 8 > 0)
    {
      for (uint32_t i = 0; i < (8 - (cntSub % 8)); i++)
      {
        addrPtr += 1;
      }
      cntSub += 8 - (cntSub % 8);
    }
    
    memcpy(&x, addrPtr, 8);
    addrPtr += 8;
    cntSub += 8;
    
    
    
    
    if (cntSub % 8 > 0)
    {
      for (uint32_t i = 0; i < (8 - (cntSub % 8)); i++)
      {
        addrPtr += 1;
      }
      cntSub += 8 - (cntSub % 8);
    }
    
    memcpy(&y, addrPtr, 8);
    addrPtr += 8;
    cntSub += 8;
    
    
    
    
    if (cntSub % 8 > 0)
    {
      for (uint32_t i = 0; i < (8 - (cntSub % 8)); i++)
      {
        addrPtr += 1;
      }
      cntSub += 8 - (cntSub % 8);
    }
    
    memcpy(&z, addrPtr, 8);
    addrPtr += 8;
    cntSub += 8;
    
    

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
  std::string type_name = "geometry_msgs::msg::dds_::Point";
};
};
}

namespace message_traits
{
template<>
struct TypeName<geometry_msgs::msg::Point*> {
  static const char* value()
  {
    return "geometry_msgs::msg::dds_::Point_";
  }
};
}

#endif