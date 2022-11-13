#pragma once

#include "Core/Reflection/Reflectable.h"

namespace Core {
namespace Geometric {
    struct Spot2D
    {
        NOTHING_REFLECTABLE();

        bool operator==(const Spot2D& other) const { return true; }
        bool operator!=(const Spot2D& other) const { return !(*this == other); }
    }; // just used to signify we use the 'orientation's position

    struct Spot3D
    {
        NOTHING_REFLECTABLE();
        
        bool operator==(const Spot3D& other) const { return true; }
        bool operator!=(const Spot3D& other) const { return !(*this == other); }
    }; // just used to signify we use the 'orientation's position
}// namespace Geometric
}// namespace Core