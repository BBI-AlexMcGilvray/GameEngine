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
    using Point2D = Math::Float2;
    using Point3D = Math::Float3;
    using Shape2D = std::variant<Circle, Line2D, Point2D, Rectangle>;
    using Shape3D = std::variant<Box, Line2D, Plane, Point3D, Sphere>;

    template <typename SHAPE>
    struct ShapeOrientation
    {
        SHAPE shape;
        Transform orientation;
    };
} // namespace Geometric
} // namespace Core