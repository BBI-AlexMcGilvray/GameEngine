#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Geometric {

  // CAN'T be rotated - at least not yet. keep it simple for now
  struct Box
  {
    Math::Float3 dimensions;

    Box()
    : Box(Math::Float3(1.0f))
    {}

    Box(const Math::Float3& dimensions)
    : dimensions(dimensions)
    {
      VERIFY(dimensions.X >= 0.0f);
      VERIFY(dimensions.Y >= 0.0f);
      VERIFY(dimensions.Z >= 0.0f);
    }

    Box(const Box&) = default;
    Box(Box&&) = default;
    Box& operator=(const Box&) = default;
    Box& operator=(Box&&) = default;

    bool operator==(const Box& other) const { return dimensions == other.dimensions; }
    bool operator!=(const Box& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core