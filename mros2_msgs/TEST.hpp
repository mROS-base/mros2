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
struct TypeName<TEST*>
{
    static const char* value()
    {
        return "TEST";
    }
};

}
