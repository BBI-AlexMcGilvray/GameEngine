#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Math/Headers/Vector2.h"

namespace Core {
namespace Geometric {
    
// equivalent to Rectangle, but does can't be rotated
  struct AABR
  {
    Math::Float2 dimensions;
    Math::Vector2<bool> infinite;

    AABR()
    : AABR(Math::Float2(1.0f))
    {}

    AABR(const Math::Float2& dimensions, const Math::Vector2<bool>& infinite = Math::Vector2<bool>(false))
    : dimensions(dimensions)
    , infinite(infinite)
    {
      VERIFY(dimensions.X >= 0.0f);
      VERIFY(dimensions.Y >= 0.0f);
    }

    AABR(const AABR&) = default;
    AABR(AABR&&) = default;
    AABR& operator=(const AABR&) = default;
    AABR& operator=(AABR&&) = default;

    bool operator==(const AABR& other) const { return dimensions == other.dimensions; }
    bool operator!=(const AABR& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core