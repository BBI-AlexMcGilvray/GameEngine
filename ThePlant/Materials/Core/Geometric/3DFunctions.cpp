#include "Core/Geometric/3DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Geometric/AABBFunctions.h"
#include "Core/Geometric/Functions.h"
#include "Core/Geometric/BoxFunctions.h"
#include "Core/Geometric/Line3DFunctions.h"
#include "Core/Geometric/PlaneFunctions.h"
#include "Core/Geometric/SphereFunctions.h"

#include "Core/Debugging/Profiling/Utils.h"

namespace Core
{
namespace Geometric
{
float DistanceSqr(const ShapeOrientation<Spot3D>& spot1, const ShapeOrientation<Spot3D>& spot2)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Spot3D, Spot3D)");

    return Math::DistanceSqr(spot1.orientation.position, spot2.orientation.position);
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot1, const ShapeOrientation<Spot3D>& spot2)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Spot3D, Sot3D)");

    return spot1.orientation.position == spot2.orientation.position;
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Line3D>& line)
{
    DEBUG_PROFILE_SCOPE("Engulfs(Spot3D, Line3D)");

    // do we care about case where spot == line.origin && line.length = 0?
    if (line.shape.infinite || line.shape.line != Core::Math::Float3(0.0f))
    {
        return false;
    }
    
    return spot.orientation.position == line.orientation.position;
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Plane>& plane)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Spot3D, Plane)");

    if (plane.shape.infinite)
    {
        return false;
    }
    
    // could be replaced with a 'IsPointOnPlane' check, though maybe this is cheaper
    if (spot.orientation.position != plane.orientation.position)
    {
        return false;
    }

    CORE_THROW("3DFunctions", "This is wrong, we would need to handle rotations");
    return Engulfs(ShapeOrientation<Spot2D>(spot.orientation, Spot2D()), ShapeOrientation2D(plane.orientation, plane.shape.shape));
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Sphere>& sphere)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Spot3D, Sphere)");

    if (sphere.shape.radius != 0.0f)
    {
        return false;
    }
    
    return spot.orientation.position == sphere.orientation.position;
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Box>& box)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Spot3D, Box)");

    if (box.shape.dimensions != Core::Math::Float3(0.0f))
    {
        return false;
    }

    return spot.orientation.position == box.orientation.position;
}

float DistanceSqr(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Line3D, Spot3D)");

    return Math::DistanceSqr(spot.orientation.position, ClosestPointOnLine(line, spot));
}

float DistanceSqr(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Line3D, Line3D)");

    const auto closestPointsOnLines = ClosestPointsBetweenLines(line1, line2);
    return Math::DistanceSqr(closestPointsOnLines.first, closestPointsOnLines.second);
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Line3D, Spot3D)");

    return PointIsOnLine(line, spot.orientation.position);
}

bool Engulfs(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Line3D, Line3D)");

    if (line1.shape.line != line2.shape.line)
    {
        return false;
    }

    if (PointIsOnLine(line1, line2.orientation.position))
    {
        return (line1.shape.infinite || (!line2.shape.infinite && PointIsOnLine(line1, LineEndpoint(line2))));
    }

    return false;
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Plane>& plane)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Line3D, Plane)");

    if (plane.shape.infinite || Math::Dot(EffectiveDirection(line), EffectiveNormal(plane)) != 0.0f)
    {
        return false;
    }

    CORE_THROW("3DFunctions", "This is wrong, we would need to handle rotations");
    return Engulfs(ShapeOrientation<Line2D>(line.orientation, Line2D()), ShapeOrientation2D(plane.orientation, plane.shape.shape));
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Sphere>& sphere)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Line3D, Sphere)");

    if (sphere.shape.radius != 0.0f)
    {
        return false;
    }

    return Engulfs(line, ShapeOrientation<Spot3D>(sphere.orientation, Spot3D()));
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Box>& box)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Line3D, Box)");

    if (box.shape.dimensions != Core::Math::Float3(0.0f))
    {
        return false;
    }

    return Engulfs(line, ShapeOrientation<Spot3D>(box.orientation, Spot3D()));
}

