#pragma once

#include "Core/Debugging/Headers/Macros.h"

namespace Core {
namespace Geometric {
  struct Circle
  {
    float radius;

    Circle()
    : Circle(0.5f)
    {}

    Circle(const float& radius)
    : radius(radius)
    {
      VERIFY(radius >= 0.0f);
    }

    Circle(const Circle&) = default;
    Circle(Circle&&) = default;
    Circle& operator=(const Circle&) = default;
    Circle& operator=(Circle&&) = default;

    bool operator==(const Circle& other) const { return radius == other.radius; }
    bool operator!=(const Circle& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core