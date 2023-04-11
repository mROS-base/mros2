#ifndef _{{msg.PKG}}_MSG_{{msg.NAME}}_H
#define _{{msg.PKG}}_MSG_{{msg.NAME}}_H

#include <iostream>
#include <string>
{%- set ns = namespace(break=0) -%}
{%- for def_data in msg.def %}
{%- if def_data.isArray %}
{%- if def_data.boundedArray == 0 %}
{%- if ns.break == 0 %}
#include <vector>
{%- set ns.break = ns.break + 1 -%}
{%- endif %}
{%- endif %}
{%- endif %}
{%- endfor %}

{%- set ns = namespace(break=0) -%}
{%- for def_data in msg.def%}
{%- if def_data.boundedArray %}
{%- if ns.break == 0 %}
#include <array>
{%- set ns.break = ns.break + 1 -%}
{%- endif %}
{%- endif %}
{%- endfor %}

{%- for dependingFileName in msg.dependingFileNames%}
#include "{{dependingFileName}}"
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
  uint32_t idxSerialized = 0;

  typedef std::pair<bool, uint32_t> FragCopyReturnType;

  template <class T>
  uint32_t copyPrimToFragBufLocal(uint8_t*& addrPtr,
                                  const uint32_t cntPub,
                                  const uint32_t size,
                                  const T& data)
  {
    uint32_t lenPad = (0 == (cntPub % sizeof(T))) ?
      0 : (sizeof(T) - (cntPub % sizeof(T))); // this doesn't get along with float128.
    if ( size < sizeof(T) ) {
      // There are no enough space.
      return 0;
    }
    // Put padding space
    for(int i = 0; i < lenPad; i++){
      *addrPtr = 0;
      addrPtr += 1;
    }
    // Store serialzed value.
    memcpy(addrPtr, &data, sizeof(T));
    addrPtr += sizeof(T);

    return sizeof(T) + lenPad;
  }

  template<class T>
  FragCopyReturnType copyArrayToFragBufLocal(uint8_t*& addrPtr,
                                             const uint32_t size,
                                             T& data,
                                             uint32_t& cntPubMemberLocal)
  {
    uint32_t pubDataSize = data.size();
    uint32_t cntLocalFrag = 0;

    if (cntPubMemberLocal < sizeof(uint32_t)) {
      if (size < sizeof(uint32_t)) {
        return {false, 0};
      }
      memcpy(addrPtr, &pubDataSize, sizeof(uint32_t));
      addrPtr += sizeof(uint32_t);
      cntPubMemberLocal += sizeof(uint32_t);
      cntLocalFrag += sizeof(uint32_t);
    }

    uint32_t cntFrag = (cntPubMemberLocal - sizeof(uint32_t));
                       // cntPubMemberLocal > 4 here
    uint32_t tmp = std::min(pubDataSize - cntFrag, size - cntLocalFrag);
    if (0 < tmp) {
      memcpy(addrPtr, data.data() + cntFrag, tmp);
      addrPtr += tmp;
      cntPubMemberLocal += tmp;
      cntLocalFrag += tmp;
    }

    return {(cntPubMemberLocal - sizeof(uint32_t)) >= pubDataSize, cntLocalFrag};
  }

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
    {% if def_data.isArray%}
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

    for(int i=0; i<arraySize ; i++){
      tmpPub = {{def_data.typeName}}[i].copyToBuf(addrPtr);
      cntPub += tmpPub;
      addrPtr += tmpPub;
    }
    }

    {% else %}
    tmpPub = {{def_data.typeName}}.copyToBuf(addrPtr);
    cntPub += tmpPub;
    addrPtr += tmpPub;
    {% endif %}
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

  uint32_t copyFromBuf(const uint8_t *addrPtr) {
    uint32_t tmpSub = 0;
    uint32_t arraySize;
    uint32_t stringSize;

    {% for def_data in msg.def %}
    {% if def_data.isCustomType%}
    {% if def_data.isArray %}
    {
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        addrPtr += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    memcpy(&arraySize,addrPtr,4);
    addrPtr += 4;    
    cntSub += 4;
    for(int i=0;i<arraySize;i++){
      {{def_data.cppType}} buf;
      tmpSub = buf.copyFromBuf(addrPtr);
      {{def_data.typeName}}.push_back(buf);
      addrPtr += tmpSub;
      cntSub += tmpSub;
    }
    }
    {% else %}
    tmpSub = {{def_data.typeName}}.copyFromBuf(addrPtr);
    cntSub += tmpSub;
    addrPtr += tmpSub;
    {% endif %}

    {% elif def_data.boundedArray%}
    {
    {%if def_data.size==2 %}
    if (cntSub%4 >0 and 2 <= (4-(cntSub%4))){
      for (int i=0; i<(4-(cntSub%4))-{{def_data.size}}; i++){
        addrPtr += 1;
      }
      cntSub += (4-(cntSub%4))-{{def_data.size}}; 
    }else if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
          addrPtr += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==4 %}
    if (cntSub%4 > 0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        addrPtr += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==8 %}
    if (cntSub%8 > 0){
      for(int i=0; i<(8-(cntSub%8)) ; i++){
        addrPtr += 1;
      }   
      cntSub += 8-(cntSub%8);
    }
    {% endif %}
    for(int i=0;i<{{def_data.boundedArray}};i++){
      {{def_data.cppType}} buf;
      memcpy(&buf,addrPtr,{{def_data.size}});
      {{def_data.typeName}}[i] = buf;
      addrPtr += {{def_data.size}};
      cntSub += {{def_data.size}};
    }
    }
    {% elif def_data.isArray %}
    {
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        addrPtr += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    memcpy(&arraySize,addrPtr,4);
    addrPtr += 4;    
    cntSub += 4;

    {%if def_data.size==8 %}
    if (cntSub%8 > 0){
      for(int i=0; i<(8-(cntSub%8)) ; i++){
        addrPtr += 1;
      }   
      cntSub += 8-(cntSub%8);
    }
    {% endif %}

    {{def_data.typeName}}.reserve(arraySize);
    
    {% if def_data.cppType == "string" %}
    for(int i=0;i<arraySize;i++){
      if (cntSub%4 >0){
        for(int j=0; j<(4-(cntSub%4)) ; j++){
          addrPtr += 1;
        }
        cntSub += 4-(cntSub%4);
      }
      memcpy(&stringSize, addrPtr, 4);
      addrPtr += 4;
      cntSub += 4;
      string buf;
      buf.resize(stringSize);
      memcpy(&buf[0],addrPtr,stringSize);
      {{def_data.typeName}}.push_back(buf);
      addrPtr += stringSize;
      cntSub += stringSize;
    }

    {% else %}
    for(int i=0;i<arraySize;i++){
      {{def_data.cppType}} buf;
      memcpy(&buf,addrPtr,{{def_data.size}});
      {{def_data.typeName}}.push_back(buf);
      addrPtr += {{def_data.size}};
      cntSub += {{def_data.size}};
    }
    {% endif %}
    }
    {% elif def_data.cppType == "string"%}
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        addrPtr += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    memcpy(&stringSize, addrPtr, 4);
    addrPtr += 4;
    cntSub += 4;
    {{def_data.typeName}}.resize(stringSize);
    memcpy(&{{def_data.typeName}}[0],addrPtr,stringSize);
    addrPtr += stringSize;
    cntSub += stringSize;

    {% elif def_data.cppType == "header"%}
    if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        addrPtr += 1;
      }
      cntSub += 4-(cntSub%4);
    }
    memcpy(&sec,addrPtr,4);
    addrPtr += 4;
    cntSub += 4;

    memcpy(&nanosec,addrPtr,4);
    addrPtr += 4;
    cntSub += 4;

    memcpy(&stringSize, addrPtr, 4);
    addrPtr += 4;
    cntSub += 4;
    frame_id.resize(stringSize);
    memcpy(&frame_id[0],addrPtr,stringSize);
    addrPtr += stringSize;
    cntSub += stringSize;

    {% else %}
    {%if def_data.size==2 %}
    if (cntSub%4 >0 and 2 <= (4-(cntSub%4))){
      for (int i=0; i<(4-(cntSub%4))-{{def_data.size}}; i++){
        addrPtr += 1;
      }
      cntSub += (4-(cntSub%4))-{{def_data.size}}; 
    }else if (cntSub%4 >0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
          addrPtr += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==4 %}
    if (cntSub%4 > 0){
      for(int i=0; i<(4-(cntSub%4)) ; i++){
        addrPtr += 1;
      }   
      cntSub += 4-(cntSub%4);
    }
    {% elif def_data.size==8 %}
    if (cntSub%8 > 0){
      for(int i=0; i<(8-(cntSub%8)) ; i++){
        addrPtr += 1;
      }   
      cntSub += 8-(cntSub%8);
    }
    {% endif %}
    memcpy(&{{def_data.typeName}},addrPtr,{{def_data.size}});
    addrPtr += {{def_data.size}};
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
    uint32_t tmpCntPub = cntPub;
    cntPub = 0;
    return tmpCntPub ;
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
    tmp = 4 // CDR encoding version.
          + calcRawTotalSize();
    tmp += ( 0 == (tmp % 4) ? // Padding
	     0 : (4 - (tmp % 4)) );
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

  FragCopyReturnType  copyToFragBuf(uint8_t *addrPtr, uint32_t size)
  {
    // TODO: store template code here
    return {false, 0};
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
