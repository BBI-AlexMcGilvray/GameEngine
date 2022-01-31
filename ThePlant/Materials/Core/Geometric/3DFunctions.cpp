#include "Core/Geometric/3DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Geometric/Functions.h"
#include "Core/Geometric/Line3DFunctions.h"
#include "Core/Geometric/PlaneFunctions.h"

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
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
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
    return std::max(0.0f, Distance(sphereCenter, spot) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return std::max(0.0f, Distance(line, sphereCenter) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    ShapeOrientation<Spot3D> sphereCenter = { sphere.orientation, Spot3D() };
    return std::max(0.0f, Distance(plane, sphereCenter) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    ShapeOrientation<Spot3D> sphere2Center = { sphere2.orientation, Spot3D() };
    return std::max(0.0f, Distance(sphere1, sphere2Center) - sphere1.shape.radius);
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Spot3D>& spot)
{
    return Distance(sphere, spot) <= sphere.shape.radius;
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    return (Distance(sphere1, sphere2) + sphere2.shape.radius) <= sphere1.shape.radius;
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Box>& box)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float Distance(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}

bool Engulfs(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return false;
}
} // namespace Geometric
} // namespace Core