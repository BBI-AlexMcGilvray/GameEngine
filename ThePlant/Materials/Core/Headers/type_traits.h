#pragma once

#include <type_traits>

namespace Core {
template <typename TYPE, int INDEX, typename ...ALL_TYPES>
struct type_index_check {};

template <typename TYPE, int INDEX, typename FIRST, typename ...REST>
struct type_index_check<TYPE, INDEX, FIRST, REST...>
{
    static constexpr std::size_t value = std::is_same<TYPE, FIRST>::value ? INDEX : type_index_check<TYPE, INDEX + 1, REST...>::value;
};

template <typename TYPE, int INDEX, typename ONLY>
struct type_index_check<TYPE, INDEX, ONLY>
{
    static constexpr std::size_t value = std::is_same<TYPE, ONLY>::value ? INDEX : -1;
};

template <typename TYPE, typename ...ALL_TYPES>
struct type_index
{
    static constexpr std::size_t value = type_index_check<TYPE, 0, ALL_TYPES...>::value;
};
} // namespace Core