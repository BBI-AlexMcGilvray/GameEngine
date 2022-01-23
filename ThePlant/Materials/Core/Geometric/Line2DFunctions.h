#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
Math::Float2 EffectiveDirection(const ShapeOrientation<Line2D>& line);

float LineMultiplierForPoint_X(const ShapeOrientation<Line2D>& line, const Point2D& point);
float LineMultiplierForPoint_Y(const ShapeOrientation<Line2D>& line, const Point2D& point);

// overload to avoid calculating multipliers multiple times if known
bool PointIsOnLine(const float& xMultiplier, const float& yMultiplier, const float& precision = Math::DEFAULT_PRECISION());
bool PointIsOnLine(const ShapeOrientation<Line2D>& line, Point2D& point, const float& precision = Math::DEFAULT_PRECISION());

Math::Float2 PointOnLine(const ShapeOrientation<Line2D>& line, const float& multiplier);
Math::Float2 LineEndpoint(const ShapeOrientation<Line2D>& line);

Math::Float2 ClosestPointOnLine(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Point>& point);
} // namespace Geometric
} // namespace Core