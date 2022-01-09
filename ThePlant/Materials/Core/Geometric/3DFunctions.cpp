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

float Distance(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Point>& point);
float Distance(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2);

float Distance(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Point>& point);
float Distance(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line);
float Distance(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2);

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Point>& point)
{
    ShapeOrientation<Point> sphereCenter = { Point(), sphere.orientation };
    return std::min(0.0f, Distance(sphereCenter, point) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line)
{
    ShapeOrientation<Point> sphereCenter = { Point(), sphere.orientation };
    return std::min(0.0f, Distance(line, sphereCenter) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane)
{
    ShapeOrientation<Point> sphereCenter = { Point(), sphere.orientation };
    return std::min(0.0f, Distance(plane, sphereCenter) - sphere.shape.radius);
}

float Distance(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2)
{
    ShapeOrientation<Point> sphereCenter = { Point(), sphere1.orientation };
    return std::min(0.0f, Distance(sphere2, sphereCenter) - sphere1.shape.radius);
}

float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Point>& point);
float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line);
float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane);
float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere);
float Distance(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2);
} // namespace Geometric
} // namespace Core