#include "Core/Geometric/PlaneFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
Math::Float3 EffectiveNormal(const ShapeOrientation<Plane>& plane)
{
    return Math::RotateNormalVectorBy(plane.shape.normal, plane.orientation.GetRotation());
}

Point3D ClosestPointOnPlaneTo(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot)
{
    Math::Float3 planeToSpot = Math::RotateVectorBy(spot.orientation.GetPosition(), plane.orientation.GetRotation().Inverse()) - plane.orientation.GetPosition();
    Math::Float3 planeToClosest = Math::Perp(planeToSpot, plane.shape.normal);
    return plane.orientation.GetPosition() + planeToClosest;
}
} // namespace Geometric
} // namespace Core