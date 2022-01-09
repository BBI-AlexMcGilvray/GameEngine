#pragma once

#include "Core/Geometric/GeometryDefs.h"
#include "Core/Geometric/2DFunctions.h"
#include "Core/Geometric/3DFunctions.h"
#include "Core/Math/Headers/MathDefs.h"

namespace Core {
namespace Geometric {
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