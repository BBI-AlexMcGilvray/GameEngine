#include "Core/Geometric/2DFunctions.h"

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Logging/LogFunctions.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Geometric/AABRFunctions.h"
#include "Core/Geometric/CircleFunctions.h"
#include "Core/Geometric/Line2DFunctions.h"
#include "Core/Geometric/RectangleFunctions.h"

namespace Core {
namespace Geometric {
std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Spot2D>& spot1, const ShapeOrientation<Spot2D>& spot2)
{
    VERIFY_2D(spot1);
    VERIFY_2D(spot2);
    
    return { spot1.orientation.position, spot2.orientation.position };
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot1, const ShapeOrientation<Spot2D>& spot2)
{
    VERIFY_2D(spot1);
    VERIFY_2D(spot2);
    
    return spot1.orientation.position == spot2.orientation.position;
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(spot);
    VERIFY_2D(circle);

    if (circle.shape.radius != 0.0f)
    {
        return false;
    }

    return spot.orientation.position == circle.orientation.position;
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(spot);
    VERIFY_2D(line);

    if (line.shape.infinite || line.shape.line != Core::Math::Float2(0.0f))
    {
        return false;
    }
    
    return spot.orientation.position == line.orientation.position;
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Rectangle>& rectangle)
{
    VERIFY_2D(spot);
    VERIFY_2D(rectangle);

    if (rectangle.shape.dimensions != Core::Math::Float2(0.0f))
    {
        return false;
    }
    
    return spot.orientation.position == rectangle.orientation.position;
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(circle);
    VERIFY_2D(spot);

    const auto circleToSpot = spot.orientation.position - circle.orientation.position;
    const auto circleToSpotMagnitudeSqr = Math::MagnitudeSqr(circleToSpot);
    
    Point3D closestSpotInCircle = circle.orientation.position + circleToSpot;
    if (circleToSpotMagnitudeSqr > Math::sqr(circle.shape.radius))
    {
        closestSpotInCircle = circle.orientation.position + (circleToSpot * std::sqrt(Math::sqr(circle.shape.radius) / circleToSpotMagnitudeSqr));
    }

    return { closestSpotInCircle, spot.orientation.position };
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2)
{
    VERIFY_2D(circle1);
    VERIFY_2D(circle2);

    const auto middlePoint = (circle1.orientation.position + circle2.orientation.position) * 0.5f;

    // the below should be a utility method
    const auto circle1ToMiddle = middlePoint - circle1.orientation.position;
    const auto circle1ToSpotMagnitudeSqr = Math::MagnitudeSqr(circle1ToMiddle);
    
    Point3D closestSpotInCircle1 = circle1.orientation.position + circle1ToMiddle;
    if (circle1ToSpotMagnitudeSqr > Math::sqr(circle1.shape.radius))
    {
        closestSpotInCircle1 = circle1.orientation.position + (circle1ToMiddle * std::sqrt(Math::sqr(circle1.shape.radius) / circle1ToSpotMagnitudeSqr));
    }

    // the below should be a utility method
    const auto circle2ToMiddle = middlePoint - circle2.orientation.position;
    const auto circle2ToSpotMagnitudeSqr = Math::MagnitudeSqr(circle2ToMiddle);
    
    Point3D closestSpotInCircle2 = circle2.orientation.position + circle2ToMiddle;
    if (circle2ToSpotMagnitudeSqr > Math::sqr(circle2.shape.radius))
    {
        closestSpotInCircle2 = circle2.orientation.position + (circle2ToMiddle * std::sqrt(Math::sqr(circle2.shape.radius) / circle2ToSpotMagnitudeSqr));
    }

    return { closestSpotInCircle1, closestSpotInCircle2 };
}

bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(circle);
    VERIFY_2D(spot);

    const auto closestPoints = ClosestPoints(circle, spot);

    return Math::DistanceSqr(closestPoints.first, closestPoints.second) <= 0.0f;
}

