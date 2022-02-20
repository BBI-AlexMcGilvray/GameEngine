#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Geometric {
  struct Line3D
  {
    Math::Float3 line;
    bool infinite;

    Line3D()
    : Line3D(Math::Float3(1.0f, 1.0f, 1.0f), false)
    {}

    Line3D(const Math::Float3 &line, bool infinite)
    : line(line)
    , infinite(infinite)
    {}

    Line3D(const Line3D&) = default;
    Line3D(Line3D&&) = default;
    Line3D& operator=(const Line3D&) = default;
    Line3D& operator=(Line3D&&) = default;

    bool operator==(const Line3D& other) const
    {
      return line == other.line && infinite == other.infinite;
    }
    bool operator!=(const Line3D& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core