float DistanceSqr(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Plane, Spot3D)");

    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float DistanceSqr(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Plane, Line3D)");

    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float DistanceSqr(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Plane, Plane)");

    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Plane, Spot3D)");

    // do we care about case where spot is on plane?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Plane, Line3D)");

    // do we care about case where line is on plane?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Plane, Plane)");

    // do we care about case where plane2 is on plane1?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Sphere>& sphere)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Plane, Sphere)");

    // do we care about case where sphere.origin is on plane && plane.radius == 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Box>& box)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Plane, Box)");

    // do we care about case where box.origin is on plane && box.dimensions == 0?
    return false;
}

float DistanceSqr(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Sphere, Spot3D)");

    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return DistanceSqr(sphereCenter, spot) - Math::sqr(EffectiveRadius(sphere));
}

float DistanceSqr(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Sphere, Line3D)");

    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return DistanceSqr(line, sphereCenter) - Math::sqr(EffectiveRadius(sphere));
}

float DistanceSqr(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Sphere, Plane)");

    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return DistanceSqr(plane, sphereCenter) - Math::sqr(EffectiveRadius(sphere));
}

float DistanceSqr(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Sphere, Sphere)");

    ShapeOrientation<Spot3D> sphere2Center = { sphere2.orientation, Spot3D() };
    return DistanceSqr(sphere1, sphere2Center) - Math::sqr(EffectiveRadius(sphere1));
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Sphere, Spot3D)");

    return DistanceSqr(sphere, spot) <= Math::sqr(sphere.shape.radius);
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Sphere, Line3D)");

    if (line.shape.infinite)
    {
        return false;
    }

    return PointIsInSphere(sphere, line.orientation.position) && PointIsInSphere(sphere, LineEndpoint(line));
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Sphere, Plane)");

    if (plane.shape.infinite)
    {
        return false;
    }

    // return Engulfs(SphereAsCircleOnPlane(sphere, plane), plane);
    CORE_THROW("3DFunctions", "Unfinished Implementation");
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Sphere, Sphere)");

    // can't contain if the sphere wouldn't even fit
    if (sphere1.shape.radius < sphere2.shape.radius)
    {
        return false;
    }

    return DistanceSqr(sphere1, sphere2) <= Math::sqr(EffectiveRadius(sphere1) - EffectiveRadius(sphere2));
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Box>& box)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Sphere, Box)");

    const auto boxCorners = BoxCorners(box);

    for (const auto& corner : boxCorners)
    {
        if (!PointIsInSphere(sphere, corner))
        {
            return false;
        }
    }

    return true;
}

float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Box, Spot3D)");

    // DEBUG_PROFILE_PUSH("PointInBox");
    if (PointInBox(box, spot))
    {
        // DEBUG_PROFILE_POP("PointInBox");
        return 0.0f;
    }
    // DEBUG_PROFILE_POP("PointInBox");

    {
        // DEBUG_PROFILE_SCOPE("Other");
        const auto closestPoint = ClosestPointToPoint(box, spot);
        return DistanceSqr(closestPoint, spot.orientation.position);
    }
}

float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Box, Line3D)");

    return DistanceSqr(line, ShapeOrientation<Spot3D>(Orientation(ClosestPointToLine(box, line)), Spot3D()));
}

float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Box, Plane)");

    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;

    // closest point on plane to box
    // distance from box to that point
}

float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Box, Sphere)");

    return DistanceSqr(box, ShapeOrientation<Spot3D>(sphere.orientation, Spot3D())) - Math::sqr(EffectiveRadius(sphere));
}

