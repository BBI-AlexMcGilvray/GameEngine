#pragma once

#include <variant>

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Geometric/AABB.h"
#include "Core/Geometric/AABR.h"
#include "Core/Geometric/Box.h"
#include "Core/Geometric/Circle.h"
#include "Core/Geometric/Line2D.h"
#include "Core/Geometric/Line3D.h"
#include "Core/Geometric/Plane.h"
#include "Core/Geometric/Spot.h"
#include "Core/Geometric/Rectangle.h"
#include "Core/Geometric/Sphere.h"
#include "Core/Geometric/Orientation.h"

namespace Core {
namespace Geometric {    
    using Point2D = Math::Float2;
    using Point3D = Math::Float3;
    // defined in Plane.h, maybe we want a '2DGeometryDefs.h' file to hold it and be referenced by both?
    // using Shape2D = std::variant<Circle, Line2D, Spot2D, Rectangle>; // does not contain AABR, AABRs currently used as optimization in oct trees
    using Shape3D = std::variant<Box, Line3D, Plane, Spot3D, Sphere>; // does not contain AABB, AABBs currently used as optimization in oct trees

    template <typename SHAPE2D>
    Plane Shape2DAsPlane(const SHAPE2D& shape_2d)
    {
        return Plane(Math::Float3(0.0f, 0.0f, 1.0f), shape_2d);
    }

    struct Intersection
    {
        bool intersect;
        Point3D point;

        Intersection()
        : Intersection(false, Point3D(0.0f, 0.0f, 0.0f))
        {}

        Intersection(const bool& intersect, const Point3D& point)
        : intersect(intersect)
        , point(point)
        {}

        Intersection(const Intersection&) = default;
        Intersection(Intersection&&) = default;
        Intersection& operator=(const Intersection&) = default;
        Intersection& operator=(Intersection&&) = default;
        ~Intersection() = default;

        bool operator==(const Intersection& other)
        {
            return intersect == other.intersect && point == other.point;
        }
        bool operator!=(const Intersection& other) { return !(*this == other); }
    };

    template <typename SHAPE>
    struct ShapeOrientation
    {
        Orientation orientation;
        SHAPE shape;

        ShapeOrientation() = default;

        ShapeOrientation(const Orientation& orientation, const SHAPE& shape)
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

            return *this;
        }
        template <typename OTHER_SHAPE>
        ShapeOrientation& operator=(ShapeOrientation<OTHER_SHAPE>&& other)
        {
            orientation = std::move(other.orientation);
            shape = std::move(other.shape);

            return *this;
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

    template <typename SHAPE, typename BOUNDING>
    struct BoundedShapeOrientation
    {
        ShapeOrientation<SHAPE> shapeOrientation;
        ShapeOrientation<BOUNDING> boundingBox;

        BoundedShapeOrientation() = default;
        BoundedShapeOrientation(const Orientation& orientation, const SHAPE& shape)
        : BoundedShapeOrientation(shapeOrientation(orientation, shape))
        {}
        BoundedShapeOrientation(const ShapeOrientation<SHAPE>& shapeOrientation)
        : shapeOrientation(shapeOrientation)
        , boundingBox(BoundingFor(shapeOrientation))
        {}

        BoundedShapeOrientation(const BoundedShapeOrientation&) = default;
        BoundedShapeOrientation(BoundedShapeOrientation&&) = default;
        BoundedShapeOrientation& operator=(const BoundedShapeOrientation&) = default;
        BoundedShapeOrientation& operator=(BoundedShapeOrientation&&) = default;

        // to allow converting between applicable shapes
        template <typename OTHER_SHAPE>
        BoundedShapeOrientation(const BoundedShapeOrientation<OTHER_SHAPE, BOUNDING>& other)
        {
            shapeOrientation = other.shapeOrientation;
            boundingBox = other.boundingBox;
        }
        template <typename OTHER_SHAPE>
        BoundedShapeOrientation(BoundedShapeOrientation<OTHER_SHAPE, BOUNDING>&& other)
        {
            shapeOrientation = std::move(other.shapeOrientation);
            boundingBox = std::move(other.boundingBox);
        }
        template <typename OTHER_SHAPE>
        BoundedShapeOrientation& operator=(const BoundedShapeOrientation<OTHER_SHAPE, BOUNDING>& other)
        {
            shapeOrientation = other.shapeOrientation;
            boundingBox = other.boundingBox;

            return *this;
        }
        template <typename OTHER_SHAPE>
        BoundedShapeOrientation& operator=(BoundedShapeOrientation<OTHER_SHAPE, BOUNDING>&&)
        {
            shapeOrientation = std::move(other.shapeOrientation);
            boundingBox = std::move(other.boundingBox);

            return *this;
        }

        bool operator==(const BoundedShapeOrientation& other) const
        {
            return shapeOrientation == other.shapeOrientation && boundingBox == other.boundingBox;
        }
        bool operator!=(const BoundedShapeOrientation& other) const
        {
            return !(*this == other);
        }
    };

    template <typename SHAPE>
    using AABBShapeOrientation = BoundedShapeOrientation<SHAPE, AABB>;
    using AABBShapeOrientation3D = AABBShapeOrientation<Shape3D>;
    template <typename SHAPE>
    using AABRShapeOrientation = BoundedShapeOrientation<SHAPE, AABR>;
    using AABRShapeOrientation2D = AABRShapeOrientation<Shape2D>;
    
#if DEBUG
#define VERIFY_2D(SHAPE_ORIENTATION) VERIFY(SHAPE_ORIENTATION.orientation.position == 0.0f); // we should also verify that the rotation maintains the x/y plane
#else
#define VERIFY_2D(SHAPE_ORIENTATION)
#endif
} // namespace Geometric
} // namespace Core