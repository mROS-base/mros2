#ifndef _GEOMETRY_MSGS_MSG_VECTOR3_H
#define _GEOMETRY_MSGS_MSG_VECTOR3_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace geometry_msgs
{
namespace msg
{
class Vector3
{
public:
  uint8_t cntPub = 0;
  uint8_t cntSub = 0;
    
  double x
;
    
  double y
;
    
  double z;
  

  void copyToBuf(uint8_t *addrPtr)
  {
    
    
    if (cntPub%4 >0 && 8 > 1){
      if ((8 <= (4-(cntPub%4)))&&(8==2)){
        for (int i=0; i<(4-(cntPub%4))-8; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }
        cntPub += (4-(cntPub%4))-8; 
      } else {
        for(int i=0; i<(4-(cntPub%4)) ; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }   
        cntPub += 4-(cntPub%4);   
      }
    }
    memcpy(addrPtr,&x
,8);
    addrPtr += 8;
    cntPub += 8;

    
    
    
    if (cntPub%4 >0 && 8 > 1){
      if ((8 <= (4-(cntPub%4)))&&(8==2)){
        for (int i=0; i<(4-(cntPub%4))-8; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }
        cntPub += (4-(cntPub%4))-8; 
      } else {
        for(int i=0; i<(4-(cntPub%4)) ; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }   
        cntPub += 4-(cntPub%4);   
      }
    }
    memcpy(addrPtr,&y
,8);
    addrPtr += 8;
    cntPub += 8;

    
    
    
    if (cntPub%4 >0 && 8 > 1){
      if ((8 <= (4-(cntPub%4)))&&(8==2)){
        for (int i=0; i<(4-(cntPub%4))-8; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }
        cntPub += (4-(cntPub%4))-8; 
      } else {
        for(int i=0; i<(4-(cntPub%4)) ; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }   
        cntPub += 4-(cntPub%4);   
      }
    }
    memcpy(addrPtr,&z,8);
    addrPtr += 8;
    cntPub += 8;

    
    

    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }  
      cntPub += 4-(cntPub%4);
    }
  }

  void copyFromBuf(const uint8_t *rbuf) {
    
    
    if (cntSub%4 >0 && 8 > 1){
      if ((8 <= (4-(cntSub%4)))&&(8==2)){
        for (int i=0; i<(4-(cntSub%4))-8; i++){
          rbuf += 1;
        }
        cntSub += (4-(cntSub%4))-8;
      } else {
        for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
        }
        cntSub += 4-(cntSub%4);
      }
    }
    memcpy(&x
,rbuf,8);
    rbuf += 8;
    cntSub += 8;
    
    
    
    if (cntSub%4 >0 && 8 > 1){
      if ((8 <= (4-(cntSub%4)))&&(8==2)){
        for (int i=0; i<(4-(cntSub%4))-8; i++){
          rbuf += 1;
        }
        cntSub += (4-(cntSub%4))-8;
      } else {
        for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
        }
        cntSub += 4-(cntSub%4);
      }
    }
    memcpy(&y
,rbuf,8);
    rbuf += 8;
    cntSub += 8;
    
    
    
    if (cntSub%4 >0 && 8 > 1){
      if ((8 <= (4-(cntSub%4)))&&(8==2)){
        for (int i=0; i<(4-(cntSub%4))-8; i++){
          rbuf += 1;
        }
        cntSub += (4-(cntSub%4))-8;
      } else {
        for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
        }
        cntSub += 4-(cntSub%4);
      }
    }
    memcpy(&z,rbuf,8);
    rbuf += 8;
    cntSub += 8;
    
    
  }

  uint8_t getTotalSize(){
    return cntPub ;
  }

private:
  std::string type_name = "geometry_msgs::msg::dds_::Vector3";
};
};
}

namespace message_traits
{
template<>
struct TypeName<geometry_msgs::msg::Vector3*> {
  static const char* value()
  {
    return "geometry_msgs::msg::dds_::Vector3_";
  }
};
}

#endif