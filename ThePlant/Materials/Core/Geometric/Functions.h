#pragma once

#include <variant>

#include "Core/Headers/type_traits.h"

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

// NOTE: We need to also handle SHAPE <-> ShapeXD interactions (variant to non-variant)
*/
// to handle calling 'Distance' with swapped arguments
template <typename SHAPE_1, typename SHAPE_2>
auto Distance(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
-> typename std::enable_if<(is_in_variant<SHAPE_1, Shape3D>::value == is_in_variant<SHAPE_2, Shape3D>::value)
                && (is_in_variant<SHAPE_1, Shape2D>::value == is_in_variant<SHAPE_2, Shape2D>::value), float>::type // only if SHAPE_1 and SHAPE_2 belong to the same variants
{
    return Distance(shape2, shape1);
}
template <typename SHAPE3D, typename SHAPE2D>
auto Distance(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, float>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return Distance(shape_3d, ShapeOrientation<Plane>(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE2D, typename SHAPE3D>
auto Distance(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, float>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return Distance(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE3D>
auto Distance(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation3D& shape3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, float>::type
{
    return Distance(ShapeOrientation3D(shape3d), shape3d);
}
template <typename SHAPE3D>
auto Distance(const ShapeOrientation3D& shape3d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, float>::type
{
    return Distance(ShapeOrientation3D(shape3d), shape3d);
}
template <typename SHAPE2D>
auto Distance(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation2D& shape2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, float>::type
{
    return Distance(ShapeOrientation2D(shape2d), shape2d);
}
template <typename SHAPE2D>
auto Distance(const ShapeOrientation2D& shape2d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, float>::type
{
    return Distance(ShapeOrientation2D(shape2d), shape2d);
}
float Distance(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d)
{
    return Distance(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
float Distance(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d)
{
    return Distance(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
float Distance(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2);
float Distance(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2);

template <typename SHAPE_1, typename SHAPE_2>
auto Engulfs(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
-> typename std::enable_if<(is_in_variant<SHAPE_1, Shape3D>::value == is_in_variant<SHAPE_2, Shape3D>::value)
                && (is_in_variant<SHAPE_1, Shape2D>::value == is_in_variant<SHAPE_2, Shape2D>::value), bool>::type // only if SHAPE_1 and SHAPE_2 belong to the same variants

{
    return Engulfs(shape2, shape1);
}
template <typename SHAPE3D, typename SHAPE2D>
auto Engulfs(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, bool>::type // only if SHAPE3D and SHAPE2D belong to different variants

{
    return Engulfs(shape_3d, ShapeOrientation<Plane>(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE2D, typename SHAPE3D>
auto Engulfs(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, bool>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return Engulfs(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE3D>
auto Engulfs(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation3D& shape3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Engulfs(ShapeOrientation3D(shape3d), shape3d);
}
template <typename SHAPE3D>
auto Engulfs(const ShapeOrientation3D& shape3d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Engulfs(ShapeOrientation3D(shape3d), shape3d);
}
template <typename SHAPE2D>
auto Engulfs(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation2D& shape2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Engulfs(ShapeOrientation2D(shape2d), shape2d);
}
template <typename SHAPE2D>
auto Engulfs(const ShapeOrientation2D& shape2d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Engulfs(ShapeOrientation2D(shape2d), shape2d);
}
bool Engulfs(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d)
{
    return Engulfs(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
bool Engulfs(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d)
{
    return Engulfs(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
bool Engulfs(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2);
bool Engulfs(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2);

// to handle checking if shapes intersect
template <typename SHAPE_1, typename SHAPE_2>
auto Intersect(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<(is_in_variant<SHAPE_1, Shape3D>::value == is_in_variant<SHAPE_2, Shape3D>::value)
                && (is_in_variant<SHAPE_1, Shape2D>::value == is_in_variant<SHAPE_2, Shape2D>::value), bool>::type // only if SHAPE_1 and SHAPE_2 belong to the same variants
{
    return Distance(shape1, shape2) <= precision;
}
template <typename SHAPE3D, typename SHAPE2D>
auto Intersect(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, bool>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return Intersect(shape_3d, ShapeOrientation<Plane>(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE2D, typename SHAPE3D>
auto Intersect(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, bool>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return Intersect(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE3D>
auto Intersect(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation3D& shape3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Intersect(ShapeOrientation3D(shape3d), shape3d);
}
template <typename SHAPE3D>
auto Intersect(const ShapeOrientation3D& shape3d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Intersect(ShapeOrientation3D(shape3d), shape3d);
}
template <typename SHAPE2D>
auto Intersect(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation2D& shape2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Intersect(ShapeOrientation2D(shape2d), shape2d);
}
template <typename SHAPE2D>
auto Intersect(const ShapeOrientation2D& shape2d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Intersect(ShapeOrientation2D(shape2d), shape2d);
}
bool Intersect(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d)
{
    return Intersect(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
bool Intersect(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d)
{
    return Intersect(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
bool Intersect(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2);
bool Intersect(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2);
} // namespace Geometric
} // namespace Core