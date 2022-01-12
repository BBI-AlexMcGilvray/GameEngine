#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
    // POINT
    float Distance(const ShapeOrientation<Point>& point1, const ShapeOrientation<Point>& point2);
    bool Engulfs(const ShapeOrientation<Point>& point1, const ShapeOrientation<Point>& point2);

    // LINE
    float Distance(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Point>& point);
    float Distance(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2);
    bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Point>& point);
    bool Engulfs(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2);

    // PLANE
    float Distance(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Point>& point);
    float Distance(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line);
    float Distance(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2);
    bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Point>& point);
    bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line);
    bool Engulfs(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2);
    
    // SPHERE
    float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Point>& point);
    float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line);
    float Distance(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane);
    float Distance(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Point>& point);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2);

    // BOX
    float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Point>& point);
    float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line);
    float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane);
    float Distance(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere);
    float Distance(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Point>& point);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere);
    bool Engulfs(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2);
}// namespace Geometric
}// namespace Core