#pragma once

#include "Core/Geometric/GeometryDefs.h"
#include "Core/Geometric/Line2DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
// rectangles have origin at (0,0)
Math::Float2 RectangleMaxCenteredAt0(const Rectangle& rectangle)
{
    return rectangle.dimensions * 0.5f;
}

// rectangles have origin at (0,0)
Math::Float2 RectangleMinCenteredAt0(const Rectangle& rectangle)
{
    return RectangleMaxCenteredAt0(rectangle) * -1.0f;
}

// assumes rectangle has origin at (0,0)
bool PointInRectangle(const Rectangle& rectangle, const Point2D& point)
{
    return Math::Max(Math::Min(point, RectangleMaxCenteredAt0(rectangle)), RectangleMinCenteredAt0(rectangle)) == point;
}

bool PointInRectangle(const ShapeOrientation<Rectangle>& rectangle, const Point2D& point)
{
    VERIFY_2D(rectangle);

    Point2D modifiedPoint = Math::RotateVectorBy(point, rectangle.orientation.GetRotation().Inverse()) - rectangle.orientation.GetPosition();
    return PointInRectangle(rectangle.shape, modifiedPoint);
}

// assumes rectangle is centered on (0,0)
Math::Float2 LastPointOnRectangleInDirection(const Rectangle& rectangle, const Math::Float2& direction)
{
    const Math::Float2 topRight = RectangleMaxCenteredAt0(rectangle);
    const Math::Float2 bottomLeft = RectangleMinCenteredAt0(rectangle);

    ShapeOrientation<Line2D> line = { Transform(), Line2D(direction) };

    // closest side is the one with the smalled multiplier, we find that then calculate the point on the line
    const auto leftMultiplier = LineMultiplierForPoint_X(line, bottomLeft);
    const auto bottomMultiplier = LineMultiplierForPoint_Y(line, bottomLeft);
    const auto rightMultiplier = LineMultiplierForPoint_X(line, topRight);
    const auto topMultiplier = LineMultiplierForPoint_Y(line, topRight);

    auto isSmallest = [leftMultiplier, bottomMultiplier, rightMultiplier, topMultiplier](const auto& value)
    {
        return (value <= leftMultiplier && value <= bottomMultiplier && value <= rightMultiplier && value <= topMultiplier);
    };

    if (isSmallest(leftMultiplier))
    {
        return PointOnLine(line, leftMultiplier);
    }
    else if (isSmallest(bottomMultiplier))
    {
        return PointOnLine(line, bottomMultiplier);
    }
    else if (isSmallest(rightMultiplier))
    {
        return PointOnLine(line, rightMultiplier);
    }
    else // isSmallest(topMultiplier)
    {
        return PointOnLine(line, topMultiplier);
    }
}

Math::Float2 LastPointOnRectangleInDirection(const ShapeOrientation<Rectangle>& rectangle, const Math::Float2& direction)
{
    VERIFY_2D(rectangle);

    const Math::Float2 effectiveDirection = Math::RotateVectorBy(direction, rectangle.orientation.GetRotation().Inverse());
    
    const auto effectiveLastPoint = LastPointOnRectangleInDirection(rectangle.shape, effectiveDirection);
    return rectangle.orientation.GetPosition().XY + Math::RotateVectorBy(effectiveLastPoint, rectangle.orientation.GetRotation());
}

Math::Float2 ClosestPointToPoint(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Point>& point, const float& precision = Math::DEFAULT_PRECISION())
{
    VERIFY_2D(rectangle);
    VERIFY_2D(point);

    // offset the point by the inverse of the rectangle so calculation is simpler
    const Math::Float2 modifiedPoint = Math::RotateVectorBy(point.orientation.GetPosition(), rectangle.orientation.GetRotation().Inverse()).XY - rectangle.orientation.GetPosition().XY;
    if (PointInRectangle(rectangle.shape, modifiedPoint))
    { // point is INSIDE the rectangle
        return modifiedPoint;
    }

    // our modified point is relative to (0,0), so we can use it as the direction
    return LastPointOnRectangleInDirection(rectangle, point.orientation.GetPosition() - rectangle.orientation.GetPosition());
}

// probably not the most efficient, but can deal with that later
Math::Float2 ClosestPointToLine(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line, const float& precision = Math::DEFAULT_PRECISION());
} // namespace Geometric
} // namespace Core