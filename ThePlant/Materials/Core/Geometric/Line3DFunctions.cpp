#include "Core/Geometric/Line3DFunctions.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
Math::Float3 EffectiveDirection(const ShapeOrientation<Line3D>& line)
{
    return Math::RotateNormalVectorBy(line.shape.direction, line.orientation.GetRotation()) * line.orientation.GetScale();
}

float LineMultiplierForPoint_X(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    return (point.X - line.orientation.GetPosition().X) / EffectiveDirection(line).X;
}

float LineMultiplierForPoint_Y(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    return (point.Y - line.orientation.GetPosition().Y) / EffectiveDirection(line).Y;
}

float LineMultiplierForPoint_Z(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    return (point.Z - line.orientation.GetPosition().Z) / EffectiveDirection(line).Z;
}

// overload to avoid calculating multipliers multiple times if known
bool PointIsOnLine(const float& xMultiplier, const float& yMultiplier, const float& zMultiplier, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    bool xyClose = std::abs(xMultiplier - yMultiplier) <= precision;
    bool yzClose = std::abs(yMultiplier - zMultiplier) <= precision;
    bool zxClose = std::abs(zMultiplier - xMultiplier) <= precision;
    return (xyClose && yzClose && zxClose);
}

bool PointIsOnLine(const ShapeOrientation<Line3D>& line, Point3D& point, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    return PointIsOnLine(LineMultiplierForPoint_X(line, point), LineMultiplierForPoint_Y(line, point), LineMultiplierForPoint_Z(line, point), precision);
}

Math::Float3 PointOnLine(const ShapeOrientation<Line3D>& line, const float& multiplier)
{
    const Math::Float3 lineOrigin = line.orientation.GetPosition();

    // direction is normalied, so multiplier can't be larger than length
    auto minMultiplier = line.shape.infinite ? multiplier : std::min(multiplier, line.shape.length);
    if (minMultiplier < 0) // point is 'behind' the line start
    {
        return lineOrigin;
    }
    return lineOrigin + (EffectiveDirection(line) * minMultiplier);
}

Math::Float3 LineEndpoint(const ShapeOrientation<Line3D>& line)
{
    VERIFY(!line.shape.infinite, "Infinite lines do not have endpoints");
    return PointOnLine(line, line.shape.length);
}

Math::Float3 ClosestPointOnLine(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot)
{
    const Math::Float3 lineOrigin = line.orientation.GetPosition();
    const Math::Float3 spotOrigin = spot.orientation.GetPosition();

    const Math::Float3 originToSpot = spotOrigin - lineOrigin;
    const Math::Float3 projectedOntoLine = Math::Project(originToSpot, EffectiveDirection(line));
    const Math::Float3 closestPointOnLine = projectedOntoLine + lineOrigin;

    // we know this is on the line since we projected it onto the line
    const float lineMultiplier = LineMultiplierForPoint_X(line, closestPointOnLine);
    return PointOnLine(line, lineMultiplier);
}

std::pair<Core::Math::Float3, Core::Math::Float3> ClosestPointsBetweenLines(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    const auto l1Dir = EffectiveDirection(line1);
    const auto l2Dir = EffectiveDirection(line2);
    const auto o1ToO2 = line2.orientation.GetPosition() - line1.orientation.GetPosition();
    const auto o2ToO1 = line1.orientation.GetPosition() - line2.orientation.GetPosition();

    const auto l1Xl2 = Math::CrossProduct(l1Dir, l2Dir);
    if (Math::Max(l1Xl2, Core::Math::Float3(precision)) == Core::Math::Float3(precision)) // lines are parallel (enough)
    {
        if (Math::Dot(l1Dir, o1ToO2) > 0.0f) // o1-----e1 o2-----e2
        {
            return { ClosestPointOnLine(line1, ShapeOrientation<Spot3D>(line2.orientation, Spot3D())), line2.orientation.GetPosition() };
        }
        return { line1.orientation.GetPosition(), ClosestPointOnLine(line2, ShapeOrientation<Spot3D>(line1.orientation, Spot3D())) };
    }

    /*
    Notes:
        We are solving this by finding the two points on the line such that the line between those two points is perpendicular to the two lines
        Given L1 = O1 + d1 * V1, L2 = O2 + d2 * V2
        We need to find d1 and d2 such that:
            L3 = (O1 + d1 * V1) - (O2 + d2 * V2)
            Dot(L3, V1) = 0 and Dot(L3, V2) = 0 // solving these two equations gives us the below logic
    */

    const auto l1l2 = Math::Dot(l1Dir, l2Dir);
    const auto l1Dir_Sqr = Math::Dot(l1Dir, l1Dir);
    const auto l2Dir_Sqr = Math::Dot(l2Dir, l2Dir);

    const auto d1Denom = (l1Dir_Sqr * l2Dir_Sqr) - Math::sqr(l1l2);

    // d1Denom is only 0 if the lines have the same direction (to make l1l2^2 == l1Dir_Sqr * l2Dir_Sqr), and that is handled above by checking if the lines are in the same direction

    float d1 = ((Math::Dot(o1ToO2, l1Dir) / l1Dir_Sqr) - (Math::Dot(o1ToO2, l2Dir) * (l1l2 / l2Dir_Sqr))) * (l1Dir_Sqr * l2Dir_Sqr / d1Denom);
    float d2 = (Math::Dot(o1ToO2, l1Dir) - (d1 * l1l2)) / l2Dir_Sqr;

    return { PointOnLine(line1, d1), PointOnLine(line2, d2) };
}
} // namespace Geometric
} // namespace Core