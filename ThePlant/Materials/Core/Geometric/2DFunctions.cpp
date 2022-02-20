#include "Core/Geometric/2DFunctions.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Geometric/CircleFunctions.h"
#include "Core/Geometric/Line2DFunctions.h"
#include "Core/Geometric/RectangleFunctions.h"

namespace Core {
namespace Geometric {
float DistanceSqr(const ShapeOrientation<Spot2D>& spot1, const ShapeOrientation<Spot2D>& spot2)
{
    VERIFY_2D(spot1);
    VERIFY_2D(spot2);
    
    return Math::DistanceSqr(spot1.orientation.position, spot2.orientation.position);
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

float DistanceSqr(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(circle);
    VERIFY_2D(spot);

    float spotToCenterSqr = Math::DistanceSqr(circle.orientation.position, spot.orientation.position);

    return spotToCenterSqr - Math::sqr(circle.shape.radius);
}

float DistanceSqr(const ShapeOrientation<Circle>& circle1, const ShapeOrientation<Circle>& circle2)
{
    VERIFY_2D(circle1);
    VERIFY_2D(circle2);

    ShapeOrientation<Spot2D> circleCenter = { circle1.orientation, Spot2D() };
    return DistanceSqr(circle2, circleCenter) - Math::sqr(circle1.shape.radius);
}

bool Engulfs(const ShapeOrientation<Circle>& circle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(circle);
    VERIFY_2D(spot);

    return DistanceSqr(circle, spot) <= 0.0f;
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

    return DistanceSqr(circle1, ShapeOrientation<Spot2D>(circle2.orientation, Spot2D())) <= Math::sqr(circle1.shape.radius - circle2.shape.radius);
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

float DistanceSqr(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(line);
    VERIFY_2D(spot);

    Math::Float2 closestPointOnLine = ClosestPointOnLine(line, spot);
    return Math::DistanceSqr(spot.orientation.position.XY, closestPointOnLine);
}

float DistanceSqr(const ShapeOrientation<Line2D>& line, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(line);
    VERIFY_2D(circle);

    ShapeOrientation<Spot2D> circleCenter = { circle.orientation, Spot2D() };
    return DistanceSqr(line, circleCenter) - Math::sqr(circle.shape.radius);
}

float DistanceSqr(const ShapeOrientation<Line2D>& line1, const ShapeOrientation<Line2D>& line2)
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

float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Spot2D>& spot)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(spot);

    const Math::Float2 closestPointInRectangle = ClosestPointToPoint(rectangle, spot);
    if (PointInRectangle(rectangle, closestPointInRectangle))
    {
        return 0.0f;
    }

    return Math::DistanceSqr(spot.orientation.position.XY, closestPointInRectangle);
}

float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Circle>& circle)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(circle);

    ShapeOrientation<Spot2D> circleCenter = { circle.orientation, Spot2D() };
    return DistanceSqr(rectangle, circleCenter) - Math::sqr(circle.shape.radius);
}

float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle, const ShapeOrientation<Line2D>& line)
{
    VERIFY_2D(rectangle);
    VERIFY_2D(line);

    const Math::Float2 closestPoint = ClosestPointToLine(rectangle, line);
    return DistanceSqr(line, { Orientation(Math::Float3(closestPoint)), Spot2D() });
}

float DistanceSqr(const ShapeOrientation<Rectangle>& rectangle1, const ShapeOrientation<Rectangle>& rectangle2)
{
    VERIFY_2D(rectangle1);
    VERIFY_2D(rectangle2);

    return 1.0f;
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
} // namespace Geometric
} // namespace Core