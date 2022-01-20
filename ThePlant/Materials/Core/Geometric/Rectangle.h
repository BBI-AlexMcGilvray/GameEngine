#pragma once

#include "Core/Math/Headers/Vector2.h"

namespace Core {
namespace Geometric {
  // should this be split out to be made up of a 'box (width and height)' and a transform?
  // maybe only if that ends up being actually useful 
  struct Rectangle
  {
    Math::Float2 dimensions;

    Rectangle()
    : Rectangle(Math::Float2(1.0f))
    {}

    Rectangle(const Math::Float2& dimensions)
    : dimensions(dimensions)
    {}

    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle& operator=(Rectangle&&) = default;

    bool operator==(const Rectangle& other) const { return dimensions == other.dimensions; }
    bool operator!=(const Rectangle& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core