#ifndef _GEOMETRY_MSGS_MSG_TWIST_H
#define _GEOMETRY_MSGS_MSG_TWIST_H

#include <iostream>
#include <string>
#include <vector>


#include "geometry_msgs/msg/vector3.hpp"


using namespace std;

namespace geometry_msgs
{
namespace msg
{
class Twist
{
public:
  uint8_t cntPub = 0;
  uint8_t cntSub = 0;
    
  geometry_msgs::msg::Vector3 linear
;
    
  geometry_msgs::msg::Vector3 angular;
  

  uint8_t copyToBuf(uint8_t *addrPtr)
  {
    
    
    cntPub += linear
.copyToBuf(addrPtr);

    
    
    
    cntPub += angular.copyToBuf(addrPtr);

    
    

    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }  
      cntPub += 4-(cntPub%4);
    }

    return cntPub;
  }

  uint8_t copyFromBuf(const uint8_t *rbuf) {
    
    
    cntSub += linear
.copyFromBuf(rbuf);

    
    
    
    cntSub += angular.copyFromBuf(rbuf);

    
    

    return cntSub;
  }

  uint8_t getTotalSize(){
    return cntPub ;
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