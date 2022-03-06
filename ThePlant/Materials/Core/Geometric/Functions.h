#pragma once

#include <variant>

#include "Core/Headers/type_traits.h"

#include "Core/Geometric/GeometryDefs.h"
#include "Core/Geometric/2DFunctions.h"
#include "Core/Geometric/3DFunctions.h"
#include "Core/Math/Headers/MathDefs.h"

namespace Core {
namespace Geometric {
// to handle calling 'Distance' with swapped arguments
template <typename SHAPE_1, typename SHAPE_2> // specific d -> specific d
auto ClosestPoints(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
-> typename std::enable_if<(is_in_variant<SHAPE_1, Shape3D>::value == is_in_variant<SHAPE_2, Shape3D>::value)
                && (is_in_variant<SHAPE_1, Shape2D>::value == is_in_variant<SHAPE_2, Shape2D>::value), std::pair<Point3D, Point3D>>::type // only if SHAPE_1 and SHAPE_2 belong to the same variants
{
    return ClosestPoints(shape2, shape1);
}
template <typename SHAPE3D, typename SHAPE2D> // specific 3d -> specific 2d
auto ClosestPoints(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, std::pair<Point3D, Point3D>>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return ClosestPoints(shape_3d, ShapeOrientation<Plane>(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE2D, typename SHAPE3D> // specific 2d -> specific 3d
auto ClosestPoints(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, std::pair<Point3D, Point3D>>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return ClosestPoints(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE3D> // specific 3d -> general 3d
auto ClosestPoints(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation3D& shape3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(ShapeOrientation3D(shape_3d), shape3d);
}
template <typename SHAPE3D> // general 3d -> specific 3d
auto ClosestPoints(const ShapeOrientation3D& shape3d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(ShapeOrientation3D(shape_3d), shape3d);
}
template <typename SHAPE2D> // general 3d -> specific 2d
auto ClosestPoints(const ShapeOrientation3D& shape3D, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(shape3D, ShapeOrientation2D(shape_2d));
}
template <typename SHAPE2D> // specific 2d -> general 3d
auto ClosestPoints(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation3D& shape3D)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(shape3D, ShapeOrientation2D(shape_2d));
}
template <typename SHAPE2D> // specific 2d -> general 2d
auto ClosestPoints(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation2D& shape2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(ShapeOrientation2D(shape_2d), shape2d);
}
template <typename SHAPE2D> // general 2d -> specific 2d
auto ClosestPoints(const ShapeOrientation2D& shape2d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(ShapeOrientation2D(shape_2d), shape2d);
}
template <typename SHAPE3D> // general 2d -> specific 3d
auto ClosestPoints(const ShapeOrientation2D& shape2D, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(shape2D, ShapeOrientation3D(shape_3d));
}
template <typename SHAPE3D> // specific 3d -> general 2d
auto ClosestPoints(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation2D& shape2D)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, std::pair<Point3D, Point3D>>::type
{
    return ClosestPoints(shape2D, ShapeOrientation3D(shape_3d));
}
// general 3d -> general 2d
std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d);
// general 2d -> general 3d
std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d);
// general 3d -> general 3d
std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2);
// general 2d -> general 2d
std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2);

template <typename SHAPE1, typename SHAPE2>
float DistanceSqr(const SHAPE1& shape1, const SHAPE2& shape2)
{
    const auto closestPoints = ClosestPoints(shape1, shape2);

    return Math::DistanceSqr(closestPoints.first, closestPoints.second);
}

// order matters for engulf calls, this should not exist
// template <typename SHAPE_1, typename SHAPE_2> // specific d -> specific d
// auto Engulfs(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2)
// -> typename std::enable_if<(is_in_variant<SHAPE_1, Shape3D>::value == is_in_variant<SHAPE_2, Shape3D>::value)
//                 && (is_in_variant<SHAPE_1, Shape2D>::value == is_in_variant<SHAPE_2, Shape2D>::value), bool>::type // only if SHAPE_1 and SHAPE_2 belong to the same variants

// {
//     return Engulfs(shape2, shape1);
// }
template <typename SHAPE3D, typename SHAPE2D> // specific 3d -> specific 2d
auto Engulfs(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, bool>::type // only if SHAPE3D and SHAPE2D belong to different variants

{
    return Engulfs(shape_3d, ShapeOrientation<Plane>(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}
template <typename SHAPE2D, typename SHAPE3D> // specific 2d -> specific 3d
auto Engulfs(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, bool>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    // 2d can't contain 3d
    return false;
}
template <typename SHAPE3D> // specific 3d -> general 3d
auto Engulfs(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation3D& shape3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Engulfs(ShapeOrientation3D(shape_3d), shape3d);
}
template <typename SHAPE3D> // general 3d -> specific 3d
auto Engulfs(const ShapeOrientation3D& shape3d, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Engulfs(ShapeOrientation3D(shape_3d), shape3d);
}
template <typename SHAPE2D> // general 3d -> specific 2d
auto Engulfs(const ShapeOrientation3D& shape3D, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Engulfs(shape3D, ShapeOrientation2D(shape_2d));
}
template <typename SHAPE2D> // specific 2d -> general 3d
auto Engulfs(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation3D& shape3D)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Engulfs(shape3D, ShapeOrientation2D(shape_2d));
}
template <typename SHAPE2D> // specific 2d -> general 2d
auto Engulfs(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation2D& shape2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Engulfs(ShapeOrientation2D(shape_2d), shape2d);
}
template <typename SHAPE2D> // general 2d -> specific 2d
auto Engulfs(const ShapeOrientation2D& shape2d, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, bool>::type
{
    return Engulfs(ShapeOrientation2D(shape_2d), shape2d);
}
template <typename SHAPE3D> // general 2d -> specific 3d
auto Engulfs(const ShapeOrientation2D& shape2D, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Engulfs(shape2D, ShapeOrientation3D(shape_3d));
}
template <typename SHAPE3D> // specific 3d -> general 2d
auto Engulfs(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation2D& shape2D)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, bool>::type
{
    return Engulfs(shape2D, ShapeOrientation3D(shape_3d));
}
// general 3d -> general 2d
bool Engulfs(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d);
// general 2d -> general 3d
bool Engulfs(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d);
// general 3d -> general 3d
bool Engulfs(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2);
// general 2d -> general 2d
bool Engulfs(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2);

// to handle checking if shapes intersect
template <typename SHAPE_1, typename SHAPE_2> // specific d -> specific d
auto Intersect(const ShapeOrientation<SHAPE_1>& shape1, const ShapeOrientation<SHAPE_2>& shape2, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<(is_in_variant<SHAPE_1, Shape3D>::value == is_in_variant<SHAPE_2, Shape3D>::value)
                && (is_in_variant<SHAPE_1, Shape2D>::value == is_in_variant<SHAPE_2, Shape2D>::value), Intersection>::type // only if SHAPE_1 and SHAPE_2 belong to the same variants
{
    const std::pair<Point3D, Point3D> closestPoints = ClosestPoints(shape1, shape2);
    const Point3D middleOfPoints = (closestPoints.first + closestPoints.second) * 0.5f;

    const bool intersect = DistanceSqr(closestPoints.first, closestPoints.second) <= precision;

    return { intersect, intersect ? middleOfPoints : Point3D() };
}
template <typename SHAPE3D, typename SHAPE2D> // specific 3d -> specific 2d
auto Intersect(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation<SHAPE2D>& shape_2d, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, Intersection>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return Intersect(shape_3d, ShapeOrientation<Plane>(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)), precision);
}
template <typename SHAPE2D, typename SHAPE3D> // specific 2d -> specific 3d
auto Intersect(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation<SHAPE3D>& shape_3d, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value && is_in_variant<SHAPE2D, Shape2D>::value, Intersection>::type // only if SHAPE3D and SHAPE2D belong to different variants
{
    return Intersect(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)), precision);
}
template <typename SHAPE3D> // specific 3d -> general 3d
auto Intersect(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation3D& shape3d, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, Intersection>::type
{
    return Intersect(ShapeOrientation3D(shape_3d), shape3d, precision);
}
template <typename SHAPE3D> // general 3d -> specific 3d
auto Intersect(const ShapeOrientation3D& shape3d, const ShapeOrientation<SHAPE3D>& shape_3d, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, Intersection>::type
{
    return Intersect(ShapeOrientation3D(shape_3d), shape3d, precision);
}
template <typename SHAPE2D> // general 3d -> specific 2d
auto Intersect(const ShapeOrientation3D& shape3D, const ShapeOrientation<SHAPE2D>& shape_2d)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, Intersection>::type
{
    return Intersect(shape3D, ShapeOrientation2D(shape_2d));
}
template <typename SHAPE2D> // specific 2d -> general 3d
auto Intersect(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation3D& shape3D)
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, Intersection>::type
{
    return Intersect(shape3D, ShapeOrientation2D(shape_2d));
}
template <typename SHAPE2D> // specific 2d -> general 2d
auto Intersect(const ShapeOrientation<SHAPE2D>& shape_2d, const ShapeOrientation2D& shape2d, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, Intersection>::type
{
    return Intersect(ShapeOrientation2D(shape_2d), shape2d, precision);
}
template <typename SHAPE2D> // general 2d -> specific 2d
auto Intersect(const ShapeOrientation2D& shape2d, const ShapeOrientation<SHAPE2D>& shape_2d, const float& precision = Math::DEFAULT_PRECISION())
-> typename std::enable_if<is_in_variant<SHAPE2D, Shape2D>::value, Intersection>::type
{
    return Intersect(ShapeOrientation2D(shape_2d), shape2d, precision);
}
template <typename SHAPE3D> // general 2d -> specific 3d
auto Intersect(const ShapeOrientation2D& shape2D, const ShapeOrientation<SHAPE3D>& shape_3d)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, Intersection>::type
{
    return Intersect(shape2D, ShapeOrientation3D(shape_3d));
}
template <typename SHAPE3D> // specific 3d -> general 2d
auto Intersect(const ShapeOrientation<SHAPE3D>& shape_3d, const ShapeOrientation2D& shape2D)
-> typename std::enable_if<is_in_variant<SHAPE3D, Shape3D>::value, Intersection>::type
{
    return Intersect(shape2D, ShapeOrientation3D(shape_3d));
}
// general 3d -> general 2d
Intersection Intersect(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d, const float& precision = Math::DEFAULT_PRECISION());
// general 2d -> general 3d
Intersection Intersect(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d, const float& precision = Math::DEFAULT_PRECISION());
// general 3d -> general 3d
Intersection Intersect(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2, const float& precision = Math::DEFAULT_PRECISION());
// general 2d -> general 2d
Intersection Intersect(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2, const float& precision = Math::DEFAULT_PRECISION());

// we may want to NOT use bounding boxes when the shapes don't warrant them (points, spheres) as that would be more efficient
Intersection Intersect(const AABBShapeOrientation3D& boundedShape3D1, const AABBShapeOrientation3D& boundedShape3D2);
bool Engulfs(const AABBShapeOrientation3D& boundedShape3D1, const AABBShapeOrientation3D& boundedShape3D2);
Intersection Intersect(const AABRShapeOrientation2D& boundedShape2D1, const AABRShapeOrientation2D& boundedShape2D2);
bool Engulfs(const AABRShapeOrientation2D& boundedShape2D1, const AABRShapeOrientation2D& boundedShape2D2);
// deal with 2d->3d and 3d->2d and all the other combinations later
} // namespace Geometric
} // namespace Core