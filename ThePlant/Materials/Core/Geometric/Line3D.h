#pragma once

#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Geometric {
  struct Line3D
  {
    Math::Float3 direction;
    float length;
    bool infinite;

    Line3D()
    : Line3D(Math::Float3(1.0f, 0.0f, 0.0f))
    {}

    Line3D(const Math::Float3 &direction)
    : direction(direction)
    , infinite(true)
    {}

    Line3D(const Math::Float3 &direction, const float& length)
    : direction(direction)
    , length(length)
    , infinite(infinite)
    {}

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