#include "Core/Geometric/PlaneFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
Math::Float3 EffectiveNormal(const ShapeOrientation<Plane>& plane)
{
    return Math::RotateVectorBy(plane.shape.normal, plane.orientation.rotation);
}

Point3D ClosestPointOnPlaneTo(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot)
{
    Math::Float3 planeToSpot = Math::RotateVectorBy(spot.orientation.position, plane.orientation.rotation.Inverse()) - plane.orientation.position;
    Math::Float3 planeToClosest = Math::Perp(planeToSpot, plane.shape.normal);
    return plane.orientation.position + planeToClosest;
}
} // namespace Geometric
} // namespace Core