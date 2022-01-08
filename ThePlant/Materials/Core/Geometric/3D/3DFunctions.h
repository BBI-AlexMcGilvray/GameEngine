#pragma once

#include "Core/Geometric/3D/Box.h"
#include "Core/Geometric/3D/Line3D.h"
#include "Core/Geometric/3D/Plane.h"
#include "Core/Geometric/3D/Sphere.h"

#include "Core/Math/Headers/MathDefs.h"

namespace Core {
namespace Geometric {
    // LINE
    float Distance(const Line3D& line, const Math::Float3& point);
    float Distance(const Math::Float3& point, const Line3D& line)
    {
        return Distance(line, point);
    }
    float Distance(const Line3D& line1, const Line3D& line2);

    // PLANE
    float Distance(const Plane& plane, const Math::Float3& point);
    float Distance(const Math::Float3& point, const Plane& plane)
    {
        return Distance(plane, point);
    }
    float Distance(const Plane& plane, const Line3D& line);
    float Distance(const Line3D& line, const Plane& plane)
    {
        return Distance(plane, line);
    }
    float Distance(const Plane& plane1, const Plane& plane2);
    
    // SPHERE
    float Distance(const Sphere& sphere, const Math::Float3& point);
    float Distance(const Math::Float3& point, const Sphere& sphere)
    {
        return Distance(sphere, point);
    }
    float Distance(const Sphere& sphere, const Line3D& line);
    float Distance(const Line3D& line, const Sphere& sphere)
    {
        return Distance(sphere, line);
    }
    float Distance(const Sphere& sphere, const Plane& plane);
    float Distance(const Plane& plane, const Sphere& sphere)
    {
        return Distance(sphere, plane);
    }
    float Distance(const Sphere& sphere1, const Sphere& sphere2);

    // BOX
    float Distance(const Box& box, const Math::Float3& point);
    float Distance(const Math::Float3& point, const Box& box)
    {
        return Distance(box, point);
    }
    float Distance(const Box& box, const Line3D& line);
    float Distance(const Line3D& line, const Box& box)
    {
        return Distance(box, line);
    }
    float Distance(const Box& box, const Plane& plane);
    float Distance(const Plane& plane, const Box& box)
    {
        return Distance(box, plane);
    }
    float Distance(const Box& box, const Sphere& sphere);
    float Distance(const Sphere& sphere, const Box& box)
    {
        return Distance(box, sphere);
    }
    float Distance(const Box& box1, const Box& box2);

    // GENERIC INTERSECTION
    template <typename T1, typename T2>
    bool Intersect(const T1& shape1, const T2& shape2, const float& variance = 0.01f)
    {
        return Distance(shape1, shape2) <= variance;
    }

    template <typename T1, typename T2, typename PRECISION = Math::Precision<100>>
    bool Intersect(const T1& shape1, const T2& shape2)
    {
        return Intersect(shape1, shape2, PRECISION());
    }
}// namespace Geometric
}// namespace Core