bool Engulfs(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2)
{
    VERIFY_2D(circle1);
    VERIFY_2D(circle2);

    // can't contain if the circle wouldn't even fit
    if (circle1.shape.radius < circle2.shape.radius)
    {
        return false;
    }

    const auto closestPoints = ClosestPoints(circle1, circle2);

    return Math::DistanceSqr(closestPoints.first, closestPoints.second) <= 0.0f;
}

bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(circle);
    VERIFY_2D(line);

    if (line.shape.infinite)
    {
        return false;
    }

    bool engulfsLineOrigin = Engulfs(circle, ShapeOrientation<Spot2D>(line.orientation, Spot2D()));

    Orientation lineEndOrientation = line.orientation;
    lineEndOrientation.position = Math::Float3(LineEndpoint(line), 0.0f);
    bool engulfsLineEnd = Engulfs(circle, ShapeOrientation<Spot2D>(lineEndOrientation, Spot2D()));
    return (engulfsLineOrigin && engulfsLineEnd);
}

bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Rectangle>& rectangle)
{
    VERIFY_2D(circle);
    VERIFY_2D(rectangle);

    CORE_THROW("2DFunctions", "Implementation Missing");
    return false;
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(line);
    VERIFY_2D(spot);

    Math::Float2 closestPointOnLine = ClosestPointOnLine(line, spot);

    return { closestPointOnLine, spot.orientation.position };
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(line);
    VERIFY_2D(circle);

    Math::Float2 closestPointOnLine = ClosestPointOnLine(line, ShapeOrientation<Spot2D>(circle.orientation, Spot2D()));
    return ClosestPoints(circle, ShapeOrientation<Spot2D>(Orientation(closestPointOnLine), Spot2D()));
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2)
{
    VERIFY_2D(line1);
    VERIFY_2D(line2);

    ShapeOrientation<Line2D> modifiedLine2 = line2;
    modifiedLine2.orientation.position += line1.orientation.position;
    modifiedLine2.orientation.rotation = line1.orientation.rotation.Inverse() * modifiedLine2.orientation.rotation;

    const auto modifiedLine2EffectiveDirection = EffectiveDirection(modifiedLine2);
    bool linesParallel = (line1.shape.line == modifiedLine2EffectiveDirection);
    if (linesParallel)
    {
        // if line1 points to line2, use ClosestPointOnLine(line1, line2.origin)
        // if line2 points to line1, use ClosestPointOnLine(line2, line1.oirign)
        // otherwise return distance between origins
    }

    // lines are guaranteed to intersect, calculate where then calculate closest point on each line to that point
    // then give distance between the closest points on each line
    CORE_ERROR("2DFunctions", "Incomplete Implementation");
    return { line1.orientation.position, line2.orientation.position };
}

bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(line);
    VERIFY_2D(spot);

    // do we care about case where spot is on line?
    return false;
}

bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(line);
    VERIFY_2D(circle);

    // do we care about case where circle.origin in on line && circle.radius = 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2)
{
    VERIFY_2D(line1);
    VERIFY_2D(line2);

    // do we care about case where line2 is on line2?
    return false;
}

bool Engulfs(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Rectangle>& rectangle)
{
    VERIFY_2D(line);
    VERIFY_2D(rectangle);

    // do we care about case where rectangle.origin is on line && rectangle.dimensions = 0?
    return false;
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(spot);

    const Math::Float2 closestPointInRectangle = ClosestPointToPoint(rectangle, spot);
    if (PointInRectangle(rectangle, closestPointInRectangle))
    {
        return { spot.orientation.position, spot.orientation.position };
    }

    return { closestPointInRectangle, closestPointInRectangle };
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(circle);

    const auto closestPointToCircle = ClosestPointToPoint(rectangle, ShapeOrientation<Spot2D>(circle.orientation, Spot2D()));
    return ClosestPoints(circle, ShapeOrientation<Spot2D>(Orientation(closestPointToCircle), Spot2D()));
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    const Math::Float2 closestPoint = ClosestPointToLine(rectangle, line);
    return ClosestPoints(line, { Orientation(Math::Float3(closestPoint)), Spot2D() });
}

