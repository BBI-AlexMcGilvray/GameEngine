#include "Core/Geometric/3D/3DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
namespace Geometric
{
float Distance(const Line3D& line, const Math::Float3& point)
{
    auto originToP = point - line.GetOrigin();

    auto pOntoLine = Math::Project(originToP, line.GetDirection());
    auto perpToP = originToP - Math::Perp(originToP, line.GetDirection());

    auto intersectionPoint = line.GetOrigin() + pOntoLine;

    // point is 'behind' the line origin
    if (Math::Dot(pOntoLine, line.GetDirection()) < 0)
    {
        return Math::Magnitude(originToP);
    }

    // give closest point on line to point
    if (line.IsInfinite())
    {
        return Math::Magnitude(perpToP);
    }

    // point is passed the end of the line
    if (Math::MagnitudeSqr(pOntoLine) > Math::sqr(line.GetLength()))
    {
        Math::Float3 endOfLine = line.GetOrigin() + (Math::Magnitude(line.GetDirection()) * line.GetLength());
        return Math::Magnitude(point - endOfLine);
    }

    return Math::Magnitude(intersectionPoint);
}

float Distance(const Line3D& line1, const Line3D& line2);

float Distance(const Plane& plane, const Math::Float3& point);
float Distance(const Plane& plane, const Line3D& line);
float Distance(const Plane& plane1, const Plane& plane2);

float Distance(const Sphere& sphere, const Math::Float3& point)
{
    return std::min(Math::Magnitude(point - sphere.GetOrigin()) - sphere.GetRadius(), 0.0f);
}

float Distance(const Sphere& sphere, const Line3D& line)
{
    return std::min(Distance(sphere.GetOrigin(), line) - sphere.GetRadius(), 0.0f);
}

float Distance(const Sphere& sphere, const Plane& plane)
{
    return std::min(Distance(sphere.GetOrigin(), plane) - sphere.GetRadius(), 0.0f);
}

float Distance(const Sphere& sphere1, const Sphere& sphere2)
{
    return std::min(Math::Magnitude(sphere1.GetOrigin() - sphere2.GetOrigin()) - (sphere1.GetRadius() + sphere2.GetRadius()), 0.0f);
}

float Distance(const Box& box, const Math::Float3& point);
float Distance(const Box& box, const Line3D& line);
float Distance(const Box& box, const Plane& plane);

float Distance(const Box& box, const Sphere& sphere)
{
    return std::min(Distance(box, sphere.GetOrigin()) - sphere.GetRadius(), 0.0f);
}

float Distance(const Box& box1, const Box& box2);
} // namespace Geometric
} // namespace Core