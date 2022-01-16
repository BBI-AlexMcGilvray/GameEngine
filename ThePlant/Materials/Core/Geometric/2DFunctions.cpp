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
float Distance(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Point>& point)
{
    VERIFY_2D(circle);
    VERIFY_2D(point);

    float pointToCenterSqr = Math::DistanceSqr(circle.orientation.GetPosition(), point.orientation.GetPosition());

    return std::min(0.0f, std::abs(pointToCenterSqr - Math::sqr(circle.shape.radius)));
}

float Distance(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2)
{
    VERIFY_2D(circle1);
    VERIFY_2D(circle2);

    ShapeOrientation<Point> circleCenter = { circle1.orientation, Point() };
    return std::min(0.0f, Distance(circle2, circleCenter) - circle1.shape.radius);
}

float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Point>& point)
{
    VERIFY_2D(line);
    VERIFY_2D(point);

    Math::Float2 closestPointOnLine = ClosestPointOnLine(line, point);
    return Math::Distance(point.orientation.GetPosition().XY, closestPointOnLine);
}

float Distance(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(line);
    VERIFY_2D(circle);

    ShapeOrientation<Point> circleCenter = { circle.orientation, Point() };
    return std::min(0.0f, std::abs(Distance(line, circleCenter) - circle.shape.radius));
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
}

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Point>& point)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(point);

    const Math::Float2 closestPointInRectangle = ClosestPointToPoint(rectangle, point);
    if (PointInRectangle(rectangle, closestPointInRectangle))
    {
        return 0.0f;
    }

    return Math::Distance(point.orientation.GetPosition().XY, closestPointInRectangle);
}

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(circle);

    ShapeOrientation<Point> circleCenter = { circle.orientation, Point() };
    return std::min(0.0f, std::abs(Distance(rectangle, circleCenter) - circle.shape.radius));
}

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    const Math::Float2 closestPoint = ClosestPointToLine(rectangle, line);
    return Distance(line, { Transform(Math::Float3(closestPoint)), Point() });
}

float Distance(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2)
{
    VERIFY_2D(rectangle1);
    VERIFY_2D(rectangle2);
}
} // namespace Geometric
} // namespace Core