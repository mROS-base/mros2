#ifndef _HEALTH_MSGS_MSG_HEALTH_H
#define _HEALTH_MSGS_MSG_HEALTH_H

#include <iostream>

namespace health_msgs
{
namespace msg
{
namespace Health
{
public:
    
  string name
;
    
  int8_t height
;
    
  float weight;
  

  u_int32_t getTotalSize(){
    return  
           1
           +
            
           1
           +
            
           4
           +
           ;
           0;
  }

  void serializeCopy(uint8_t *addrPtr)
  {
    uint32_t size;
    

    
    memcpy(addrPtr,&name
,1);
    addrPtr += 1;

    

    

    
    memcpy(addrPtr,&height
,1);
    addrPtr += 1;

    

    

    
    memcpy(addrPtr,&weight,4);
    addrPtr += 4;

    

    
  }

  void deserialize(uint8_t *rbuf) {
    uint32_t size;
    

    
    memcpy(&name
,rbuf,1);
    rbuf += 1;

    

    

    
    memcpy(&height
,rbuf,1);
    rbuf += 1;

    

    

    
    memcpy(&weight,rbuf,4);
    rbuf += 4;

    

    
  }


private:
  std::string type_name = "";
};
}
}

namespace message_traits
{

template<>
struct TypeName<*> {
  static const char* value()
  {
    return "";
  }
};

}
