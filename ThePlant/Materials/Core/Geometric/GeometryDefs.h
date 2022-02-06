#pragma once

#include <variant>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Geometric/Box.h"
#include "Core/Geometric/Circle.h"
#include "Core/Geometric/Line2D.h"
#include "Core/Geometric/Line3D.h"
#include "Core/Geometric/Plane.h"
#include "Core/Geometric/Spot.h"
#include "Core/Geometric/Rectangle.h"
#include "Core/Geometric/Sphere.h"
#include "Core/Geometric/Transform.h"

namespace Core {
namespace Geometric {    
    using Point2D = Math::Float2;
    using Point3D = Math::Float3;
    // defined in Plane.h, maybe we want a '2DGeometryDefs.h' file to hold it and be referenced by both?
    // using Shape2D = std::variant<Circle, Line2D, Spot2D, Rectangle>;
    using Shape3D = std::variant<Box, Line3D, Plane, Spot3D, Sphere>;

    template <typename SHAPE2D>
    Plane Shape2DAsPlane(const SHAPE2D& shape_2d)
    {
        return Plane(Math::Float3(0.0f, 0.0f, 1.0f), shape_2d);
    }

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

        // to allow converting between applicable shapes
        template <typename OTHER_SHAPE>
        ShapeOrientation(const ShapeOrientation<OTHER_SHAPE>& other)
        {
            orientation = other.orientation;
            shape = other.shape;
        }
        template <typename OTHER_SHAPE>
        ShapeOrientation(ShapeOrientation<OTHER_SHAPE>&& other)
        {
            orientation = std::move(other.orientation);
            shape = std::move(other.shape);
        }
        template <typename OTHER_SHAPE>
        ShapeOrientation& operator=(const ShapeOrientation<OTHER_SHAPE>& other)
        {
            orientation = other.orientation;
            shape = other.shape;
        }
        template <typename OTHER_SHAPE>
        ShapeOrientation& operator=(ShapeOrientation<OTHER_SHAPE>&&)
        {
            orientation = std::move(other.orientation);
            shape = std::move(other.shape);
        }

        bool operator==(const ShapeOrientation& other) const
        {
            return orientation == other.orientation && shape == other.shape;
        }
        bool operator!=(const ShapeOrientation& other) const
        {
            return !(*this == other);
        }
    };

    using ShapeOrientation2D = ShapeOrientation<Shape2D>;
    using ShapeOrientation3D = ShapeOrientation<Shape3D>;
    
#if DEBUG
#define VERIFY_2D(SHAPE_ORIENTATION) VERIFY(SHAPE_ORIENTATION.orientation.GetPosition().Z == 0.0f); // we should also verify that the rotation maintains the x/y plane
#else
#define VERIFY_2D(SHAPE_ORIENTATION)
#endif
} // namespace Geometric
} // namespace Core