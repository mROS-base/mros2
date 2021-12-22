#ifndef _{{msg.PKG}}_MSG_{{msg.NAME}}_H
#define _{{msg.PKG}}_MSG_{{msg.NAME}}_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace {{msg.pkg}}
{
namespace msg
{
class {{msg.name}}
{
public:
  uint8_t cntPub = 0;
  uint8_t cntSub = 0;
  {%for def_data in msg.def %}  
  {%if def_data.isArray %}std::vector<{{def_data.cppType}}>{% else %}{{def_data.cppType}}{% endif %} {{def_data.typeName}};
  {% endfor %}

  void copyToBuf(uint8_t *addrPtr)
  {
    {%for def_data in msg.def %}
    {% if def_data.isArray%}
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    uint32_t arraySize = {{def_data.typeName}}.size();
    memcpy(addrPtr,&arraySize,4);
    addrPtr += 4;
    cntPub += 4;
    const {{def_data.cppType}}* ptr = {{def_data.typeName}}.data();
    for(int i=0; i<arraySize ; i++){
      memcpy(addrPtr, &(ptr[i]),{{def_data.size}});
      addrPtr += {{def_data.size}};
      cntPub += {{def_data.size}};
    }

    {% elif def_data.cppType == "string"%}
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    uint32_t stringSize = {{def_data.typeName}}.size();
    memcpy(addrPtr,&stringSize,4);
    addrPtr += 4;
    cntPub += 4;
    memcpy(addrPtr,{{def_data.typeName}}.c_str(),stringSize);
    addrPtr += stringSize;
    cntPub += stringSize;

    {% else %}
    if (cntPub%4 >0 && {{def_data.size}} > 1){
      if (({{def_data.size}} <= (4-(cntPub%4)))&&({{def_data.size}}==2)){
        for (int i=0; i<(4-(cntPub%4))-{{def_data.size}}; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }
        cntPub += (4-(cntPub%4))-{{def_data.size}}; 
      } else {
        for(int i=0; i<(4-(cntPub%4)) ; i++){
          *addrPtr = 0;
          addrPtr += 1;
        }   
        cntPub += 4-(cntPub%4);   
      }
    }
    memcpy(addrPtr,&{{def_data.typeName}},{{def_data.size}});
    addrPtr += {{def_data.size}};
    cntPub += {{def_data.size}};

    {% endif %}
    {% endfor %}

    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }  
      cntPub += 4-(cntPub%4);
    }
  }

  void copyFromBuf(const uint8_t *rbuf) {
    {% for def_data in msg.def %}
    {% if def_data.isArray%}
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
    {{def_data.typeName}}.reserve(arraySize);
    for(int i=0;i<arraySize;i++){
      {{def_data.cppType}} buf;
      memcpy(&buf,rbuf,{{def_data.size}});
      {{def_data.typeName}}.push_back(buf);
      rbuf += {{def_data.size}};
      cntSub += {{def_data.size}};
    }

    {% elif def_data.cppType == "string"%}
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
    {{def_data.typeName}}.resize(stringSize);
    memcpy(&{{def_data.typeName}}[0],rbuf,stringSize);
    rbuf += stringSize;
    cntSub += stringSize;

    {% else %}
    if (cntSub%4 >0 && {{def_data.size}} > 1){
      if (({{def_data.size}} <= (4-(cntSub%4)))&&({{def_data.size}}==2)){
        for (int i=0; i<(4-(cntSub%4))-{{def_data.size}}; i++){
          rbuf += 1;
        }
        cntSub += (4-(cntSub%4))-{{def_data.size}};
      } else {
        for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
        }
        cntSub += 4-(cntSub%4);
      }
    }
    memcpy(&{{def_data.typeName}},rbuf,{{def_data.size}});
    rbuf += {{def_data.size}};
    cntSub += {{def_data.size}};
    {% endif %}
    {% endfor %}
  }

  uint8_t getTotalSize(){
    return cntPub ;
  }

private:
  std::string type_name = "{{msg.pkg}}::msg::dds_::{{msg.name}}";
};
};
}

namespace message_traits
{
template<>
struct TypeName<{{msg.pkg}}::msg::{{msg.name}}*> {
  static const char* value()
  {
    return "{{msg.pkg}}::msg::dds_::{{msg.name}}_";
  }
};
}

#endif