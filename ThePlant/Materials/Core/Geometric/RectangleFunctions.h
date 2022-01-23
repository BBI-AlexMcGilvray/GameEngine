#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
// rectangles have origin at (0,0)
Math::Float2 RectangleMaxCenteredAt0(const Rectangle& rectangle);
Math::Float2 RectangleMinCenteredAt0(const Rectangle& rectangle);

// assumes rectangle has origin at (0,0)
bool PointInRectangle(const Rectangle& rectangle, const Point2D& point);
bool PointInRectangle(const ShapeOrientation<Rectangle>& rectangle, const Point2D& point);

// assumes rectangle is centered on (0,0)
Math::Float2 LastPointOnRectangleInDirection(const Rectangle& rectangle, const Math::Float2& direction);
Math::Float2 LastPointOnRectangleInDirection(const ShapeOrientation<Rectangle>& rectangle, const Math::Float2& direction);

Math::Float2 ClosestPointToPoint(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Point>& point, const float& precision = Math::DEFAULT_PRECISION());
// probably not the most efficient, but can deal with that later
Math::Float2 ClosestPointToLine(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line, const float& precision = Math::DEFAULT_PRECISION());
} // namespace Geometric
} // namespace Core