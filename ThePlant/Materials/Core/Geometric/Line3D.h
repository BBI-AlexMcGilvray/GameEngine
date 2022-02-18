#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Geometric {
  struct Line3D
  {
    Math::Float3 direction; // direction should always be normalized
    float length;
    bool infinite;

    Line3D()
    : Line3D(Math::Float3(1.0f, 0.0f, 0.0f))
    {}

    Line3D(const float& length)
    : Line3D(Math::Float3(1.0f, 0.0f, 0.0f), length)
    {}

    Line3D(const Math::Float3 &direction)
    : direction(Math::Normalize(direction))
    , infinite(true)
    {}

    Line3D(const Math::Float3 &direction, const float& length)
    : direction(Math::Normalize(direction))
    , length(length)
    , infinite(false)
    {
      VERIFY(infinite || length >= 0.0f);
    }

    Line3D(const Math::Float3 &direction, bool infinite, const float& length)
    : direction(Math::Normalize(direction))
    , length(length)
    , infinite(infinite)
    {
      VERIFY(infinite || length >= 0.0f);
    }

    Line3D(const Line3D&) = default;
    Line3D(Line3D&&) = default;
    Line3D& operator=(const Line3D&) = default;
    Line3D& operator=(Line3D&&) = default;

    bool operator==(const Line3D& other) const
    {
      return direction == other.direction &&
              (length == other.length || infinite == other.infinite);
    }
    bool operator!=(const Line3D& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core