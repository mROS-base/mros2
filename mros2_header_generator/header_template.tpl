#ifndef _{{msg.PKG}}_MSG_{{msg.NAME}}_H
#define _{{msg.PKG}}_MSG_{{msg.NAME}}_H

#include <iostream>
#include <string>
{%- set break = 0 %}
{%- for def_data in msg.def %}
{%- if def_data.isArray %}
{%- if def_data.boundedArray == 0 %}
{%- if break == 0 %}
#include <vector>
{%- set break = 1 %}
{%- endif %}
{%- endif %}
{%- endif %}
{%- endfor %}

{%- set break = 0 %}
{%- for def_data in msg.def%}
{%- if def_data.boundedArray %}
{%- if break == 0 %}
#include <array>
{%- set break = 1 %}
{%- endif %}
{%- endif %}
{%- endfor %}

{%- for dependingFileName in msg.dependingFileNames%}
#include "../../{{dependingFileName}}"
{%- endfor%}

using namespace std;

namespace {{msg.pkg}}
{
namespace msg
{
class {{msg.name}}
{
public:
  uint32_t cntPub = 0;
  uint32_t cntSub = 0;

  {%for def_data in msg.def %}  
  {%if def_data.boundedArray %}std::array<{{def_data.cppType}}, {{def_data.boundedArray}}>{% elif def_data.isArray %}std::vector<{{def_data.cppType}}>{% elif def_data.cppType == "header" %}int32_t sec; uint32_t nanosec; string frame_id;{% else %}{{def_data.cppType}}{% endif %}{%if def_data.cppType != "header" %} {{def_data.typeName}};{%endif%}
  {% endfor %}

  uint32_t copyToBuf(uint8_t *addrPtr)
  {
    uint32_t tmpPub = 0;
    uint32_t arraySize;
    uint32_t stringSize;
    {%for def_data in msg.def %}
    {% if def_data.isCustomType%}
    tmpPub = {{def_data.typeName}}.copyToBuf(addrPtr);
    cntPub += tmpPub;
    addrPtr += tmpPub;

    {% elif def_data.boundedArray%}
    {
    {%if def_data.size==2%}
    if (cntPub%4 >0 && 2 <= (4-(cntPub%4))){
      for (int i=0; i<(4-(cntPub%4))-2; i++){
      *addrPtr = 0;
      addrPtr += 1;
      }
      cntPub += (4-(cntPub%4))-2; 
    } else if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }   
      cntPub += 4-(cntPub%4);
    }
    {% elif def_data.size==4 %}
    if (cntPub%4 > 0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }   
      cntPub += 4-(cntPub%4);
    }
    {% elif def_data.size==8 %}
    if (cntPub%8 > 0){
      for(int i=0; i<(8-(cntPub%8)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }   
      cntPub += 8-(cntPub%8);
    }
    {% endif %}
    const {{def_data.cppType}}* ptr = {{def_data.typeName}}.data();
    for(int i=0; i<{{def_data.boundedArray}} ; i++){
      memcpy(addrPtr, &(ptr[i]),{{def_data.size}});
      addrPtr += {{def_data.size}};
      cntPub += {{def_data.size}};
    }
    }
    {% elif def_data.isArray %}
    {
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    arraySize = {{def_data.typeName}}.size();
    memcpy(addrPtr,&arraySize,4);
    addrPtr += 4;
    cntPub += 4;

    {% if def_data.size==8 %}
    if (cntPub%8 > 0){
      for(int i=0; i<(8-(cntPub%8)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }   
      cntPub += 8-(cntPub%8);
    }
    {% endif %}

    {% if def_data.cppType == "string"%}
    const string* ptr = {{def_data.typeName}}.data();

    for(int i=0; i<arraySize ; i++){
      if (cntPub%4 >0){
      for(int j=0; j<(4-(cntPub%4)) ; j++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
      }
      stringSize = (ptr[i]).size();
      memcpy(addrPtr,&stringSize,4);
      addrPtr += 4;
      cntPub += 4;
      memcpy(addrPtr,(ptr[i]).c_str(),stringSize);
      addrPtr += stringSize;
      cntPub += stringSize;
    }

    {% else %}
    const {{def_data.cppType}}* ptr = {{def_data.typeName}}.data();

    for(int i=0; i<arraySize ; i++){
      memcpy(addrPtr, &(ptr[i]),{{def_data.size}});
      addrPtr += {{def_data.size}};
      cntPub += {{def_data.size}};
    }
    {% endif %}
    }
    {% elif def_data.cppType == "string"%}
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    stringSize = {{def_data.typeName}}.size();
    memcpy(addrPtr,&stringSize,4);
    addrPtr += 4;
    cntPub += 4;
    memcpy(addrPtr,{{def_data.typeName}}.c_str(),stringSize);
    addrPtr += stringSize;
    cntPub += stringSize;

    {% elif def_data.cppType == "header"%}
    if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }

    memcpy(addrPtr,&sec,4);
    addrPtr += 4;
    cntPub += 4;

    memcpy(addrPtr,&nanosec,4);
    addrPtr += 4;
    cntPub += 4;

    stringSize = frame_id.size();
    memcpy(addrPtr,&stringSize,4);
    addrPtr += 4;
    cntPub += 4;
    memcpy(addrPtr,frame_id.c_str(),stringSize);
    addrPtr += stringSize;
    cntPub += stringSize;
  
    {% else %}
    {%if def_data.size==2%}
    if (cntPub%4 >0 && 2 <= (4-(cntPub%4))){
      for (int i=0; i<(4-(cntPub%4))-2; i++){
      *addrPtr = 0;
      addrPtr += 1;
      }
      cntPub += (4-(cntPub%4))-2; 
    } else if (cntPub%4 >0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }   
      cntPub += 4-(cntPub%4);
    }
    {% elif def_data.size==4 %}
    if (cntPub%4 > 0){
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }   
      cntPub += 4-(cntPub%4);
    }
    {% elif def_data.size==8 %}
    if (cntPub%8 > 0){
      for(int i=0; i<(8-(cntPub%8)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }   
      cntPub += 8-(cntPub%8);
    }
    {% endif %}
    memcpy(addrPtr,&{{def_data.typeName}},{{def_data.size}});
    addrPtr += {{def_data.size}};
    cntPub += {{def_data.size}};

    {% endif %}
    {% endfor %}

    return cntPub;
  }

