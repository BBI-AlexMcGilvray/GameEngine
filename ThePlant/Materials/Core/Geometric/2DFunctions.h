#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
float Distance(const ShapeOrientation<Point2D>& point1, const ShapeOrientation<Point2D>& point2);

float Distance(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Point2D>& point);
float Distance(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Circle>& point);

float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Point2D>& point);
float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle);
float Distance(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2);

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Point2D>& point);
float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle);
float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line);
float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Rectangle>& rectangle);
} // namespace Geometric
} // namespace Core