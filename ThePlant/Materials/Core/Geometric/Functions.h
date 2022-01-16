#pragma once

#include "Core/Geometric/GeometryDefs.h"
#include "Core/Geometric/2DFunctions.h"
#include "Core/Geometric/3DFunctions.h"
#include "Core/Math/Headers/MathDefs.h"

namespace Core {
namespace Geometric {
namespace INTERNAL_HELPER {
    // given two variants, will call the appropriate Distance(...) method for the two types held by them respectively
    struct Shape3DVisitor_Distance
    {
        template <typename SHAPE1, typename SHAPE2>
        float operator()(const SHAPE1& shape1, const SHAPE2& shape2)
        {
            return Distance(shape1, shape2);
        }
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

// if possible, this type of parrern for the variants
// one for each method for 3d shapes, one for each method for 2d shapes, and one for each method of 3d and 2d shape (where the 2d shape is used to make a plane)
float Distance(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2)
{
    return std::visit(INTERNAL_HELPER::Shape3DVisitor_Distance(), shape1, shape2);
}

template <typename SHAPE_1, typename SHAPE_2>
bool Engulfs(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
{
    return Engulfs(shape2, shape1);
}

// to handle checking if shapes intersect
template <typename SHAPE_1, typename SHAPE_2, typename PRECISION = Math::DEFAULT_PRECISION>
bool Intersect(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
{
    return Distance(shape1, shape2) <= PRECISION();
}

template <typename SHAPE_1, typename SHAPE_2>
bool Intersect(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2, const float& precision = Math::DEFAULT_PRECISION())
{
    return Distance(shape1, shape2) <= precision;
}
} // namespace Geometric
} // namespace Core