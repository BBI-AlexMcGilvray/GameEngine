#pragma once

#include <variant>

#include "Core/Geometric/GeometryDefs.h"
#include "Core/Geometric/2DFunctions.h"
#include "Core/Geometric/3DFunctions.h"
#include "Core/Math/Headers/MathDefs.h"

namespace Core {
namespace Geometric {
namespace INTERNAL_HELPER {
    // given two variants, will call the appropriate Distance(...) method for the two types held by them respectively
    struct ShapeVisitor_Distance
    {
        ShapeVisitor_Distance(const Transform& transform1, const Transform transform2)
        : transform1(transform1)
        , transform2(transform2)
        {}

        template <typename SHAPE1, typename SHAPE2>
        float operator()(const SHAPE1& shape1, const SHAPE2& shape2) const
        {
            return Distance({ transform1, shape1 }, { transform2, shape2 });
        }

    private:
        const Transform& transform1;
        const Transform& transform2;
    };

    // given two variants, will call the appropriate Engulfs(...) method for the two types held by them respectively
    struct ShapeVisitor_Engulfs
    {
        ShapeVisitor_Engulfs(const Transform& transform1, const Transform transform2)
        : transform1(transform1)
        , transform2(transform2)
        {}

        template <typename SHAPE1, typename SHAPE2>
        float operator()(const SHAPE1& shape1, const SHAPE2& shape2) const
        {
            return Engulfs({ transform1, shape1 }, { transform2, shape2 });
        }

    private:
        const Transform& transform1;
        const Transform& transform2;
    };

    // given two variants, will call the appropriate Intersect(...) method for the two types held by them respectively
    struct ShapeVisitor_Intersect
    {
        ShapeVisitor_Intersect(const Transform& transform1, const Transform transform2)
        : transform1(transform1)
        , transform2(transform2)
        {}

        template <typename SHAPE1, typename SHAPE2>
        float operator()(const SHAPE1& shape1, const SHAPE2& shape2) const
        {
            return Intersect({ transform1, shape1 }, { transform2, shape2 });
        }

    private:
        const Transform& transform1;
        const Transform& transform2;
    };
} // namespace INTERNAL_HELPER

/*
// NOTE: We may want a
Math::Float2 IntersectionPoint(...)
method, but that can wait - likely much more complex
*/
// to handle calling 'Distance' with swapped arguments
template <typename SHAPE_1, typename SHAPE_2>
float Distance(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
{
    return Distance(shape2, shape1);
}

float Distance(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2)
{
    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Distance(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

float Distance(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2)
{
    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Distance(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

template <typename SHAPE_1, typename SHAPE_2>
bool Engulfs(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
{
    return Engulfs(shape2, shape1);
}

float Engulfs(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2)
{
    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Engulfs(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

float Engulfs(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2)
{
    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Engulfs(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

// to handle checking if shapes intersect
template <typename SHAPE_1, typename SHAPE_2>
bool Intersect(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2, const float& precision = Math::DEFAULT_PRECISION())
{
    return Intersect(shape1, shape2) <= precision;
}

float Intersect(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2)
{
    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Intersect(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

float Intersect(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2)
{
    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Intersect(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}
} // namespace Geometric
} // namespace Core