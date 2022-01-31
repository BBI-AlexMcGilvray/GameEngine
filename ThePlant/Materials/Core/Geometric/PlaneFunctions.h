#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
Math::Float3 EffectiveNormal(const ShapeOrientation<Plane>& plane);

Point3D ClosestPointOnPlaneTo(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot);
} // namespace Geometric
} // namespace Core