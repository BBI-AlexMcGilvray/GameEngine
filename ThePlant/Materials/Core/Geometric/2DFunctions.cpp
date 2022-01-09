#pragma once

#include "Core/Geometric/2DFunctions.h"

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Math/Headers/VectorFunctions.h"
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

    ShapeOrientation<Point> circleCenter = { Point(), circle1.orientation };
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

    ShapeOrientation<Point> circleCenter = { Point(), circle.orientation };
    return std::min(0.0f, std::abs(Distance(line, circleCenter) - circle.shape.radius));
}

float Distance(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2)
{
    VERIFY_2D(line1);
    VERIFY_2D(line2);


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

    ShapeOrientation<Point> circleCenter = { Point(), circle.orientation };
    return std::min(0.0f, std::abs(Distance(rectangle, circleCenter) - circle.shape.radius));
}

float Distance(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    const Math::Float2 closestPoint = ClosestPointToLine(rectangle, line);
    return Distance(line, { Point2D(), Transform(Math::Float3(closestPoint)) });
}

float Distance(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2)
{
    VERIFY_2D(rectangle1);
    VERIFY_2D(rectangle2);
}
} // namespace Geometric
} // namespace Core