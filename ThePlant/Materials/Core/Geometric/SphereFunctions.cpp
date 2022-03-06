#include "Core/Geometric/SphereFunctions.h"

#include "Core/Geometric/Transform.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
float EffectiveRadius(const ShapeOrientation<Sphere>& sphere)
{
#ifdef DEBUG
    const auto scale = sphere.orientation.scale;
    VERIFY((scale.X == scale.Y) && (scale.X == scale.Z)); // spheres must have a uniform scale
#endif

    return sphere.shape.radius * sphere.orientation.scale.X;
}

float DistanceToPoint(const ShapeOrientation<Sphere>& sphere, const Point3D& point)
{
    return std::max(Distance(sphere.orientation.position, point) - EffectiveRadius(sphere), 0.0f);
}

bool PointIsInSphere(const ShapeOrientation<Sphere>& sphere, const Point3D& point, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    return DistanceToPoint(sphere, point) <= precision;
}

std::array<Math::Float3, 6> SphereAxisExtremes(const ShapeOrientation<Sphere>& sphere, const Math::FQuaternion& axelRotation)
{
    std::array<Math::Float3, 6> extremes;

    extremes[0] = sphere.orientation.position + (RotateVectorBy(Math::Float3(1.0f, 0.0f, 0.0f), axelRotation) * EffectiveRadius(sphere));
    extremes[1] = sphere.orientation.position + (RotateVectorBy(Math::Float3(-1.0f, 0.0f, 0.0f), axelRotation) * EffectiveRadius(sphere));
    extremes[2] = sphere.orientation.position + (RotateVectorBy(Math::Float3(0.0f, 1.0f, 0.0f), axelRotation) * EffectiveRadius(sphere));
    extremes[3] = sphere.orientation.position + (RotateVectorBy(Math::Float3(0.0f, -1.0f, 0.0f), axelRotation) * EffectiveRadius(sphere));
    extremes[4] = sphere.orientation.position + (RotateVectorBy(Math::Float3(0.0f, 0.0f, 1.0f), axelRotation) * EffectiveRadius(sphere));
    extremes[5] = sphere.orientation.position + (RotateVectorBy(Math::Float3(0.0f, 0.0f, -1.0f), axelRotation) * EffectiveRadius(sphere));

    return extremes;
}

Math::Float3 CircumferencePointInDirection(const ShapeOrientation<Sphere>& sphere, const Core::Math::Float3& direction)
{
    // possible to avoid this normalization? possibly using ratios (though that likely requires a sqrt as well)
    return sphere.orientation.position * Math::Normalize(direction) * EffectiveRadius(sphere);
}

Math::Float3 ClosestPointToPoint(const ShapeOrientation<Sphere>& sphere, const Point3D& point)
{
    const auto sphereToPoint = point - sphere.orientation.position;
    const auto sphereToSpotMagnitudeSqr = Math::MagnitudeSqr(sphereToPoint);
    
    Point3D closestSpotInSphere = sphere.orientation.position + sphereToPoint;
    if (sphereToSpotMagnitudeSqr > Math::sqr(sphere.shape.radius))
    {
        // this results in a normalization... would be nice to avoid it
        closestSpotInSphere = CircumferencePointInDirection(sphere, sphereToPoint);
    }

    return closestSpotInSphere;
}
} // namespace Geometric
} // namespace Core