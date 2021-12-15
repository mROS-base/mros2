#include <string>

class TEST
{
public:
  static std::string getTypeName();
  std::string data;
private:
  std::string type_name = "TEST";
};

namespace message_traits
{

template<>
struct TypeName<TEST*> {
  static const char* value()
  {
    return "TEST";
  }
};

}

/* Work in Progress: for custom message
template mros2::Publisher mros2::Node::create_publisher<TEST>(std::string topic_name, int qos);
template mros2::Subscriber mros2::Node::create_subscription(std::string topic_name, int qos, void (*fp)(TEST*));
template void mros2::Publisher::publish(TEST& msg);
*/