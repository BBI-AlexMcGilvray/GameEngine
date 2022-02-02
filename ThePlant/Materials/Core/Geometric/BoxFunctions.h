#pragma once

#include <utility>

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
// NOTE: These should all forward to using the base 'shape' so that those methods also exist (we don't need the orientation)

Math::Float3 EffectiveDimensions(const ShapeOrientation<Box>& box);

bool PointInBox(const ShapeOrientation<Box>& box, const Point3D& point);
bool PointInBox(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot);

// we always assume boxes are not rotated, instead rotated the other shape
Math::Float3 BoxMaxCenteredAt0(const ShapeOrientation<Box>& box);
Math::Float3 BoxMinCenteredAt0(const ShapeOrientation<Box>& box);

// order of the corners is NOT guaranteed
std::array<Math::Float3, 8> BoxCorners(const ShapeOrientation<Box>& box);

// we always assume boxes are not rotated, instead rotated the other shape
Math::Float3 LastPointOnBoxInDirection(const ShapeOrientation<Box>& box, const Math::Float3& direction);

Math::Float3 ClosestPointToPoint(const ShapeOrientation<Box>& box, const Point3D& point);
Math::Float3 ClosestPointToPoint(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot);
// probably not the most efficient, but can deal with that later
Math::Float3 ClosestPointToLine(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line, const float& precision = Math::DEFAULT_PRECISION());
} // namespace Geometric
} // namespace Core