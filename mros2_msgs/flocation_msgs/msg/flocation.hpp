#ifndef _FLOCATION_MSGS_MSG_FLOCATION_H
#define _FLOCATION_MSGS_MSG_FLOCATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace flocation_msgs
{
namespace msg
{
class Flocation
{
public:
  uint8_t cntPub = 0;
  uint8_t cntSub = 0;
    
  float x
;
    
  float y
;
    
  float z;
  

  void copyToBuf(uint8_t *addrPtr)
  {
    
    
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
    memcpy(addrPtr,&x
,4);
    addrPtr += 4;
    cntPub += 4;

    
    
    
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
    memcpy(addrPtr,&y
,4);
    addrPtr += 4;
    cntPub += 4;

    
    
    
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
    memcpy(addrPtr,&z,4);
    addrPtr += 4;
    cntPub += 4;

    
    

    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }  
      cntPub += 4-(cntPub%4);
    }
  }

  void copyFromBuf(const uint8_t *rbuf) {
    
    
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
    memcpy(&x
,rbuf,4);
    rbuf += 4;
    cntSub += 4;
    
    
    
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
    memcpy(&y
,rbuf,4);
    rbuf += 4;
    cntSub += 4;
    
    
    
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
    memcpy(&z,rbuf,4);
    rbuf += 4;
    cntSub += 4;
    
    
  }

  uint8_t getTotalSize(){
    return cntPub ;
  }

private:
  std::string type_name = "flocation_msgs::msg::dds_::Flocation";
};
};
}

namespace message_traits
{
template<>
struct TypeName<flocation_msgs::msg::Flocation*> {
  static const char* value()
  {
    return "flocation_msgs::msg::dds_::Flocation_";
  }
};
}

#endif