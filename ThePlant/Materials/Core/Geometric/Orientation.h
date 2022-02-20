#pragma once

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Geometric {
  // Should we have an 'orientation' struct that holds position, rotation, and scale?
  // makes it cheaper to copy around and smaller for when we don't need a full 'transform'
  struct Orientation
  {
    Core::Math::Float3 position;
    Core::Math::FQuaternion rotation;
    Core::Math::Float3 scale;

    // create constructor for each variation of data (position, rotation, scale)
    Orientation()
    : Orientation(Core::Math::Float3(0.0f))
    {}

    Orientation(Core::Math::FQuaternion rotation, Core::Math::Float3 scale = Core::Math::Float3(1.0f))
    : Orientation(Core::Math::Float3(0.0f), rotation, scale)
    {}

    Orientation(Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(), Core::Math::Float3 scale = Core::Math::Float3(1.0f))
    : position(position)
    , rotation(rotation)
    , scale(scale)
    {}

    Orientation(const Orientation&) = default;
    Orientation(Orientation&&) = default;

    Orientation &operator=(const Orientation&) = default;
    Orientation& operator=(Orientation&&) = default;

    bool operator==(const Orientation& other) const
    {
        return position == other.position &&
                rotation == other.rotation &&
                scale == other.scale;
    }
    bool operator!=(const Orientation& other) const { return !(*this == other); }
  };
}// namespace Geometric
}// namespace Core