#include "Core/Geometric/3D/Line3D.h"

#include "Core/Geometric/3D/Plane.h"

namespace Core
{
namespace Geometric
{
Line3D::Line3D()
: Line3D(Math::Float3(0.0f), Math::Float3(1.0f, 0.0f, 0.0f))
{}

Line3D::Line3D(const Math::Float3 &origin, const Math::Float3 &direction)
: _origin(origin)
, _direction(direction)
, _length(0.0f)
, _infinite(true)
{}

Line3D::Line3D(const Math::Float3 &origin, const Math::Float3 &direction, const float& length)
: _origin(origin)
, _direction(direction)
, _length(length)
, _infinite(false)
{}

bool Line3D::operator==(const Line3D& other) const
{
    return _origin == other._origin &&
            _direction == other._direction &&
            _length == other._length &&
            _infinite == other._infinite;
}

bool Line3D::operator!=(const Line3D& other) const
{
    return !(*this == other);
}

void Line3D::SetOrigin(const Math::Float3 &origin)
{
    _origin = origin;
}

void Line3D::AdjustOrigin(const Math::Float3 &adjustment)
{
    _origin += adjustment;
}

Math::Float3 Line3D::GetOrigin() const
{
    return _origin;
}

void Line3D::SetDirection(const Math::Float3& direction)
{
    _direction = direction;
}

void Line3D::AdjustDirection(const Math::Float3& adjustment)
{
    _direction += adjustment;
}

Math::Float3 Line3D::GetDirection() const
{
    return _direction;
}

void Line3D::SetLength(const float& length)
{
    _infinite = false;
    _length = length;
}

void Line3D::AdjustLength(const float& adjustment)
{
    _infinite = false;
    _length += adjustment;
}

float Line3D::GetLength() const
{
    return _length;
}

void Line3D::SetInfinite()
{
    _infinite = true;
}

bool Line3D::IsInfinite() const
{
    return _infinite;
}

Plane Line3D::GetNormal(const Math::Float3& atPoint) const
{
    return Plane(*this);
}

Line3D Rotate(const Line3D& line, const Math::FQuaternion& rotation);

float Distance(const Line3D& line, const Math::Float3& point);
float Distance(const Line3D& line1, const Line3D& line2);

bool Intersect(const Line3D& line, const Math::Float3& point);
bool Intersect(const Line3D& line1, const Line3D& line2);
} // namespace Geometric
} // namespace Core