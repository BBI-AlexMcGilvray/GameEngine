#include "Core/Geometric/AABBFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Geometric/AABRFunctions.h"
#include "Core/Geometric/BoxFunctions.h"
#include "Core/Geometric/Line3DFunctions.h"
#include "Core/Geometric/SphereFunctions.h"

namespace Core {
namespace Geometric {

AABB EffectiveAABB(const ShapeOrientation<AABB>& aabb)
{
    return AABB(aabb.shape.dimensions * aabb.orientation.scale);
}

Math::Float3 HalfDimensions(const AABB& aabb)
{
    return aabb.dimensions * 0.5f;
}

Math::Float3 HalfDimensions(const ShapeOrientation<AABB>& aabb)
{
    return HalfDimensions(EffectiveAABB(aabb));
}

Math::Float3 AABBMax(const AABB& aabb)
{
    return HalfDimensions(aabb);
}

Math::Float3 AABBMax(const ShapeOrientation<AABB>& aabb)
{
    return aabb.orientation.position + HalfDimensions(aabb);
}

Math::Float3 AABBMin(const AABB& aabb)
{
    return HalfDimensions(aabb) * -1.0f;
}

Math::Float3 AABBMin(const ShapeOrientation<AABB>& aabb)
{
    return aabb.orientation.position - HalfDimensions(aabb);
}

std::pair<Math::Float3, Math::Float3> AABBMinMax(const AABB& aabb)
{
    return { AABBMin(aabb), AABBMax(aabb) };
}

std::pair<Math::Float3, Math::Float3> AABBMinMax(const ShapeOrientation<AABB>& aabb)
{
    AABB effectiveAABB = EffectiveAABB(aabb);
    return { aabb.orientation.position + AABBMin(effectiveAABB), aabb.orientation.position + AABBMax(effectiveAABB) };
}

AABB AABBFor(const Spot3D& point)
{
    return AABB(Math::Float3(0.0f));
}

ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Spot3D>& point)
{
    return ShapeOrientation<AABB>(point.orientation, AABBFor(point.shape));
}

AABB AABBFor(const Line3D& line)
{
    if (line.infinite)
    {
        return AABB(line.line, Math::Vector3<bool>(line.line.X != 0.0f, line.line.Y != 0.0f, line.line.Z != 0.0f));
    }

    return AABB(LineEndpoint(line)); // line is centered on 0 so this gives the full line dimensions, the line is properly centered by the 0.5 adjustment below
}

ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Line3D>& line)
{
    const auto effectiveLine = EffectiveDirection(line);
    Orientation aabbOrientation = line.orientation;
    aabbOrientation.position -= effectiveLine * 0.5f; // need to center the AABB

    return ShapeOrientation<AABB>(aabbOrientation, AABBFor(Line3D(effectiveLine, line.shape.infinite)));
}

AABB AABBFor(const Plane& plane)
{
    if (plane.infinite)
    {
        Math::Vector3<bool> infiniteDirections;
        // a direction is only NOT infinite if it is the only non-0 element
        infiniteDirections.X = plane.normal.Y != 0.0f && plane.normal.Z != 0.0f;
        infiniteDirections.Y = plane.normal.X != 0.0f && plane.normal.Z != 0.0f;
        infiniteDirections.Z = plane.normal.X != 0.0f && plane.normal.Y != 0.0f;
        
        return AABB(infiniteDirections);
    }

    return AABB(AABRFor(plane.shape));
}

ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Plane>& plane)
{
    // return ShapeOrientation<AABB>(plane.orientation, AABBFor(EffectivePlane(plane)));
    CORE_THROW("AABBFunctions", "Unfinished Implementation");
}

AABB AABBFor(const Sphere& sphere)
{
    return AABB(Core::Math::Float3(sphere.radius * 2.0f));
}

ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Sphere>& sphere)
{
    return ShapeOrientation<AABB>(sphere.orientation, AABBFor(Sphere(EffectiveRadius(sphere))));
}

AABB AABBFor(const Box& box)
{
    return AABB(box.dimensions);
}

ShapeOrientation<AABB> AABBFor(const ShapeOrientation<Box>& box)
{
    const auto boxCorners = BoxCorners(box);
    Math::Float3 fullMin = boxCorners[0];
    Math::Float3 fullMax = boxCorners[0];
    for (size_t i = 1; i < boxCorners.size(); ++i)
    {
        fullMin = Math::Min(fullMin, boxCorners[i]);
        fullMax = Math::Max(fullMax, boxCorners[i]);
    }
    Math::Float3 fullDimensions = fullMax - fullMin;

    return ShapeOrientation<AABB>(box.orientation, AABBFor(Box(fullDimensions)));
}

} // namespace Geometric
} // namespace Core