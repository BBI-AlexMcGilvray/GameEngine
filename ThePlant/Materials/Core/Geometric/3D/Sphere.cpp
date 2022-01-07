#include "Core/Geometric/3D/Sphere.h"

#include "Core/Geometric/3D/Line3D.h"
#include "Core/Geometric/3D/Plane.h"
#include "Core/Math/Headers/VectorFunctions.h"

namespace Core
{
namespace Geometric
{
Sphere::Sphere(const Math::Float3& origin)
: Sphere(origin, 1.0f)
{}

Sphere::Sphere(const Math::Float3& origin, const float& radius)
: _origin(origin)
, _radius(radius)
{}

bool Sphere::operator==(const Sphere& other) const
{
    return _origin == other._origin &&
            _radius == other._radius;
}

bool Sphere::operator!=(const Sphere& other) const
{
    return !(*this == other);
}

void Sphere::SetRadius(const float& radius)
{
    _radius = radius;
}

void Sphere::AdjustRadius(const float& adjustment)
{
    _radius += adjustment;
}

float Sphere::GetRadius() const
{
    return _radius;
}

void Sphere::SetOrigin(const Math::Float3 &origin)
{
    _origin = origin;
}

void Sphere::AdjustOrigin(const Math::Float3 &adjustment)
{
    _origin += adjustment;
}

Math::Float3 Sphere::GetOrigin() const
{
    return _origin;
}

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

bool Intersect(const Sphere& sphere, const Math::Float3& point, const float& variance/* = 0.01f*/);
bool Intersect(const Sphere& sphere, const Line3D& line, const float& variance/* = 0.01f*/);
bool Intersect(const Sphere& sphere, const Plane& plane, const float& variance/* = 0.01f*/);
bool Intersect(const Sphere& sphere1, const Sphere& sphere2, const float& variance/* = 0.01f*/);
} // namespace Geometric
} // namespace Core