#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
/*
NOTE: These are all for 2D shapes, we assume they are on the same x,y-plane and that the z-axis is not used

NOTE: All DistanceSqr(...) methods return POSITIVE values
*/
// SPOT
float DistanceSqr(const ShapeOrientation<Spot2D>& spot1, const ShapeOrientation<Spot2D>& spot2);
bool Engulfs(const ShapeOrientation<Spot2D>& spot1, const ShapeOrientation<Spot2D>& spot2);
bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Circle>& circle);
bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Line2D>& line);
bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Rectangle>& rectangle);

// CIRCLE
float DistanceSqr(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot);
float DistanceSqr(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2);
bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot);
bool Engulfs(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2);
bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Line2D>& line);
bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Rectangle>& rectangle);

// LINE
float DistanceSqr(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Spot2D>& spot);
float DistanceSqr(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle);
float DistanceSqr(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2);
bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Spot2D>& spot);
bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle);
bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Line2D>& line2);
bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Rectangle>& rectangle);

// RECTANGLE
float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot);
float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle);
float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line);
float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line);
bool Engulfs(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2);

// AABR - only against other AABBs for now as this is just used in oct trees for now
bool Intersect(const ShapeOrientation<AABR>& aabr1, const ShapeOrientation<AABR>& aabr2);
bool Engulfs(const ShapeOrientation<AABR>& aabr1, const ShapeOrientation<AABR>& aabr2);
} // namespace Geometric
} // namespace Core