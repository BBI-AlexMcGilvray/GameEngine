#include <utility>
#include <cstring>

#if __clang__// || __GNUC__
template <typename ENUM, ENUM VALUE>
constexpr bool is_valid()
{
    // When compiled with clang, `name` will contain a prettified function name,
    // including the enum value name for `V` if valid. For example:
    // "bool IsValid() [E = Fruit, V = Fruit::BANANA]" for valid enum values, or:
    // "bool IsValid() [E = Fruit, V = 10]" for invalid enum values.
    auto name = __PRETTY_FUNCTION__;

    // Find the final space character in the pretty name.
    int i = strlen(name);
    for (; i >= 0; --i) {
        if (name[i] == ' ')
        {
            break;
        }
    }

    // The character after the final space will indicate if
    // it's a valid value or not.
    char c = name[i + 1];
    if (c >= '0' && c <= '9')
    {
        return false;
    }
    return true;
}

template <typename ENUM>
constexpr int count_valid()
{
    return 0;
}

template <typename ENUM, ENUM FIRST, ENUM... REST>
constexpr int count_valid()
{
    bool firstIsValid = is_valid<ENUM, FIRST>();
    return count_valid<ENUM, REST...>() + static_cast<int>(firstIsValid);
}

template <typename ENUM, int... I>
constexpr int internal_element_count(std::integer_sequence<int, I...> unused)
{
    (void)unused;
    return count_valid<ENUM, (ENUM)I...>();
}

template <typename ENUM>
struct enum_count
{
    constexpr static int MAX_ENUM_SIZE = 500;
    static const int value = internal_element_count<ENUM>(std::make_integer_sequence<int, MAX_ENUM_SIZE>());
};
#endif