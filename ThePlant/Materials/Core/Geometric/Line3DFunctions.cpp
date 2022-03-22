#include "Core/Geometric/Line3DFunctions.h"

#include "Core/Debugging/Profiling/Utils.h"
#include "Core/Logging/LogFunctions.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
Math::Float3 EffectiveDirection(const ShapeOrientation<Line3D>& line)
{
    auto effectiveDirection = Math::RotateVectorBy(line.shape.line, line.orientation.rotation);
    return effectiveDirection * line.orientation.scale;
}

float LineMultiplierForPoint_X(const Line3D& line, const Point3D& point)
{
    if (point.X == 0.0f)
    {
        return 0.0f;
    }

    return point.X / line.line.X;
}

float LineMultiplierForPoint_Y(const Line3D& line, const Point3D& point)
{
    if (point.Y == 0.0f)
    {
        return 0.0f;
    }

    return point.Y / line.line.Y;
}

float LineMultiplierForPoint_Z(const Line3D& line, const Point3D& point)
{
    if (point.Z == 0.0f)
    {
        return 0.0f;
    }

    return point.Z / line.line.Z;
}

float AnyValidMultiplier(const Line3D& line, const Point3D& point)
{
    if (line.line.X != 0.0f)
    {
        return LineMultiplierForPoint_X(line, point);
    }
    if (line.line.Y != 0.0f)
    {
        return LineMultiplierForPoint_Y(line, point);
    }
    if (line.line.Z != 0.0f)
    {
        return LineMultiplierForPoint_Z(line, point);
    }
    CORE_THROW("Line3DFunctions", "Line has no valid multipliers, line == 0");
}

float LineMultiplierForPoint_X(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    return LineMultiplierForPoint_X(Line3D(EffectiveDirection(line), line.shape.infinite), point - line.orientation.position);
}

float LineMultiplierForPoint_Y(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    return LineMultiplierForPoint_Y(Line3D(EffectiveDirection(line), line.shape.infinite), point - line.orientation.position);
}

float LineMultiplierForPoint_Z(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    return LineMultiplierForPoint_Z(Line3D(EffectiveDirection(line), line.shape.infinite), point - line.orientation.position);
}

float AnyValidMultiplier(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    return AnyValidMultiplier(Line3D(EffectiveDirection(line), line.shape.infinite), point - line.orientation.position);
}

// overload to avoid calculating multipliers multiple times if known
bool PointIsOnLine(const float& xMultiplier, const float& yMultiplier, const float& zMultiplier, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    bool xyClose = std::abs(xMultiplier - yMultiplier) <= precision;
    bool yzClose = std::abs(yMultiplier - zMultiplier) <= precision;
    bool zxClose = std::abs(zMultiplier - xMultiplier) <= precision;
    return (xyClose && yzClose && zxClose);
}

bool PointIsOnLine(const Line3D& line, const Point3D& point, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    for (size_t dimension = 0; dimension < point.Dimensions(); ++dimension)
    {
        // check for divide by 0 case
        if (point[dimension] != 0.0f && line.line[dimension] == 0.0f)
        {
            return false;
        }
    }

    return PointIsOnLine(LineMultiplierForPoint_X(line, point), LineMultiplierForPoint_Y(line, point), LineMultiplierForPoint_Z(line, point), precision);
}

bool PointIsOnLine(const ShapeOrientation<Line3D>& line, const Point3D& point, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    return PointIsOnLine(Line3D(EffectiveDirection(line), line.shape.infinite), point - line.orientation.position);
}

Math::Float3 PointOnLine(const Line3D& line, const float& multiplier)
{
    // direction is normalied, so multiplier can't be larger than length
    auto minMultiplier = line.infinite ? multiplier : std::min(multiplier, 1.0f);
    if (minMultiplier < 0.0f) // point is 'behind' the line start
    {
        return 0.0f;
    }
    return (line.line * minMultiplier);
}

Math::Float3 PointOnLine(const ShapeOrientation<Line3D>& line, const float& multiplier)
{
    return line.orientation.position + PointOnLine(Line3D(EffectiveDirection(line), line.shape.infinite), multiplier);
}

Math::Float3 LineEndpoint(const Line3D& line)
{
    VERIFY(!line.infinite, "Infinite lines do not have endpoints");
    return PointOnLine(line, 1.0f);
}