  uint32_t copyFromBuf(const uint8_t *rbuf) {
    uint32_t tmpSub = 0;
    uint32_t arraySize;
    uint32_t stringSize;

    {% for def_data in msg.def %}
    {% if def_data.isCustomType%}
    tmpSub = {{def_data.typeName}}.copyFromBuf(rbuf);
    cntSub += tmpSub;
    rbuf += tmpSub;

    {% elif def_data.boundedArray%}
    {
    {%if def_data.size==2 %}
    if (cntSub%4 >0 and 2 <= (4-(cntSub%4))){
      for (int i=0; i<(4-(cntSub%4))-{{def_data.size}}; i++){
        rbuf += 1;
      }
      cntSub += (4-(cntSub%4))-{{def_data.size}}; 
    }else if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==4 %}
    if (cntSub%4 > 0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        rbuf += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==8 %}
    if (cntSub%8 > 0){
      for(int i=0; i<(8-(cntSub%8)) ; i++){
        rbuf += 1;
      }   
      cntSub += 8-(cntSub%8);
    }
    {% endif %}
    for(int i=0;i<{{def_data.boundedArray}};i++){
      {{def_data.cppType}} buf;
      memcpy(&buf,rbuf,{{def_data.size}});
      {{def_data.typeName}}[i] = buf;
      rbuf += {{def_data.size}};
      cntSub += {{def_data.size}};
    }
    }
    {% elif def_data.isArray %}
    {
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        rbuf += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    memcpy(&arraySize,rbuf,4);
    rbuf += 4;    
    cntSub += 4;

    {%if def_data.size==8 %}
    if (cntSub%8 > 0){
      for(int i=0; i<(8-(cntSub%8)) ; i++){
        rbuf += 1;
      }   
      cntSub += 8-(cntSub%8);
    }
    {% endif %}

    {{def_data.typeName}}.reserve(arraySize);
    
    {% if def_data.cppType == "string" %}
    for(int i=0;i<arraySize;i++){
      if (cntSub%4 >0){
        for(int j=0; j<(4-(cntSub%4)) ; j++){
          rbuf += 1;
        }
        cntSub += 4-(cntSub%4);
      }
      memcpy(&stringSize, rbuf, 4);
      rbuf += 4;
      cntSub += 4;
      string buf;
      buf.resize(stringSize);
      memcpy(&buf[0],rbuf,stringSize);
      {{def_data.typeName}}.push_back(buf);
      rbuf += stringSize;
      cntSub += stringSize;
    }

    {% else %}
    for(int i=0;i<arraySize;i++){
      {{def_data.cppType}} buf;
      memcpy(&buf,rbuf,{{def_data.size}});
      {{def_data.typeName}}.push_back(buf);
      rbuf += {{def_data.size}};
      cntSub += {{def_data.size}};
    }
    {% endif %}
    }
    {% elif def_data.cppType == "string"%}
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        rbuf += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    memcpy(&stringSize, rbuf, 4);
    rbuf += 4;
    cntSub += 4;
    {{def_data.typeName}}.resize(stringSize);
    memcpy(&{{def_data.typeName}}[0],rbuf,stringSize);
    rbuf += stringSize;
    cntSub += stringSize;

    {% elif def_data.cppType == "header"%}
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        rbuf += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    memcpy(&sec,rbuf,4);
    rbuf += 4;
    cntSub += 4;

    memcpy(&nanosec,rbuf,4);
    rbuf += 4;
    cntSub += 4;

    memcpy(&stringSize, rbuf, 4);
    rbuf += 4;
    cntSub += 4;
    frame_id.resize(stringSize);
    memcpy(&frame_id[0],rbuf,stringSize);
    rbuf += stringSize;
    cntSub += stringSize;

    {% else %}
    {%if def_data.size==2 %}
    if (cntSub%4 >0 and 2 <= (4-(cntSub%4))){
      for (int i=0; i<(4-(cntSub%4))-{{def_data.size}}; i++){
        rbuf += 1;
      }
      cntSub += (4-(cntSub%4))-{{def_data.size}}; 
    }else if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
          rbuf += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==4 %}
    if (cntSub%4 > 0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        rbuf += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==8 %}
    if (cntSub%8 > 0){
      for(int i=0; i<(8-(cntSub%8)) ; i++){
        rbuf += 1;
      }   
      cntSub += 8-(cntSub%8);
    }
    {% endif %}
    memcpy(&{{def_data.typeName}},rbuf,{{def_data.size}});
    rbuf += {{def_data.size}};
    cntSub += {{def_data.size}};
    {% endif %}
    {% endfor %}

    return cntSub;
  }

   void memAlign(uint8_t *addrPtr){
    if (cntPub%4 > 0){
      addrPtr += cntPub;
      for(int i=0; i<(4-(cntPub%4)) ; i++){
        *addrPtr = 0;
        addrPtr += 1;
      }
      cntPub += 4-(cntPub%4);
    }
    return;
  }

  uint32_t getTotalSize(){
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