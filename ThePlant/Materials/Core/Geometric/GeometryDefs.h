#pragma once

#include <variant>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Geometric/Box.h"
#include "Core/Geometric/Circle.h"
#include "Core/Geometric/Line2D.h"
#include "Core/Geometric/Line3D.h"
#include "Core/Geometric/Plane.h"
#include "Core/Geometric/Rectangle.h"
#include "Core/Geometric/Sphere.h"
#include "Core/Geometric/Transform.h"

namespace Core {
namespace Geometric {
    struct Point{}; // just used to signify we use the 'orientation's position
    
    using Point2D = Math::Float2;
    using Point3D = Math::Float3;
    using Shape2D = std::variant<Circle, Line2D, Point, Rectangle>;
    using Shape3D = std::variant<Box, Line2D, Plane, Point, Sphere>;

    template <typename SHAPE>
    struct ShapeOrientation
    {
        SHAPE shape;
        Transform orientation;
    };
    
#if DEBUG
#define VERIFY_2D(SHAPE_ORIENTATION) VERIFY(SHAPE_ORIENTATION.orientation.GetPosition().Z == 0.0f);
#else
#define VERIFY_2D(SHAPE_ORIENTATION)
#endif
} // namespace Geometric
} // namespace Core