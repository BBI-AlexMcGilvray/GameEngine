#pragma once

namespace Core {
namespace Geometric {
    struct Spot2D
    {
        bool operator==(const Spot2D& other) const { return true; }
        bool operator!=(const Spot2D& other) const { return !(*this == other); }
    }; // just used to signify we use the 'orientation's position

    struct Spot3D
    {
        bool operator==(const Spot3D& other) const { return true; }
        bool operator!=(const Spot3D& other) const { return !(*this == other); }
    }; // just used to signify we use the 'orientation's position
}// namespace Geometric
}// namespace Core