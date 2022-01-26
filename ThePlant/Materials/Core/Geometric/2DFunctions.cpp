#pragma once

#include "Core/Geometric/2DFunctions.h"

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"
#include "Core/Geometric/Line2DFunctions.h"
#include "Core/Geometric/RectangleFunctions.h"

namespace Core {
namespace Geometric {
float Distance(const ShapeOrientation<Spot2D>& spot1, const ShapeOrientation<Spot2D>& spot2)
{
    VERIFY_2D(spot1);
    VERIFY_2D(spot2);
    
    return Math::Distance(spot1.orientation.GetPosition(), spot2.orientation.GetPosition());
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot1, const ShapeOrientation<Spot2D>& spot2)
{
    VERIFY_2D(spot1);
    VERIFY_2D(spot2);
    
    return spot1.orientation == spot2.orientation;
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Circle>& circle2)
{
    VERIFY_2D(spot);
    VERIFY_2D(circle2);

    // do we care about case where spot == circle.origin && circle.length = 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(spot);
    VERIFY_2D(line);

    // do we care about case where spot == line.origin && line.length = 0?
    return false;
}

bool Engulfs(const ShapeOrientation<Spot2D>& spot, const ShapeOrientation<Rectangle>& rectangle)
{
    VERIFY_2D(spot);
    VERIFY_2D(rectangle);

    // do we care about case where spot == rectangle.origin && rectangle.dimensions = 0?
    return false;
}

float Distance(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(circle);
    VERIFY_2D(spot);

    float spotToCenterSqr = Math::DistanceSqr(circle.orientation.GetPosition(), spot.orientation.GetPosition());

    return std::max(0.0f, spotToCenterSqr - Math::sqr(circle.shape.radius));
}

float Distance(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2)
{
    VERIFY_2D(circle1);
    VERIFY_2D(circle2);

    ShapeOrientation<Spot2D> circleCenter = { circle1.orientation, Spot2D() };
    return std::max(0.0f, Distance(circle2, circleCenter) - circle1.shape.radius);
}

bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(circle);
    VERIFY_2D(spot);

    return Distance(circle, spot) <= 0.0f;
}

bool Engulfs(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2)
{
    VERIFY_2D(circle1);
    VERIFY_2D(circle2);

    return (std::abs(Distance(circle1, ShapeOrientation<Spot2D>(circle2.orientation, Spot2D()))) + circle2.shape.radius) <= circle1.shape.radius;
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

    Transform lineEndOrientation = line.orientation;
    lineEndOrientation.SetPosition(Math::Float3(LineEndpoint(line), 0.0f));
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

float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(line);
    VERIFY_2D(spot);

    Math::Float2 closestPointOnLine = ClosestPointOnLine(line, spot);
    return Math::Distance(spot.orientation.GetPosition().XY, closestPointOnLine);
}

float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(line);
    VERIFY_2D(circle);

    ShapeOrientation<Spot2D> circleCenter = { circle.orientation, Spot2D() };
    return std::max(0.0f, Distance(line, circleCenter) - circle.shape.radius);
}

float Distance(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2)
{
    VERIFY_2D(line1);
    VERIFY_2D(line2);

    ShapeOrientation<Line2D> modifiedLine2 = line2;
    modifiedLine2.orientation.AdjustPosition(line1.orientation.GetPosition());
    modifiedLine2.orientation.AdjustRotation(line1.orientation.GetRotation().Inverse());

    const auto modifiedLine2EffectiveDirection = EffectiveDirection(modifiedLine2);
    bool linesParallel = (std::abs(Math::DistanceSqr(line1.shape.direction, modifiedLine2EffectiveDirection)) <= Math::DEFAULT_PRECISION());
    if (linesParallel)
    {
        // if line1 points to line2, use ClosestPointOnLine(line1, line2.origin)
        // if line2 points to line1, use ClosestPointOnLine(line2, line1.oirign)
        // otherwise return distance between origins
    }

    // lines are guaranteed to intersect, calculate where then calculate closest point on each line to that point
    // then give distance between the closest points on each line
    CORE_ERROR("2DFunctions", "Incomplete Implementation");
    return 1.0f;
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

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(spot);

    const Math::Float2 closestPointInRectangle = ClosestPointToPoint(rectangle, spot);
    if (PointInRectangle(rectangle, closestPointInRectangle))
    {
        return 0.0f;
    }

    return Math::Distance(spot.orientation.GetPosition().XY, closestPointInRectangle);
}

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(circle);

    ShapeOrientation<Spot2D> circleCenter = { circle.orientation, Spot2D() };
    return std::max(0.0f, Distance(rectangle, circleCenter) - circle.shape.radius);
}

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    const Math::Float2 closestPoint = ClosestPointToLine(rectangle, line);
    return Distance(line, { Transform(Math::Float3(closestPoint)), Spot2D() });
}

float Distance(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2)
{
    VERIFY_2D(rectangle1);
    VERIFY_2D(rectangle2);

    return 1.0f;
}

bool Engulfs(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(spot);

    return PointInRectangle(rectangle, spot.orientation.GetPosition());
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

    Transform lineEndOrientation = line.orientation;
    lineEndOrientation.SetPosition(Math::Float3(LineEndpoint(line), 0.0f));
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
} // namespace Geometric
} // namespace Core