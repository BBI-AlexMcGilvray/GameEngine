#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Reflection/Reflectable.h"

#include "Core/Math/Headers/Vector2.h"

namespace Core {
namespace Geometric {
  // should this be split out to be made up of a 'box (width and height)' and a transform?
  // maybe only if that ends up being actually useful 
  struct Rectangle
  {
    REFLECTABLE(
      (Math::Float2) dimensions
    )

    Rectangle()
    : Rectangle(Math::Float2(1.0f))
    {}

    Rectangle(const Math::Float2& dimensions)
    : dimensions(dimensions)
    {
      VERIFY(dimensions.X >= 0.0f);
      VERIFY(dimensions.Y >= 0.0f);
    }

    Rectangle(const Rectangle&) = default;
    Rectangle(Rectangle&&) = default;
    Rectangle& operator=(const Rectangle&) = default;
    Rectangle& operator=(Rectangle&&) = default;

    bool operator==(const Rectangle& other) const { return dimensions == other.dimensions; }
    bool operator!=(const Rectangle& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core