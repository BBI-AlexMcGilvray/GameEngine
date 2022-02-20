#include "Core/Geometric/Line2DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
Math::Float2 EffectiveDirection(const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(line);
    
    return Math::RotateVectorBy(line.shape.line, line.orientation.rotation) * line.orientation.scale.XY;
}

float LineMultiplierForPoint_X(const ShapeOrientation<Line2D>& line, const Point2D& point)
{
    VERIFY_2D(line);

    return (point.X - line.orientation.position.X) / EffectiveDirection(line).X;
}

float LineMultiplierForPoint_Y(const ShapeOrientation<Line2D>& line, const Point2D& point)
{
    VERIFY_2D(line);

    return (point.Y - line.orientation.position.Y) / EffectiveDirection(line).Y;
}

// overload to avoid calculating multipliers multiple times if known
bool PointIsOnLine(const float& xMultiplier, const float& yMultiplier, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    return std::abs(xMultiplier - yMultiplier) <= precision;
}

bool PointIsOnLine(const ShapeOrientation<Line2D>& line, Point2D& point, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    VERIFY_2D(line);

    return PointIsOnLine(LineMultiplierForPoint_X(line, point), LineMultiplierForPoint_Y(line, point), precision);
}

Math::Float2 PointOnLine(const ShapeOrientation<Line2D>& line, const float& multiplier)
{
    VERIFY_2D(line);

    const Math::Float2 lineOrigin = line.orientation.position.XY;

    // direction is normalied, so multiplier can't be larger than length
    auto minMultiplier = line.shape.infinite ? multiplier : std::min(multiplier, 1.0f);
    if (minMultiplier < 0.0f) // point is 'behind' the line start
    {
        return lineOrigin;
    }
    return lineOrigin + (EffectiveDirection(line) * minMultiplier);
}

Math::Float2 LineEndpoint(const ShapeOrientation<Line2D>& line)
{
    VERIFY(!line.shape.infinite, "Infinite lines do not have endpoints");
    return PointOnLine(line, 1.0f);
}

Math::Float2 ClosestPointOnLine(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(line);
    VERIFY_2D(spot);

    const Math::Float2 lineOrigin = line.orientation.position.XY;
    const Math::Float2 spotOrigin = spot.orientation.position.XY;

    const Math::Float2 originToSpot = spotOrigin - lineOrigin;
    const auto projectedOntoLine = lineOrigin + Math::Project(originToSpot, EffectiveDirection(line));

    // we know this is on the line since we projected it onto the line
    const auto closestPointOnLine = lineOrigin + projectedOntoLine;

    const auto lineMultiplier = LineMultiplierForPoint_X(line, closestPointOnLine);
    return PointOnLine(line, lineMultiplier);
}
} // namespace Geometric
} // namespace Core