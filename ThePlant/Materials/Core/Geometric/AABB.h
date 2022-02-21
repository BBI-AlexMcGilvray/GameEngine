#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Math/Headers/Vector3.h"

#include "Core/Geometric/AABR.h"

namespace Core {
namespace Geometric {

// equivalent to Box, but does can't be rotated
  struct AABB
  {
    Math::Float3 dimensions;
    Math::Vector3<bool> infinite;

    AABB()
    : AABB(Math::Float3(1.0f))
    {}

    AABB(const Math::Vector3<bool>& infinite)
    : AABB(Math::Float3(1.0f), infinite)
    {}

    AABB(const Math::Float3& dimensions, const Math::Vector3<bool>& infinite = Math::Vector3<bool>(false))
    : dimensions(dimensions)
    , infinite(infinite)
    {
      VERIFY(dimensions.X >= 0.0f);
      VERIFY(dimensions.Y >= 0.0f);
      VERIFY(dimensions.Z >= 0.0f);
    }

    AABB(const AABR& aabr, const Math::Vector3<bool>& infinite)
    : dimensions(aabr.dimensions, 0.0f)
    , infinite(infinite)
    {}

    AABB(const AABR& aabr)
    : dimensions(aabr.dimensions, 0.0f)
    , infinite(aabr.infinite, false)
    {}

    AABB(const AABB&) = default;
    AABB(AABB&&) = default;
    AABB& operator=(const AABB&) = default;
    AABB& operator=(AABB&&) = default;

    bool operator==(const AABB& other) const { return dimensions == other.dimensions; }
    bool operator!=(const AABB& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core