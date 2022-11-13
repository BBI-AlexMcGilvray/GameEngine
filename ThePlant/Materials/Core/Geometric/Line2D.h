#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Reflection/Reflectable.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/VectorFunctions.h"

namespace Core {
namespace Geometric {
  struct Line2D
  {
    REFLECTABLE(
      (Math::Float2) line,
      (bool) infinite
    )

    Line2D()
    : Line2D(Math::Float2(1.0f, 1.0f), true)
    {}

    Line2D(const Math::Float2 &line, bool infinite)
    : line(line)
    , infinite(infinite)
    {}
    
    Line2D(const Line2D&) = default;
    Line2D(Line2D&&) = default;
    Line2D& operator=(const Line2D&) = default;
    Line2D& operator=(Line2D&&) = default;

    bool operator==(const Line2D& other) const
    {
      return line == other.line && infinite == other.infinite;
    }
    bool operator!=(const Line2D& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core