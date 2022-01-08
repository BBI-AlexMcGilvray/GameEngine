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
} // namespace Geometric
} // namespace Core