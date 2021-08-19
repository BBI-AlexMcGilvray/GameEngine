#pragma once

#include <type_traits>

/*
* type traits should not be in namespaces (?)
*/

template<typename T, typename = void>
struct is_iterable : std::false_type
{
};

template<typename T>
struct is_iterable<T, std::void_t<decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>> : std::true_type
{
};