Math::Float3 LineEndpoint(const ShapeOrientation<Line3D>& line)
{
    return line.orientation.position + LineEndpoint(Line3D(EffectiveDirection(line), line.shape.infinite));
}

Math::Float3 ClosestPointOnLine(const Line3D& line, const Point3D& point)
{
    const Math::Float3 projectedOntoLine = Math::Project(point, line.line);

    // we know this is on the line since we projected it onto the line
    const float lineMultiplier = AnyValidMultiplier(line, projectedOntoLine);
    return PointOnLine(line, lineMultiplier);
}

Math::Float3 ClosestPointOnLine(const ShapeOrientation<Line3D>& line, const Point3D& point)
{
    const Math::Float3 adjustedPoint = point - line.orientation.position;
    return line.orientation.position + ClosestPointOnLine(Line3D(EffectiveDirection(line), line.shape.infinite), adjustedPoint);
}

Math::Float3 ClosestPointOnLine(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot)
{
    return ClosestPointOnLine(line, spot.orientation.position);
}

std::pair<Core::Math::Float3, Core::Math::Float3> ClosestPointsBetweenLines(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    const auto l1Dir = EffectiveDirection(line1);
    const auto l2Dir = EffectiveDirection(line2);
    const auto o1ToO2 = line2.orientation.position - line1.orientation.position;
    const auto o2ToO1 = line1.orientation.position - line2.orientation.position;

    const auto l1Xl2 = Math::CrossProduct(l1Dir, l2Dir);
    if (Math::Max(l1Xl2, Core::Math::Float3(precision)) == Core::Math::Float3(precision)) // lines are parallel (enough)
    {
        if (Math::Dot(l1Dir, o1ToO2) > 0.0f) // o1-----e1 o2-----e2
        {
            return { ClosestPointOnLine(line1, ShapeOrientation<Spot3D>(line2.orientation, Spot3D())), line2.orientation.position };
        }
        return { line1.orientation.position, ClosestPointOnLine(line2, ShapeOrientation<Spot3D>(line1.orientation, Spot3D())) };
    }

    /*
    Notes:
        We are solving this by finding the two points on the line such that the line between those two points is perpendicular to the two lines
        Given L1 = O1 + d1 * V1, L2 = O2 + d2 * V2
        We need to find d1 and d2 such that:
            L3 = (O1 + d1 * V1) - (O2 + d2 * V2)
            Dot(L3, V1) = 0 and Dot(L3, V2) = 0 // solving these two equations gives us the below logic
            d1 = (1/Dot(V1, V1))[Dot(O2 - O1, V1) + d2 * Dot(V2, V1)]
            d2 = (1/Dot(V2, V2))[Dot(O1 - O2, V2) + d1 * Dot(V1, V2)]
    */

    const auto l1l2 = Math::Dot(l1Dir, l2Dir);
    const auto l1Dir_Sqr = Math::Dot(l1Dir, l1Dir);
    const auto l2Dir_Sqr = Math::Dot(l2Dir, l2Dir);

    const auto numer = l1Dir_Sqr * l2Dir_Sqr;
    const auto denom = (l1Dir_Sqr * l2Dir_Sqr) - Math::sqr(l1l2);
    const auto first = Math::Dot(o1ToO2, l1Dir) / l1Dir_Sqr;
    const auto second = (l1l2 / (l1Dir_Sqr * l2Dir_Sqr)) * Math::Dot(o2ToO1, l2Dir);

    // d1Denom is only 0 if the lines have the same direction (to make l1l2^2 == l1Dir_Sqr * l2Dir_Sqr), and that is handled above by checking if the lines are in the same direction

    float d1 = (numer / denom) * (first + second);
    float d2 =  (1.0f / l2Dir_Sqr) * (Math::Dot(o2ToO1, l2Dir) + (d1 * l1l2));

    return { PointOnLine(line1, d1), PointOnLine(line2, d2) };
}

ShapeOrientation<Line3D> LineFromPoints(const Point3D& point1, const Point3D& point2)
{
    // DEBUG_PROFILE_SCOPE("LineFromPoints");
    
    const auto point1To2 = point2 - point1;
    return ShapeOrientation<Line3D>(Orientation(point1), Line3D(point1To2, false));
}
} // namespace Geometric
} // namespace Core