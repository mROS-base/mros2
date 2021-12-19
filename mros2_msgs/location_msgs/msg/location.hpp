#ifndef _LOCATION_MSGS_MSG_LOCATION_H
#define _LOCATION_MSGS_MSG_LOCATION_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace location_msgs
{
namespace msg
{
class Location
{
public:
  uint8_t cntPub = 0;
  uint8_t cntSub = 0;
    
  int16_t x
;
    
  int16_t y
;
    
  int16_t z;
  

  void copyToBuf(uint8_t *addrPtr)
  {
    
    
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
    memcpy(addrPtr,&x
,2);
    addrPtr += 2;
    cntPub += 2;

    
    
    
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
    memcpy(addrPtr,&y
,2);
    addrPtr += 2;
    cntPub += 2;

    
    
    
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
    memcpy(addrPtr,&z,2);
    addrPtr += 2;
    cntPub += 2;

    
    

    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }  
      cntPub += 4-(cntPub%4);
    }
  }

  void copyFromBuf(const uint8_t *rbuf) {
    
    
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
    memcpy(&x
,rbuf,2);
    rbuf += 2;
    cntSub += 2;
    
    
    
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
    memcpy(&y
,rbuf,2);
    rbuf += 2;
    cntSub += 2;
    
    
    
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
    memcpy(&z,rbuf,2);
    rbuf += 2;
    cntSub += 2;
    
    
  }

  uint8_t getTotalSize(){
    return cntPub ;
  }

private:
  std::string type_name = "location_msgs::msg::dds_::Location";
};
};
}

namespace message_traits
{
template<>
struct TypeName<location_msgs::msg::Location*> {
  static const char* value()
  {
    return "location_msgs::msg::dds_::Location_";
  }
};
}

#endif