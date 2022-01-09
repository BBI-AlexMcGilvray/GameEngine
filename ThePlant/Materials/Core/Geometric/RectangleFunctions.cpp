#include "Core/Geometric/RectangleFunctions.h"

#include "Core/Geometric/2DFunctions.h"

namespace Core {
namespace Geometric {
Math::Float2 ClosestPointToLine(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    const auto& rectMax = RectangleMaxCenteredAt0(rectangle.shape);
    const auto& rectMin = RectangleMinCenteredAt0(rectangle.shape);

    // offset the point by the inverse of the rectangle so calculation is simpler
    ShapeOrientation<Line2D> modifiedLine = line;
    modifiedLine.orientation.AdjustPosition(rectangle.orientation.GetPosition() * -1.0f);
    modifiedLine.orientation.AdjustRotation(rectangle.orientation.GetRotation().Inverse());

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

    if (PointInRectangle(rectangle.shape, modifiedLine.orientation.GetPosition())) // line is in rectangle
    {
        return modifiedLine.orientation.GetPosition();
    }

    ShapeOrientation<Line2D> topEdge = { Line2D(Math::Float2(1.0f, 0.0f)), Transform(Math::Float2(rectMin.X, rectMax.Y)) };
    ShapeOrientation<Line2D> bottomdge = { Line2D(Math::Float2(1.0f, 0.0f)), Transform(Math::Float2(rectMin.X, rectMin.Y)) };
    ShapeOrientation<Line2D> leftEdge = { Line2D(Math::Float2(0.0f, 1.0f)), Transform(Math::Float2(rectMin.X, rectMin.Y)) };
    ShapeOrientation<Line2D> rightEdge = { Line2D(Math::Float2(0.0f, 1.0f)), Transform(Math::Float2(rectMax.X, rectMin.Y)) };
    const auto topEdgeDistance = Distance(modifiedLine, topEdge);
    const auto bottomEdgeDistance = Distance(modifiedLine, bottomdge);
    const auto leftEdgeDistance = Distance(modifiedLine, leftEdge);
    const auto rightEdgeDistance = Distance(modifiedLine, rightEdge);

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