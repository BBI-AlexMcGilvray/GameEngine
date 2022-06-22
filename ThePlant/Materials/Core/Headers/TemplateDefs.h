#pragma once

#include <type_traits>
#include <string>

namespace Core {
template<typename T>
constexpr std::string_view TemplateTypeAsString() noexcept
{
    #if defined __clang__ || defined __GNUC__
    constexpr std::string_view pretty_function{ __PRETTY_FUNCTION__ }; //returns "auto Util::TemplateToConstexprStr() [Type = MyClass]"
    constexpr auto first = pretty_function.find_first_not_of(' ', pretty_function.find_first_of(' ', pretty_function.find_first_of('=') + 1) + 1);
    constexpr auto value = pretty_function.substr(first, pretty_function.find_last_of(']') - first);
    #else
    constexpr std::string_view pretty_function{ __FUNCSIG__ }; //returns "auto __cdecl Util::TemplateToConstexprStr<class T>(void) noexcept"
    constexpr auto first = pretty_function.find_first_not_of(' ', pretty_function.find_first_of(' ', pretty_function.find_first_of('<') + 1) + 1);
    constexpr auto value = pretty_function.substr(first, pretty_function.find_last_of('>') - first);
    #endif
    constexpr auto str = value.data();
    return str;
}
}// namespace Core