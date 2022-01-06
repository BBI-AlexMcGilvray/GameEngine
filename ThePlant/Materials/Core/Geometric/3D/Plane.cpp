#include "Core/Geometric/3D/Plane.h"

#include "Core/Geometric/3D/Line3D.h"
#include "Core/Math/Headers/VectorFunctions.h"

namespace Core
{
namespace Geometric
{
Plane::Plane()
: Plane(Math::Float3(1.0f, 0.0f, 0.0f), Math::Float3(0.0f))
{}

Plane::Plane(const Line3D& line);
: Plane(line.GetDirection(), line.GetOrigin())
{}

Plane::Plane(const Math::Float3& normal, const Math::Float3& origin)
: _normal(normal)
, _origin(origin)
, _dimensions(1.0f)
, _infinite(true)
{}

Plane::Plane(const Math::Float3& normal, const Math::Float3& origin, const Math::Float2& dimensions)
: _normal(normal)
, _origin(origin)
, _dimensions(dimensions)
, _infinite(false)
{}

bool Plane::operator==(const Plane& other) const
{
    return _normal == other._normal &&
            _origin == other._origin &&
            _dimensions == other._dimensions &&
            _infinite == other._infinite;
}

bool Plane::operator!=(const Plane& other) const
{
    return !(*this == other);
}

void Plane::SetNormal(const Math::Float3 &normal)
{
    _normal = normal;
}

void Plane::AdjustNormal(const Math::Float3 &adjustment)
{
    _normal += adjustment;
}

Math::Float3 Plane::GetNormal() const
{
    return _normal;
}

void Plane::SetOrigin(const Math::Float3& origin)
{
    _origin = origin;
}

void Plane::AdjustOrigin(const Math::Float3& adjustment)
{
    _origin += adjustment;
}

Math::Float3 Plane::GetOrigin() const
{
    return _origin;
}

void Plane::SetDimensions(const Math::Float2& dimensions)
{
    _infinite = false;
    _dimensions = dimensions;
}

void Plane::AdjustDimensions(const Math::Float2& adjustment)
{
    _infinite = false;
    _dimensions += adjustment;
}

Math::Float2 Plane::GetDimensions() const
{
    return _dimensions;
}

void Plane::SetInfinite()
{
    _infinite = true;
}

bool Plane::IsInfinite() const
{
    return _infinite;
}

Plane _BetweenPoints(const Math::Float3& point1, const Math::Float3& point2, const Math::Float3& point3, const Math::Float2& dimensions, const bool& infinite)
{
    Math::Float3 origin = (point1 + point2 + point3) / 3.0f;
    Math::Float3 normal = Math::CrossProduct(point3 - point1, point3 - point2);
    if (infinite)
    {
        return Plane(normal, origin);
    }
    return Plane(normal, origin, dimensions)
}

Plane BetweenPoints(const Math::Float3& point1, const Math::Float3& point2, const Math::Float3& point3)
{
    _BetweenPoints(point1, point2, point3, Math::Float2(), true);
}

Plane BetweenPoints(const Math::Float3& point1, const Math::Float3& point2, const Math::Float3& point3, const Math::Float2& dimensions)
{
    _BetweenPoints(point1, point2, point3, dimensions, false);
}

Plane Rotate(const Plane& plane, const Math::FQuaternion& rotation);

float Distance(const Plane& plane, const Math::Float3& point);
float Distance(const Plane& plane, const Line3D& line);
float Distance(const Plane& plane1, const Plane& plane2);

bool Intersect(const Plane& plane, const Math::Float3& point);
bool Intersect(const Plane& plane, const Line3D& line);
bool Intersect(const Plane& plane1, const Plane& plane2);
} // namespace Geometric
} // namespace Core