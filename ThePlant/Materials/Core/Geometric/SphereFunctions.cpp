#include "Core/Geometric/SphereFunctions.h"

#include "Core/Geometric/Transform.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
float EffectiveRadius(const ShapeOrientation<Sphere>& sphere)
{
#ifdef DEBUG
    const auto scale = sphere.orientation.GetScale();
    VERIFY(scale.X == scale.Y && scale.X == scale.Z); // spheres must have a uniform scale
#endif

    return sphere.shape.radius * sphere.orientation.GetScale().X;
}

float DistanceToPoint(const ShapeOrientation<Sphere>& sphere, const Point3D& point)
{
    return std::max(Distance(sphere.orientation.GetPosition(), point) - EffectiveRadius(sphere), 0.0f);
}

bool PointIsInSphere(const ShapeOrientation<Sphere>& sphere, const Point3D& point, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    return DistanceToPoint(sphere, point) <= precision;
}

std::array<Math::Float3, 4> SphereAxisExtremes(const ShapeOrientation<Sphere>& sphere, const Math::FQuaternion& axelRotation)
{
    std::array<Math::Float3, 4> extremes;
}

Math::Float3 CircumferencePointInDirection(const ShapeOrientation<Sphere>& sphere, const Core::Math::Float3& direction)
{
    return sphere.orientation.GetPosition() * Math::Normalize(direction) * EffectiveRadius(sphere);
}
} // namespace Geometric
} // namespace Core