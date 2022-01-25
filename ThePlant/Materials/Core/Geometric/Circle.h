#pragma once

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
    {}

    Circle(const Circle&) = default;
    Circle(Circle&&) = default;
    Circle& operator=(const Circle&) = default;
    Circle& operator=(Circle&&) = default;

    bool operator==(const Circle& other) const { return radius == other.radius; }
    bool operator!=(const Circle& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core