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

    AABB AABBFor(const Spot3D& point);
    ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Spot3D>& point);
    AABB AABBFor(const Line3D& line);
    ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Line3D>& line);
    AABB AABBFor(const Plane& plane);
    ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Plane>& plane);
    AABB AABBFor(const Sphere& sphere);
    ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Sphere>& sphere);
    AABB AABBFor(const Box& box);
    ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Box>& box);
} // namespace Geometric
} // namespace Core