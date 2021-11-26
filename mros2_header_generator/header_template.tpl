#ifndef _{{msg.PKG}}_MSG_{{msg.NAME}}_H
#define _{{msg.PKG}}_MSG_{{msg.NAME}}_H

#include <iostream>
#include <string>

using namespace std;

namespace {{msg.pkg}}
{
namespace msg
{
class {{msg.name}}
{
public:
  {%for def_data in msg.def %}  
  {%if def_data.isArray %}std::vector<{{def_data.cppType}}>{% else %}{{def_data.cppType}}{% endif %} {{def_data.typeName}};
  {% endfor %}

  uint32_t getTotalSize(){
    return {%for def_data in msg.def %} 
           {{def_data.size}}
           +
           {%endfor%}
           0;
  }

  void copyToBuf(uint8_t *addrPtr)
  {
    uint32_t size;
    {%for def_data in msg.def %}

    {% if def_data.isArray%}{
      size = {{def_data.typeName}}.size();
      memcpy(addrPtr,&size,4);
      addrPtr += 4;
      const {{def_data.cppType}}* ptr = {{def_data.typeName}}.data();
      for(int i=0; i<size ; i++){
        memcpy(addrPtr, &(ptr[i]),{{def_data.size}});
        addrPtr += {{def_data.size}};
      }
    }

    {% else %}
    memcpy(addrPtr,&{{def_data.typeName}},{{def_data.size}});
    addrPtr += {{def_data.size}};

    {% endif %}

    {% endfor %}
  }

  void deserialize(uint8_t *rbuf) {
    uint32_t size;
    {% for def_str in msg.def %}

    {% if def_str.isArray%}{
      uint32_t size;
      memcpy(&size,rbuf,4);
      rbuf += 4;
      {{def_str.typeName}}.reserve(size);
      for(int i=0;i<size;i++){
        {{def_str.cppType}} buf;
        memcpy(&buf,rbuf,{{def_str.size}});
        {{def_str.typeName}}.push_back(buf);
        rbuf += {{def_str.size}};
      }
    }

    {% else %}
    memcpy(&{{def_str.typeName}},rbuf,{{def_str.size}});
    rbuf += {{def_str.size}};

    {% endif %}

    {% endfor %}
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
