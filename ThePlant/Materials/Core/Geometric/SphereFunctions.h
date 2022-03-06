#pragma once

#include <utility>

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
// NOTE: These should all forward to using the base 'shape' so that those methods also exist (we don't need the orientation)

float EffectiveRadius(const ShapeOrientation<Sphere>& sphere);

float DistanceToPoint(const ShapeOrientation<Sphere>& sphere, const Point3D& point);
bool PointIsInSphere(const ShapeOrientation<Sphere>& sphere, const Point3D& point, const float& precision = Math::DEFAULT_PRECISION());

std::array<Math::Float3, 6> SphereAxisExtremes(const ShapeOrientation<Sphere>& sphere, const Math::FQuaternion& axelRotation);

Math::Float3 CircumferencePointInDirection(const ShapeOrientation<Sphere>& sphere, const Core::Math::Float3& direction);
Math::Float3 ClosestPointToPoint(const ShapeOrientation<Sphere>& sphere, const Point3D& point);
} // namespace Geometric
} // namespace Core