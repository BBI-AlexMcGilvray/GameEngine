#pragma once

#include <utility>

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
    AABB EffectiveAABB(const ShapeOrientation<AABB>& aabb);

    Math::Float3 HalfDimensions(const AABB& aabb);
    Math::Float3 HalfDimensions(const ShapeOrientation<AABB>& aabb);

    Math::Float3 AABBMax(const AABB& aabb);
    Math::Float3 AABBMax(const ShapeOrientation<AABB>& aabb);
    Math::Float3 AABBMin(const AABB& aabb);
    Math::Float3 AABBMin(const ShapeOrientation<AABB>& aabb);
    std::pair<Math::Float3, Math::Float3> AABBMinMax(const AABB& aabb);
    std::pair<Math::Float3, Math::Float3> AABBMinMax(const ShapeOrientation<AABB>& aabb);

    Box RemoveAA(const AABB& aabb);
    ShapeOrientation<Box> RemoveAA(const ShapeOrientation<AABB>& aabb);

    AABB BoundingFor(const Spot3D& point);
    ShapeOrientation<AABB> BoundingFor(const ShapeOrientation<Spot3D>& point);
    AABB BoundingFor(const Line3D& line);
    ShapeOrientation<AABB> BoundingFor(const ShapeOrientation<Line3D>& line);
    AABB BoundingFor(const Plane& plane);
    ShapeOrientation<AABB> BoundingFor(const ShapeOrientation<Plane>& plane);
    AABB BoundingFor(const Sphere& sphere);
    ShapeOrientation<AABB> BoundingFor(const ShapeOrientation<Sphere>& sphere);
    AABB BoundingFor(const Box& box);
    ShapeOrientation<AABB> BoundingFor(const ShapeOrientation<Box>& box);
    AABB BoundingFor(const Shape3D& shape);
    ShapeOrientation<AABB> BoundingFor(const ShapeOrientation3D& shape);
} // namespace Geometric
} // namespace Core