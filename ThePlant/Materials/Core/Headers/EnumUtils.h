#pragma once

#include <array>

#include "Core/Headers/type_traits.h"

namespace Core
{
    template<typename T, typename = std::enable_if<std::is_enum<T>::value>>
    constexpr std::underlying_type_t<T> enum_cast(const T &e)
    {
        return static_cast<std::underlying_type_t<T>>(e);
    }

    template<typename T, typename = std::enable_if<!std::is_enum<T>::value>>
    constexpr T enum_cast(const std::underlying_type_t<T> &i)
    {
        return static_cast<T>(i);
    }

    template <typename TYPE, typename ENUM, typename = typename std::enable_if_t<std::is_enum_v<ENUM>>>
    using EnumIndexedArray = std::array<TYPE, enum_cast(ENUM::Count)>;
} // namespace Core