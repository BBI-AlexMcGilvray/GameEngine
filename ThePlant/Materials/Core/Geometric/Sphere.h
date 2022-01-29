#pragma once

#include "Core/Debugging/Headers/Macros.h"

namespace Core {
namespace Geometric {
  struct Sphere
  {
    float radius;

    Sphere()
    : Sphere(0.5f)
    {}

    Sphere(const float& radius)
    : radius(radius)
    {
      VERIFY(radius >= 0.0f);
    }

    Sphere(const Sphere&) = default;
    Sphere(Sphere&&) = default;
    Sphere& operator=(const Sphere&) = default;
    Sphere& operator=(Sphere&&) = default;

    bool operator==(const Sphere& other) const { return radius == other.radius; }
    bool operator!=(const Sphere& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core