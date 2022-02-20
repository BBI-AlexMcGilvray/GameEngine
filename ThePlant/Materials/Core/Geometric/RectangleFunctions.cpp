#include "Core/Geometric/RectangleFunctions.h"

#include "Core/Geometric/2DFunctions.h"
#include "Core/Geometric/Transform.h"
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

    Point2D modifiedPoint = Math::RotateVectorBy(Math::Float3(point, 0.0f), rectangle.orientation.rotation.Inverse()) - rectangle.orientation.position;
    return PointInRectangle(rectangle.shape, modifiedPoint);
}

// assumes rectangle is centered on (0,0)
Math::Float2 LastPointOnRectangleInDirection(const Rectangle& rectangle, const Math::Float2& direction)
{
    CORE_THROW("RectangleFunction", "This is wrong, we don't take into account negative multipliers properly");

    const Math::Float2 topRight = RectangleMaxCenteredAt0(rectangle);
    const Math::Float2 bottomLeft = RectangleMinCenteredAt0(rectangle);

    ShapeOrientation<Line2D> line = { Orientation(), Line2D(direction, true) };

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

    const Math::Float2 effectiveDirection = Math::RotateVectorBy(direction, rectangle.orientation.rotation.Inverse());
    
    const auto effectiveLastPoint = LastPointOnRectangleInDirection(rectangle.shape, effectiveDirection);
    return rectangle.orientation.position.XY + Math::RotateVectorBy(effectiveLastPoint, rectangle.orientation.rotation);
}

Math::Float2 ClosestPointToPoint(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(spot);

    // offset the point by the inverse of the rectangle so calculation is simpler
    const Math::Float2 modifiedPoint = Math::RotateVectorBy(spot.orientation.position, rectangle.orientation.rotation.Inverse()).XY - rectangle.orientation.position.XY;
    if (PointInRectangle(rectangle.shape, modifiedPoint))
    { // point is INSIDE the rectangle
        return modifiedPoint;
    }

    // our modified point is relative to (0,0), so we can use it as the direction
    return LastPointOnRectangleInDirection(rectangle, spot.orientation.position - rectangle.orientation.position);
}

Math::Float2 ClosestPointToLine(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    const auto& rectMax = RectangleMaxCenteredAt0(rectangle.shape);
    const auto& rectMin = RectangleMinCenteredAt0(rectangle.shape);

    // offset the point by the inverse of the rectangle so calculation is simpler
    ShapeOrientation<Line2D> modifiedLine = line;
    modifiedLine.orientation.position += rectangle.orientation.position * -1.0f;
    modifiedLine.orientation.rotation = rectangle.orientation.rotation.Inverse() * modifiedLine.orientation.rotation;

    // if we touch the box, we either go through the sides, have every point IN the box, or all points are out of the box
    const auto xMultiplier_TopRight = LineMultiplierForPoint_X(modifiedLine, rectMax);
    Math::Float2 pointOnLine_Right = PointOnLine(modifiedLine, xMultiplier_TopRight);
    if (PointInRectangle(rectangle.shape, pointOnLine_Right)) // goes through right side
    {
        return pointOnLine_Right;
    }

    const auto yMultiplier_TopRight = LineMultiplierForPoint_Y(modifiedLine, rectMax);
    Math::Float2 pointOnLine_Top = PointOnLine(modifiedLine, yMultiplier_TopRight);
    if (PointInRectangle(rectangle.shape, pointOnLine_Top)) // goes through top
    {
        return pointOnLine_Top;
    }

    const auto xMultiplier_BottomLeft = LineMultiplierForPoint_X(modifiedLine, rectMin);
    Math::Float2 pointOnLine_Left = PointOnLine(modifiedLine, xMultiplier_BottomLeft);
    if (PointInRectangle(rectangle.shape, pointOnLine_Left)) // goes through left
    {
        return pointOnLine_Left;
    }

    const auto yMutliplier_BottomLeft = LineMultiplierForPoint_Y(modifiedLine, rectMin);
    Math::Float2 pointOnLine_Bottom = PointOnLine(modifiedLine, yMutliplier_BottomLeft);
    if (PointInRectangle(rectangle.shape, pointOnLine_Bottom)) // goes through bottom
    {
        return pointOnLine_Bottom;
    }

    if (PointInRectangle(rectangle.shape, modifiedLine.orientation.position)) // line is in rectangle
    {
        return modifiedLine.orientation.position;
    }

    ShapeOrientation<Line2D> topEdge(Orientation(Math::Float3(rectMin.X, rectMax.Y, 0.0f)), Line2D(Math::Float2(1.0f, 0.0f), true));
    ShapeOrientation<Line2D> bottomdge(Orientation(Math::Float3(rectMin.X, rectMin.Y, 0.0f)), Line2D(Math::Float2(1.0f, 0.0f), true));
    ShapeOrientation<Line2D> leftEdge(Orientation(Math::Float3(rectMin.X, rectMin.Y, 0.0f)), Line2D(Math::Float2(0.0f, 1.0f), true));
    ShapeOrientation<Line2D> rightEdge(Orientation(Math::Float3(rectMax.X, rectMin.Y, 0.0f)), Line2D(Math::Float2(0.0f, 1.0f), true));
    const auto topEdgeDistance = DistanceSqr(modifiedLine, topEdge);
    const auto bottomEdgeDistance = DistanceSqr(modifiedLine, bottomdge);
    const auto leftEdgeDistance = DistanceSqr(modifiedLine, leftEdge);
    const auto rightEdgeDistance = DistanceSqr(modifiedLine, rightEdge);

    auto smallestDistance = [topEdgeDistance, bottomEdgeDistance, leftEdgeDistance, rightEdgeDistance](const auto& distance)
    {
        return (distance <= topEdgeDistance && distance <= bottomEdgeDistance && distance <= leftEdgeDistance && distance <= rightEdgeDistance);
    };

    if (smallestDistance(topEdgeDistance))
    {
        return topEdgeDistance;
    }
    else if (smallestDistance(bottomEdgeDistance))
    {
        return bottomEdgeDistance;
    }
    else if (smallestDistance(leftEdgeDistance))
    {
        return leftEdgeDistance;
    }
    else // smallestDistance(rightEdgeDistance)
    {
        return rightEdgeDistance;
    }
}
} // namespace Geometric
} // namespace Core