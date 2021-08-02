#include "Core/Reflection/Reflectable.h"

// Plain Old Data
#define POD(type_name, ...)\
struct type_name\
{\
    REFLECTABLE(__VA_ARGS__)\
};

// Plain Old Data Extension
// this will not work since the reflector class will try to do type_name::FOO, but it would need to be parent_type::FOO for the base class's fields
// maybe try anyways?
// #define POD_EXTENSION(type_name, parent_type, ...)\
// struct type_name : public parent_type\
// {\
//     REFLECTABLE(__VA_ARGS__)\
// };

#define STRUCT(type_name, ...)\
struct type_name\
{\
    REFLECTABLE(__VA_ARGS__)\

#define CLASS(type_name, ...)\
class type_name\
{\
    REFLECTABLE(__VA_ARGS__)\
