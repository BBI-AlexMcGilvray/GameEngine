#include "Core/Geometric/3D/Sphere.h"

#include "Core/Geometric/3D/Line3D.h"
#include "Core/Geometric/3D/Plane.h"

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

float Distance(const Sphere& sphere, const Math::Float3& point);
float Distance(const Sphere& sphere, const Line3D& line);
float Distance(const Sphere& sphere, const Plane& plane);
float Distance(const Sphere& sphere1, const Sphere& sphere2);

bool Intersect(const Sphere& sphere, const Math::Float3& point);
bool Intersect(const Sphere& sphere, const Line3D& line);
bool Intersect(const Sphere& sphere, const Plane& plane);
bool Intersect(const Sphere& sphere1, const Sphere& sphere2);
} // namespace Geometric
} // namespace Core