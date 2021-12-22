#ifndef _U_INT32_ARRAY_MSGS_MSG_UINT32ARRAY_H
#define _U_INT32_ARRAY_MSGS_MSG_UINT32ARRAY_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace u_int32_array_msgs
{
namespace msg
{
class UInt32Array
{
public:
  uint8_t cntPub = 0;
  uint8_t cntSub = 0;
    
  std::vector<uint32_t> data;
  

  void copyToBuf(uint8_t *addrPtr)
  {
    
    {
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    uint32_t arraySize = data.size();
    memcpy(addrPtr,&arraySize,4);
    addrPtr += 4;
    cntPub += 4;
    const uint32_t* ptr = data.data();
    for(int i=0; i<arraySize ; i++){
      memcpy(addrPtr, &(ptr[i]),4);
      addrPtr += 4;
      cntPub += 4;
    }
    }
    
    
    

    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }  
      cntPub += 4-(cntPub%4);
    }
  }

  void copyFromBuf(const uint8_t *rbuf) {
    
    {
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        rbuf += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    uint32_t arraySize;
    memcpy(&arraySize,rbuf,4);
    rbuf += 4;    
    cntSub += 4;
    data.reserve(arraySize);
    for(int i=0;i<arraySize;i++){
      uint32_t buf;
      memcpy(&buf,rbuf,4);
      data.push_back(buf);
      rbuf += 4;
      cntSub += 4;
    }

    
    
  }

  uint8_t getTotalSize(){
    return cntPub ;
  }

private:
  std::string type_name = "u_int32_array_msgs::msg::dds_::UInt32Array";
};
};
}

namespace message_traits
{
template<>
struct TypeName<u_int32_array_msgs::msg::UInt32Array*> {
  static const char* value()
  {
    return "u_int32_array_msgs::msg::dds_::UInt32Array_";
  }
};
}

#endif