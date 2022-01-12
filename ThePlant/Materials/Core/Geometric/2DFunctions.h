#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
/*
NOTE: These are all for 2D shapes, we assume they are on the same x,y-plane and that the z-axis is not used
*/
// CIRCLE
float Distance(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Point>& point);
float Distance(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2);
bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Point>& point);
bool Engulfs(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2);

// LINE
float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Point>& point);
float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle);
float Distance(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2);
bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Point>& point);
bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle);
bool Engulfs(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2);

// RECTANGLE
float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Point>& point);
float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle);
float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line);
float Distance(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Point>& point);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2);
} // namespace Geometric
} // namespace Core