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

template <typename T, template <typename ...> typename TEMPLATE>
struct is_specialization_of : std::false_type{};

template <template <typename ...> typename TEMPLATE, typename ...ARGS>
struct is_specialization_of<TEMPLATE<ARGS...>, TEMPLATE> : std::true_type{};