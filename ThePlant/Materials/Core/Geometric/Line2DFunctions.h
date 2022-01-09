#pragma once

#include "Core/Geometric/GeometryDefs.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
Math::Float2 EffectiveDirection(const ShapeOrientation<Line2D>& line)
{
    return Math::RotateNormalVectorBy(line.shape.direction, line.orientation.GetRotation());
}

bool PointIsOnLine(const ShapeOrientation<Line2D>& line, Point2D& point, const float& precision = Math::DEFAULT_PRECISION())
{
    VERIFY_2D(line);

    return PointIsOnLine(LineMultiplierForPoint_X(line, point), LineMultiplierForPoint_Y(line, point), precision);
}

// overload to avoid calculating multipliers multiple times if known
bool PointIsOnLine(const float& xMultiplier, const float& yMultiplier, const float& precision = Math::DEFAULT_PRECISION())
{
    return std::abs(xMultiplier - yMultiplier) <= precision;
}

float LineMultiplierForPoint_X(const ShapeOrientation<Line2D>& line, const Point2D& point)
{
    VERIFY_2D(line);

    return (point.X - line.orientation.GetPosition().X) / EffectiveDirection(line).X;
}

float LineMultiplierForPoint_Y(const ShapeOrientation<Line2D>& line, const Point2D& point)
{
    VERIFY_2D(line);

    return (point.Y - line.orientation.GetPosition().Y) / EffectiveDirection(line).Y;
}

Math::Float2 PointOnLine(const ShapeOrientation<Line2D>& line, const float& multiplier)
{
    VERIFY_2D(line);

    const Math::Float2 lineOrigin = line.orientation.GetPosition().XY;

    // direction is normalied, so multiplier can't be larger than length
    auto minMultiplier = line.shape.infinite ? multiplier : std::min(multiplier, line.shape.length);
    if (minMultiplier < 0) // point is 'behind' the line start
    {
        return lineOrigin;
    }
    return lineOrigin + (line.shape.direction * minMultiplier);
}

Math::Float2 ClosestPointOnLine(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Point>& point)
{
    VERIFY_2D(line);
    VERIFY_2D(point);

    const Math::Float2 lineOrigin = line.orientation.GetPosition().XY;
    const Math::Float2 pointOrigin = point.orientation.GetPosition().XY;

    const Math::Float2 originToPoint = pointOrigin - lineOrigin;
    const auto projectedOntoLine = lineOrigin + Math::Project(originToPoint, EffectiveDirection(line));

    // we know this is on the line since we projected it onto the line
    const auto closestPointOnLine = lineOrigin + projectedOntoLine;

    const auto lineMultiplier = LineMultiplierForPoint_X(line, closestPointOnLine);
    return PointOnLine(line, lineMultiplier);
}
} // namespace Geometric
} // namespace Core