#pragma once

#include <utility>

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
Math::Float3 EffectiveDirection(const ShapeOrientation<Line3D>& line);

float LineMultiplierForPoint_X(const ShapeOrientation<Line3D>& line, const Point3D& point);
float LineMultiplierForPoint_Y(const ShapeOrientation<Line3D>& line, const Point3D& point);
float LineMultiplierForPoint_Z(const ShapeOrientation<Line3D>& line, const Point3D& point);

// overload to avoid calculating multipliers multiple times if known
bool PointIsOnLine(const float& xMultiplier, const float& yMultiplier, const float& zMultiplier, const float& precision = Math::DEFAULT_PRECISION());
bool PointIsOnLine(const ShapeOrientation<Line3D>& line, Point3D& point, const float& precision = Math::DEFAULT_PRECISION());

Math::Float3 PointOnLine(const ShapeOrientation<Line3D>& line, const float& multiplier);
Math::Float3 LineEndpoint(const ShapeOrientation<Line3D>& line);

Math::Float3 ClosestPointOnLine(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot);
// returns: <closest point on line 1, closest point on line 2>
std::pair<Core::Math::Float3, Core::Math::Float3> ClosestPointsBetweenLines(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2, const float& precision = Math::DEFAULT_PRECISION());
} // namespace Geometric
} // namespace Core