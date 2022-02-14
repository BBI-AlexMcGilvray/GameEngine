#include "Core/Geometric/3DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Geometric/Functions.h"
#include "Core/Geometric/BoxFunctions.h"
#include "Core/Geometric/Line3DFunctions.h"
#include "Core/Geometric/PlaneFunctions.h"
#include "Core/Geometric/SphereFunctions.h"

namespace Core
{
namespace Geometric
{
float Distance(const ShapeOrientation<Spot3D>& spot1, const ShapeOrientation<Spot3D>& spot2)
{
    return Math::Distance(spot1.orientation.GetPosition(), spot2.orientation.GetPosition());
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot1, const ShapeOrientation<Spot3D>& spot2)
{
    return spot1.orientation.GetPosition() == spot2.orientation.GetPosition();
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Line3D>& line)
{
    // do we care about case where spot == line.origin && line.length = 0?
    if (line.shape.infinite || line.shape.length != 0.0f)
    {
        return false;
    }
    
    return spot.orientation.GetPosition() == line.orientation.GetPosition();
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Plane>& plane)
{
    if (plane.shape.infinite)
    {
        return false;
    }
    
    // could be replaced with a 'IsPointOnPlane' check, though maybe this is cheaper
    if (spot.orientation.GetPosition() != plane.orientation.GetPosition())
    {
        return false;
    }

    CORE_THROW("3DFunctions", "This is wrong, we would need to handle rotations");
    return Engulfs(ShapeOrientation<Spot2D>(spot.orientation, Spot2D()), ShapeOrientation2D(plane.orientation, plane.shape.shape));
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Sphere>& sphere)
{
    if (sphere.shape.radius != 0.0f)
    {
        return false;
    }
    
    return spot.orientation.GetPosition() == sphere.orientation.GetPosition();
}

bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Box>& box)
{
    if (box.shape.dimensions != Core::Math::Float3(0.0f))
    {
        return false;
    }

    return spot.orientation.GetPosition() == box.orientation.GetPosition();
}

float Distance(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot)
{
    return Math::Distance(spot.orientation.GetPosition(), ClosestPointOnLine(line, spot));
}

float Distance(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2)
{
    const auto closestPointsOnLines = ClosestPointsBetweenLines(line1, line2);
    return Math::Distance(closestPointsOnLines.first, closestPointsOnLines.second);
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot)
{
    return PointIsOnLine(line, spot.orientation.GetPosition());
}

bool Engulfs(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2)
{
    if (line1.shape.direction != line2.shape.direction)
    {
        return false;
    }

    if (PointIsOnLine(line1, line2.orientation.GetPosition()))
    {
        return (line1.shape.infinite || (!line2.shape.infinite && PointIsOnLine(line1, LineEndpoint(line2))));
    }

    return false;
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Plane>& plane)
{
    if (plane.shape.infinite || Math::Dot(EffectiveDirection(line), EffectiveNormal(plane)) != 0.0f)
    {
        return false;
    }

    CORE_THROW("3DFunctions", "This is wrong, we would need to handle rotations");
    return Engulfs(ShapeOrientation<Line2D>(line.orientation, Line2D()), ShapeOrientation2D(plane.orientation, plane.shape.shape));
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Sphere>& sphere)
{
    if (sphere.shape.radius != 0.0f)
    {
        return false;
    }

    return Engulfs(line, ShapeOrientation<Spot3D>(sphere.orientation, Spot3D()));
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Box>& box)
{
    if (box.shape.dimensions != Core::Math::Float3(0.0f))
    {
        return false;
    }

    return Engulfs(line, ShapeOrientation<Spot3D>(box.orientation, Spot3D()));
}

float Distance(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float Distance(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float Distance(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot)
{
    // do we care about case where spot is on plane?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line)
{
    // do we care about case where line is on plane?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2)
{
    // do we care about case where plane2 is on plane1?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Sphere>& sphere)
{
    // do we care about case where sphere.origin is on plane && plane.radius == 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Box>& box)
{
    // do we care about case where box.origin is on plane && box.dimensions == 0?
    return false;
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Spot3D>& spot)
{
    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return std::max(0.0f, Distance(sphereCenter, spot) - EffectiveRadius(sphere));
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return std::max(0.0f, Distance(line, sphereCenter) - EffectiveRadius(sphere));
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return std::max(0.0f, Distance(plane, sphereCenter) - EffectiveRadius(sphere));
}

float Distance(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    ShapeOrientation<Spot3D> sphere2Center = { sphere2.orientation, Spot3D() };
    return std::max(0.0f, Distance(sphere1, sphere2Center) - EffectiveRadius(sphere1));
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Spot3D>& spot)
{
    return Distance(sphere, spot) <= sphere.shape.radius;
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    if (line.shape.infinite)
    {
        return false;
    }

    return PointIsInSphere(sphere, line.orientation.GetPosition()) && PointIsInSphere(sphere, LineEndpoint(line));
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    if (plane.shape.infinite)
    {
        return false;
    }

    // return Engulfs(SphereAsCircleOnPlane(sphere, plane), plane);
    CORE_THROW("3DFunctions", "Unfinished Implementation");
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    return (Distance(sphere1, sphere2) + EffectiveRadius(sphere2)) <= EffectiveRadius(sphere1);
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Box>& box)
{
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

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    if (PointInBox(box, spot))
    {
        return 0.0f;
    }

    const auto closestPoint = ClosestPointToPoint(box, spot);
    return Distance(closestPoint, spot.orientation.GetPosition());
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line)
{
    return Distance(line, ShapeOrientation<Spot3D>(Transform(ClosestPointToLine(box, line)), Spot3D()));
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;

    // closest point on plane to box
    // distance from box to that point
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere)
{
    return std::max(0.0f, Distance(box, ShapeOrientation<Spot3D>(sphere.orientation, Spot3D())) - EffectiveRadius(sphere));
}

float Distance(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2)
{
    // the below is wrong, doesn't account for edge-edge contact. need to get all the EDGES of box 2 and check them for box1, then
    // check corners of box1 against box 2
    // i think, does it need to be the edges of each?

    const auto box2Edges = BoxEdges(box2);
    const auto box1Edges = BoxEdges(box1);

    bool first = true;
    float minimumDistance;
    // closest point from box1 to a box2 corner
    for (const auto& edge : box2Edges)
    {
        const auto closestInBoxToEdge = ClosestPointToLine(box1, edge);
        const auto closestPointOnEdgeToBox = ClosestPointOnLine(edge, closestInBoxToEdge);
        const auto distance = Distance(closestInBoxToEdge, closestPointOnEdgeToBox);
        
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
    // need to check the opposite too, as they may be closer
    for (const auto& edge : box1Edges)
    {
        const auto closestInBoxToEdge = ClosestPointToLine(box2, edge);
        const auto closestPointOnEdgeToBox = ClosestPointOnLine(edge, closestInBoxToEdge);
        const auto distance = Distance(closestInBoxToEdge, closestPointOnEdgeToBox);

        minimumDistance = std::min(distance, minimumDistance);

        if (minimumDistance <= 0.0f)
        {
            return 0.0f;
        }
    }

    return std::max(0.0f, minimumDistance);
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    return PointInBox(box, spot);
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line)
{
    if (line.shape.infinite)
    {
        return false;
    }

    return PointInBox(box, line.orientation.GetPosition()) && PointInBox(box, LineEndpoint(line));
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane)
{
    if (plane.shape.infinite)
    {
        return false;
    }

    // get defining points on shape on plane, check if all points are in box
    CORE_THROW("3DFunctions", "Unfinished Implementation");
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere)
{
    const auto sphereExtremes = SphereAxisExtremes(sphere, box.orientation.GetRotation().Inverse());

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
} // namespace Geometric
} // namespace Core