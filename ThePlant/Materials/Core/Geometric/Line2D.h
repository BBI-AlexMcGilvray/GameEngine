#pragma once

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Quaternion.h"

namespace Core {
namespace Geometric {
  struct Line2D
  {
    Math::Float2 direction;
    float length;
    bool infinite;

    Line2D()
    : Line2D(Math::Float2(1.0f, 0.0f))
    {}

    Line2D(const Math::Float2 &direction)
    : direction(direction)
    , infinite(true)
    {}

    Line2D(const Math::Float2 &direction, const float& length)
    : direction(direction)
    , length(length)
    , infinite(false)
    {}
    
    Line2D(const Line2D&) = default;
    Line2D(Line2D&&) = default;
    Line2D& operator=(const Line2D&) = default;
    Line2D& operator=(Line2D&&) = default;

    bool operator==(const Line2D& other) const
    {
      return direction == other.direction &&
              (length == other.length || infinite == other.infinite);
    }
    bool operator!=(const Line2D& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core