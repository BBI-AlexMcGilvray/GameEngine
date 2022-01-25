#include "Core/Geometric/3DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
namespace Geometric
{
float Distance(const ShapeOrientation<Point>& point1, const ShapeOrientation<Point>& point2)
{
    return Math::Distance(point1.orientation.GetPosition(), point2.orientation.GetPosition());
}

bool Engulfs(const ShapeOrientation<Point>& point1, const ShapeOrientation<Point>& point2)
{
    return point1.orientation == point2.orientation;
}

bool Engulfs(const ShapeOrientation<Point>& point, const ShapeOrientation<Line3D>& line)
{
    // do we care about case where point == line.origin && line.length = 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Point>& point, const ShapeOrientation<Plane>& plane)
{
    // do we care about case where point == plane.origin && line.dimensions = 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Point>& point, const ShapeOrientation<Sphere>& sphere)
{
    // do we care about case where point == sphere.origin && sphere.radius = 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Point>& point, const ShapeOrientation<Box>& box)
{
    // do we care about case where point == box.origin && box.dimensions = 0?
    return false;
}

float Distance(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Point>& point)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

float Distance(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2)
{
    CORE_ERROR("3DFunctions", "Implementation Missing");
    return -1.0f;
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Point>& point)
{
    // do we care about case where point is on line?
    return false;
}

bool Engulfs(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line)
{
    // do we care about case where line2 is on line1?
    return false;
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Plane>& plane)
{
    // do we care about case where plane.origin is on line && plane.dimensions == 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Sphere>& sphere)
{
    // do we care about case where sphere.origin is on line && sphere.radius == 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Box>& box)
{
    // do we care about case where box.origin is on line && box.dimensions == 0?
    return false;
}

float Distance(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Point>& point)
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

bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Point>& point)
{
    // do we care about case where point is on plane?
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

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Point>& point)
{
    ShapeOrientation<Point> sphereCenter = { sphere.orientation, Point() };
    return std::abs(Distance(sphereCenter, point) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    ShapeOrientation<Point> sphereCenter = { sphere.orientation, Point() };
    return std::abs(Distance(line, sphereCenter) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    ShapeOrientation<Point> sphereCenter = { sphere.orientation, Point() };
    return std::abs(Distance(plane, sphereCenter) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    ShapeOrientation<Point> sphere2Center = { sphere2.orientation, Point() };
    return std::abs(Distance(sphere1, sphere2Center) - sphere1.shape.radius);
}

bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Point>& point)
{
    return Distance(sphere, point) <= sphere.shape.radius;
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

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Point>& point)
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

bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Point>& point)
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