std::pair<Point3D, Point3D> ClosestPoints(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2)
{
    VERIFY_2D(rectangle1);
    VERIFY_2D(rectangle2);

    CORE_ERROR("2DFunctions", "Incomplete Implementation");

    return { rectangle1.orientation.position, rectangle2.orientation.position };
}

bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(spot);

    return PointInRectangle(rectangle, spot.orientation.position);
}

bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(circle);

    // get vectors from circle origin to all 3 rect sides
    // using the sides that are POSITIVE when dotted with the vector from rect origin to circle origin
    //      check the farthest points on circle to see if they are still in rectangle
    //  ** if the circle origin == rect origin, pick 2 sides that are perpendicular to each other
    CORE_ERROR("2DFunctions", "Implementation Missing");
    return false;
}

bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    if (line.shape.infinite)
    {
        return false;
    }

    bool engulfsLineOrigin = Engulfs(rectangle, ShapeOrientation<Spot2D>(line.orientation, Spot2D()));

    Orientation lineEndOrientation = line.orientation;
    lineEndOrientation.position = Math::Float3(LineEndpoint(line), 0.0f);
    bool engulfsLineEnd = Engulfs(rectangle, ShapeOrientation<Spot2D>(lineEndOrientation, Spot2D()));
    return (engulfsLineOrigin && engulfsLineEnd);
}

bool Engulfs(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2)
{
    VERIFY_2D(rectangle1);
    VERIFY_2D(rectangle2);

    // check that all 4 corners of rect 2 and in rect 1
    CORE_ERROR("2DFunctions", "Implementation Missing");
    return false;
}

Intersection Intersect(const ShapeOrientation<AABR>& aabr1, const ShapeOrientation<AABR>& aabr2)
{
    std::pair<Math::Float2, Math::Float2> aabr1Extremes = AABRMinMax(aabr1);
    std::pair<Math::Float2, Math::Float2> aabr2Extremes = AABRMinMax(aabr2);

    const bool xIntersect = (aabr1.shape.infinite.X || aabr2.shape.infinite.X) || (aabr1Extremes.first.X <= aabr2Extremes.second.X && aabr1Extremes.second.X >= aabr2Extremes.first.X);
    const float xValue = std::max(std::min((aabr2Extremes.second.X + aabr1Extremes.first.X) * 0.5f, aabr1Extremes.second.X), aabr2Extremes.first.X);

    const bool yIntersect = (aabr1.shape.infinite.Y || aabr2.shape.infinite.Y) || (aabr1Extremes.first.Y <= aabr2Extremes.second.Y && aabr1Extremes.second.Y >= aabr2Extremes.first.Y);
    const float yValue = std::max(std::min((aabr2Extremes.second.Y + aabr1Extremes.first.Y) * 0.5f, aabr1Extremes.second.Y), aabr2Extremes.first.Y);

    return Intersection(xIntersect && yIntersect, Point3D(xValue, yValue, 0.0f));
}

bool Engulfs(const ShapeOrientation<AABR>& aabr1, const ShapeOrientation<AABR>& aabr2)
{
    const auto& infinites1 = aabr1.shape.infinite;
    const auto& infinites2 = aabr2.shape.infinite;
    // if aabb2 is infinite where aabb1 is not, no way aabb1 can engulf it
    if ((infinites2.X && !infinites1.X) || (infinites2.Y && !infinites1.Y))
    {
        return false;
    }

    std::pair<Math::Float3, Math::Float3> aabr1Extremes = AABRMinMax(aabr1);
    std::pair<Math::Float3, Math::Float3> aabr2Extremes = AABRMinMax(aabr2);

    return (aabr2Extremes.first.X >= aabr1Extremes.first.X && aabr2Extremes.second.X <= aabr1Extremes.second.X) &&
            (aabr2Extremes.first.Y >= aabr1Extremes.first.Y && aabr2Extremes.second.Y <= aabr1Extremes.second.Y);
}
} // namespace Geometric
} // namespace Core