float DistanceSqr(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2)
{
    // DEBUG_PROFILE_SCOPE("DistanceSqr(Box, Box)");

    auto boxEdges = BoxEdges(box2);

    bool first = true;
    float minimumDistance;
    // closest point from box1 to a box2 corner
    for (const auto& edge : boxEdges)
    {
        const auto distance = DistanceSqr(box1, edge);

        if (!first)
        {
            minimumDistance = std::min(distance, minimumDistance);
        }
        else
        {
            minimumDistance = distance;
            first = false;
        }

        if (minimumDistance <= 0.0f)
        {
            return 0.0f;
        }
    }

    boxEdges = BoxEdges(box1);
    // need to check the opposite too, as they may be closer
    for (const auto& edge : boxEdges)
    {
        const auto distance = DistanceSqr(box2, edge);

        minimumDistance = std::min(distance, minimumDistance);

        if (minimumDistance <= 0.0f)
        {
            return 0.0f;
        }
    }

    return minimumDistance;
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Box, Spot3D)");

    return PointInBox(box, spot);
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Box, Line3D)");

    if (line.shape.infinite)
    {
        return false;
    }

    return PointInBox(box, line.orientation.position) && PointInBox(box, LineEndpoint(line));
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Box, Plane)");

    if (plane.shape.infinite)
    {
        return false;
    }

    // get defining points on shape on plane, check if all points are in box
    CORE_THROW("3DFunctions", "Unfinished Implementation");
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Box, Sphere)");

    const auto sphereExtremes = SphereAxisExtremes(sphere, box.orientation.rotation.Inverse());

    for (const auto& extreme : sphereExtremes)
    {
        if (!PointInBox(box, extreme))
        {
            return false;
        }
    }

    return true;
}

bool Engulfs(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2)
{
    // DEBUG_PROFILE_SCOPE("Engulfs(Box, Box)");

    const auto boxCorners = BoxCorners(box2);
    
    for (const auto& corner : boxCorners)
    {
        if (!PointInBox(box1, corner))
        {
            return false;
        }
    }

    return true;
}

bool Intersect(const ShapeOrientation<AABB>& aabb1, const ShapeOrientation<AABB>& aabb2)
{
    std::pair<Math::Float3, Math::Float3> aabb1Extremes = AABBMinMax(aabb1);
    std::pair<Math::Float3, Math::Float3> aabb2Extremes = AABBMinMax(aabb2);

    return ((aabb1.shape.infinite.X || aabb2.shape.infinite.X) || (aabb1Extremes.first.X <= aabb2Extremes.second.X && aabb1Extremes.second.X >= aabb2Extremes.first.X)) &&
            ((aabb1.shape.infinite.Y || aabb2.shape.infinite.Y) || (aabb1Extremes.first.Y <= aabb2Extremes.second.Y && aabb1Extremes.second.Y >= aabb2Extremes.first.Y)) &&
            ((aabb1.shape.infinite.Z || aabb2.shape.infinite.Z) || (aabb1Extremes.first.Z <= aabb2Extremes.second.Z && aabb1Extremes.second.Z >= aabb2Extremes.first.Z));
}

bool Engulfs(const ShapeOrientation<AABB>& aabb1, const ShapeOrientation<AABB>& aabb2)
{
    const auto& infinites1 = aabb1.shape.infinite;
    const auto& infinites2 = aabb2.shape.infinite;
    // if aabb2 is infinite where aabb1 is not, no way aabb1 can engulf it
    if ((infinites2.X && !infinites1.X) || (infinites2.Y && !infinites1.Y) || (infinites2.Z && !infinites1.Z))
    {
        return false;
    }

    std::pair<Math::Float3, Math::Float3> aabb1Extremes = AABBMinMax(aabb1);
    std::pair<Math::Float3, Math::Float3> aabb2Extremes = AABBMinMax(aabb2);

    return (aabb2Extremes.first.X >= aabb1Extremes.first.X && aabb2Extremes.second.X <= aabb1Extremes.second.X) &&
            (aabb2Extremes.first.Y >= aabb1Extremes.first.Y && aabb2Extremes.second.Y <= aabb1Extremes.second.Y) && 
            (aabb2Extremes.first.Z >= aabb1Extremes.first.Z && aabb2Extremes.second.Z <= aabb1Extremes.second.Z);
}
} // namespace Geometric
} // namespace Core