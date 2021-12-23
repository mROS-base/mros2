#ifndef _MIX_MSGS_MSG_MIX_H
#define _MIX_MSGS_MSG_MIX_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace mix_msgs
{
namespace msg
{
class Mix
{
public:
  uint8_t cntPub = 0;
  uint8_t cntSub = 0;
    
  string name
;
    
  uint16_t height
;
    
  float weight
;
    
  std::vector<uint16_t> array;
  

  void copyToBuf(uint8_t *addrPtr)
  {
    
    
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    uint32_t stringSize = name
.size();
    memcpy(addrPtr,&stringSize,4);
    addrPtr += 4;
    cntPub += 4;
    memcpy(addrPtr,name
.c_str(),stringSize);
    addrPtr += stringSize;
    cntPub += stringSize;

    
    
    
    if (cntPub%4 >0 && 2 > 1){
      if ((2 <= (4-(cntPub%4)))&&(2==2)){
        for (int i=0; i<(4-(cntPub%4))-2; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }
        cntPub += (4-(cntPub%4))-2; 
      } else {
        for(int i=0; i<(4-(cntPub%4)) ; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }   
        cntPub += 4-(cntPub%4);   
      }
    }
    memcpy(addrPtr,&height
,2);
    addrPtr += 2;
    cntPub += 2;

    
    
    
    if (cntPub%4 >0 && 4 > 1){
      if ((4 <= (4-(cntPub%4)))&&(4==2)){
        for (int i=0; i<(4-(cntPub%4))-4; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }
        cntPub += (4-(cntPub%4))-4; 
      } else {
        for(int i=0; i<(4-(cntPub%4)) ; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }   
        cntPub += 4-(cntPub%4);   
      }
    }
    memcpy(addrPtr,&weight
,4);
    addrPtr += 4;
    cntPub += 4;

    
    
    
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    uint32_t arraySize = array.size();
    memcpy(addrPtr,&arraySize,4);
    addrPtr += 4;
    cntPub += 4;
    const uint16_t* ptr = array.data();
    for(int i=0; i<arraySize ; i++){
      memcpy(addrPtr, &(ptr[i]),2);
      addrPtr += 2;
      cntPub += 2;
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
    
    
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        rbuf += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    uint32_t stringSize;
    memcpy(&stringSize, rbuf, 4);
    rbuf += 4;
    cntSub += 4;
    name
.resize(stringSize);
    memcpy(&name
[0],rbuf,stringSize);
    rbuf += stringSize;
    cntSub += stringSize;

    
    
    
    if (cntSub%4 >0 && 2 > 1){
      if ((2 <= (4-(cntSub%4)))&&(2==2)){
        for (int i=0; i<(4-(cntSub%4))-2; i++){
          rbuf += 1;
        }
        cntSub += (4-(cntSub%4))-2;
      } else {
        for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
        }
        cntSub += 4-(cntSub%4);
      }
    }
    memcpy(&height
,rbuf,2);
    rbuf += 2;
    cntSub += 2;
    
    
    
    if (cntSub%4 >0 && 4 > 1){
      if ((4 <= (4-(cntSub%4)))&&(4==2)){
        for (int i=0; i<(4-(cntSub%4))-4; i++){
          rbuf += 1;
        }
        cntSub += (4-(cntSub%4))-4;
      } else {
        for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
        }
        cntSub += 4-(cntSub%4);
      }
    }
    memcpy(&weight
,rbuf,4);
    rbuf += 4;
    cntSub += 4;
    
    
    
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
    array.reserve(arraySize);
    for(int i=0;i<arraySize;i++){
      uint16_t buf;
      memcpy(&buf,rbuf,2);
      array.push_back(buf);
      rbuf += 2;
      cntSub += 2;
    }

    
    
  }

  uint8_t getTotalSize(){
    return cntPub ;
  }

private:
  std::string type_name = "mix_msgs::msg::dds_::Mix";
};
};
}

namespace message_traits
{
template<>
struct TypeName<mix_msgs::msg::Mix*> {
  static const char* value()
  {
    return "mix_msgs::msg::dds_::Mix_";
  }
};
}

#endif