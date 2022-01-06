#include "Core/Geometric/3D/Box.h"

#include "Core/Geometric/3D/Line3D.h"
#include "Core/Geometric/3D/Plane.h"
#include "Core/Geometric/3D/Sphere.h"
#include "Core/Math/Headers/VectorFunctions.h"

namespace Core
{
namespace Geometric
{
Box::Box(const Math::Float3& origin)
: Box(origin - Math::Float3(0.5f), origin + Math::Float3(0.5f))
{}

Box::Box(const Math::Float3& min, const Math::Float3& max)
: _min(min)
, _max(max)
{}

bool Box::operator==(const Box& other) const
{
    return _min == other._min &&
            _max == other._max;
}
bool Box::operator!=(const Box& other) const
{
    return !(*this == other);
}

void Box::SetMin(const Math::Float3& min)
{
    _min = min;
    _max = Math::Max(_min, _max);
}

void Box::AdjustMin(const Math::Float3& adjustment)
{
    _min += adjustment;
    _max = Math::Max(_min, _max);
}

Math::Float3 Box::GetMin() const
{
    return _min;
}

void Box::SetMax(const Math::Float3& max)
{
    _max = max;
    _min = Math::Min(_min, _max);
}

void Box::AdjustMin(const Math::Float3& adjustment)
{
    _max += adjustment;
    _min = Math::Min(_min, _max);
}

Math::Float3 Box::GetMax() const
{
    return _max;
}

Math::Float3 Box::GetDimensions() const
{
    return _max - _min;
}

Math::Float3 Box::GetOrigin() const
{
    return _min + (_max - _min);
}

Box FromDimensions(const Math::Float3& origin, const Math::Float3& dimensions);

float Distance(const Box& box, const Math::Float3& point);
float Distance(const Box& box, const Line3D& line);
float Distance(const Box& box, const Plane& plane);
float Distance(const Box& box, const Sphere& sphere);
float Distance(const Box& box1, const Box& box2);

bool Intersect(const Box& box, const Math::Float3& point);
bool Intersect(const Box& box, const Line3D& line);
bool Intersect(const Box& box, const Plane& plane);
bool Intersect(const Box& box, const Sphere& sphere);
bool Intersect(const Box& box1, const Box& box2);
} // namespace Geometric
} // namespace Core