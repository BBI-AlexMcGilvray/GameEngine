#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Geometric/Circle.h"
#include "Core/Geometric/Line2D.h"
#include "Core/Geometric/Rectangle.h"

namespace Core {
namespace Geometric {
  using Shape2D = std::variant<Circle, Line2D, Rectangle>;

  struct Plane
  {
    Math::Float3 normal;
    Shape2D shape;
    bool infinite;

    Plane()
    : Plane(Math::Float3(0.0f, 0.0f, 1.0f))
    {}

    Plane(const Math::Float3& normal)
    : normal(normal)
    , infinite(true)
    {}

    Plane(const Math::Float3& normal, const Shape2D& shape)
    : normal(normal)
    , shape(shape)
    , infinite(false)
    {}

    Plane(const Plane&) = default;
    Plane(Plane&&) = default;
    Plane& operator=(const Plane&) = default;
    Plane& operator=(Plane&&) = default;

    bool operator==(const Plane& other) const
    {
      return normal == other.normal &&
              (shape == other.shape || infinite == other.infinite);
    }
    bool operator!=(const Plane& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core