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
    // using Shape2D = std::variant<Circle, Line2D, Point, Rectangle>; // defined in Plane.h, maybe we want a '2DGeometryDefs.h' file to hold it and be referenced by both?
    using Shape3D = std::variant<Box, Line2D, Plane, Point, Sphere>;

    template <typename SHAPE>
    struct ShapeOrientation
    {
        Transform orientation;
        SHAPE shape;

        ShapeOrientation() = delete;

        ShapeOrientation(const Transform& orientation, const SHAPE& shape)
        : orientation(orientation)
        , shape(shape)
        {}

        ShapeOrientation(const ShapeOrientation&) = default;
        ShapeOrientation(ShapeOrientation&&) = default;
        ShapeOrientation& operator=(const ShapeOrientation&) = default;
        ShapeOrientation& operator=(ShapeOrientation&&) = default;
    };

    using ShapeOrientation2D = ShapeOrientation<Shape2D>;
    using ShapeOrientation3D = ShapeOrientation<Shape3D>;
    
#if DEBUG
#define VERIFY_2D(SHAPE_ORIENTATION) VERIFY(SHAPE_ORIENTATION.orientation.GetPosition().Z == 0.0f);
#else
#define VERIFY_2D(SHAPE_ORIENTATION)
#endif
} // namespace Geometric
} // namespace Core