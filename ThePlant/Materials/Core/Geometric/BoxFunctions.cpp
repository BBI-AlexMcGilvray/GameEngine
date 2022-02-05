#include "Core/Geometric/BoxFunctions.h"

#include "Core/Geometric/Transform.h"
#include "Core/Geometric/Line3DFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
Math::Float3 EffectiveDimensions(const ShapeOrientation<Box>& box)
{
    return box.shape.dimensions * box.orientation.GetScale();
}

bool PointInBox(const Box& box, const Point3D& point)
{
    const auto halfDimensions = box.dimensions * 0.5f;
    return (Math::Clamp(point, halfDimensions * -1.0f, halfDimensions) == point);
}

bool PointInBox(const ShapeOrientation<Box>& box, const Point3D& point)
{
    const auto counterRotatedSpot = RotateVectorBy(point, box.orientation.GetRotation().Inverse());
    const auto relativeSpot = counterRotatedSpot - box.orientation.GetPosition();

    const auto effectiveDimensions = EffectiveDimensions(box);
    return PointInBox(Box(effectiveDimensions), relativeSpot);
}

bool PointInBox(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    return PointInBox(box, spot.orientation.GetPosition());
}

// we always assume boxes are not rotated, instead rotated the other shape
Math::Float3 BoxMaxCenteredAt0(const ShapeOrientation<Box>& box)
{
    return box.orientation.GetPosition() + (EffectiveDimensions(box) * 0.5f);
}

// we always assume boxes are not rotated, instead rotated the other shape
Math::Float3 BoxMinCenteredAt0(const ShapeOrientation<Box>& box)
{
    return box.orientation.GetPosition() - (EffectiveDimensions(box) * 0.5f);
}

std::array<Math::Float3, 8> BoxCorners(const ShapeOrientation<Box>& box)
{
    std::array<Math::Float3, 8> corners;

    const auto max = RotateVectorBy(BoxMaxCenteredAt0(box), box.orientation.GetRotation());
    const auto min = RotateVectorBy(BoxMinCenteredAt0(box), box.orientation.GetRotation());

    corners[0] = min;
    corners[1] = Math::Float3(min.X, min.Y, max.Z);
    corners[2] = Math::Float3(min.X, max.Y, min.Z);
    corners[3] = Math::Float3(max.X, min.Y, min.Z);
    corners[4] = Math::Float3(min.X, max.Y, max.Z);
    corners[5] = Math::Float3(max.X, max.Y, min.Z);
    corners[6] = Math::Float3(max.X, min.Y, max.Z);
    corners[7] = max;

    return corners;
}

// we always assume boxes are not rotated, instead rotated the other shape
Math::Float3 LastPointOnBoxInDirection(const ShapeOrientation<Box>& box, const Math::Float3& direction)
{
    const Line3D lineInDirection(RotateVectorBy(direction, box.orientation.GetRotation().Inverse()));
    ShapeOrientation<Line3D> lineOrientation(box.orientation.GetPosition(), lineInDirection);

    const auto boxMax = BoxMaxCenteredAt0(box);
    const auto boxMin = BoxMinCenteredAt0(box);

    const auto xMult_Min = LineMultiplierForPoint_X(lineOrientation, boxMin);
    const auto xMult_Max = LineMultiplierForPoint_X(lineOrientation, boxMax);
    const auto xMult = xMult_Min < 0.0f ? xMult_Max : (xMult_Max < 0.0f ? xMult_Min : std::min(xMult_Min, xMult_Max));

    const auto yMult_Min = LineMultiplierForPoint_Y(lineOrientation, boxMin);
    const auto yMult_Max = LineMultiplierForPoint_Y(lineOrientation, boxMax);
    const auto yMult = yMult_Min < 0.0f ? yMult_Max : (yMult_Max < 0.0f ? yMult_Min : std::min(yMult_Min, yMult_Max));

    const auto zMult_Min = LineMultiplierForPoint_Z(lineOrientation, boxMin);
    const auto zMult_Max = LineMultiplierForPoint_Z(lineOrientation, boxMax);
    const auto zMult = zMult_Min < 0.0f ? zMult_Max : (zMult_Max < 0.0f ? zMult_Min : std::min(zMult_Min, zMult_Max));

    const auto smallestMult = std::min(std::min(xMult, yMult), xMult);
    return ClosestPointToPoint(box, PointOnLine(lineOrientation, smallestMult));
}

Math::Float3 ClosestPointToPoint(const ShapeOrientation<Box>& box, const Point3D& point)
{
    const auto halfDimensions = EffectiveDimensions(box) * 0.5f;
    return Math::Clamp(point, halfDimensions * -1.0f, halfDimensions); // closest point is in bounds in that direction
}

Math::Float3 ClosestPointToPoint(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    const auto counterRotatedSpot = RotateVectorBy(spot.orientation.GetPosition(), box.orientation.GetRotation().Inverse());
    const auto relativeSpot = counterRotatedSpot - box.orientation.GetPosition();

    return ClosestPointToPoint(box, relativeSpot);
}

// probably not the most efficient, but can deal with that later
Math::Float3 ClosestPointToLine(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    ShapeOrientation<Line3D> counterRotatedLine = line;
    counterRotatedLine.orientation.SetPosition(RotateVectorBy(counterRotatedLine.orientation.GetPosition(), box.orientation.GetRotation().Inverse())); // must also counter-rotate the line origin
    counterRotatedLine.orientation.AdjustRotation(box.orientation.GetRotation().Inverse()); // must alter the line's direction

    const auto lineOriginToBox = box.orientation.GetPosition() - counterRotatedLine.orientation.GetPosition();

    const auto linePointingToBox = Math::Dot(EffectiveDirection(counterRotatedLine), lineOriginToBox);
    if (linePointingToBox <= 0.0f) // pointing away/not at box, modified line origin will be closest
    {
        return ClosestPointToPoint(box, counterRotatedLine.orientation.GetPosition());
    }

    const auto boxMax = BoxMaxCenteredAt0(box);
    const auto boxMin = BoxMinCenteredAt0(box);
    std::array<std::pair<float, Math::Float3>, 6> planeIntersections;

    const auto xMult_Min = LineMultiplierForPoint_X(counterRotatedLine, boxMin);
    const auto xMult_Max = LineMultiplierForPoint_X(counterRotatedLine, boxMax);
    const auto crossMinXPoint = PointOnLine(counterRotatedLine, xMult_Min);
    const auto crossMaxXPoint = PointOnLine(counterRotatedLine, xMult_Max);
    planeIntersections[0] = {xMult_Min, crossMinXPoint};
    planeIntersections[1] = {xMult_Max, crossMaxXPoint};

    const auto yMult_Min = LineMultiplierForPoint_Y(counterRotatedLine, boxMin);
    const auto yMult_Max = LineMultiplierForPoint_Y(counterRotatedLine, boxMax);
    const auto crossMinYPoint = PointOnLine(counterRotatedLine, yMult_Min);
    const auto crossMaxYPoint = PointOnLine(counterRotatedLine, yMult_Max);
    planeIntersections[2] = {yMult_Min, crossMinYPoint};
    planeIntersections[3] = {yMult_Max, crossMaxYPoint};

    const auto zMult_Min = LineMultiplierForPoint_Z(counterRotatedLine, boxMin);
    const auto zMult_Max = LineMultiplierForPoint_Z(counterRotatedLine, boxMax);
    const auto crossMinZPoint = PointOnLine(counterRotatedLine, zMult_Min);
    const auto crossMaxZPoint = PointOnLine(counterRotatedLine, zMult_Max);
    planeIntersections[4] = {zMult_Min, crossMinZPoint};
    planeIntersections[5] = {zMult_Max, crossMaxZPoint};
    
    std::pair<float, Math::Float3> bestIntersection = planeIntersections[0];
    Math::Float3 closestPointToBestIntersection = ClosestPointToPoint(box, bestIntersection.second);
    bool bestHitsBox = closestPointToBestIntersection == bestIntersection.second;
    for (const auto intersection : planeIntersections)
    {
        bool newBest = false;

        const auto closestPointToCurrentIntersection = ClosestPointToPoint(box, intersection.second);
        bool currentHitsBox = closestPointToCurrentIntersection == intersection.second;

        if (bestIntersection.first < 0.0f) // line must go backwards
        {
            newBest = true; // best sucks, just replace it
        }
        else if (intersection.first < 0.0f) // line must go backwards
        {
            newBest = false; // don't replace if this one also sucks
        }
        else
        {
            // both miss, but this one is closer to the box
            bool closerMiss = (!bestHitsBox && !currentHitsBox && Distance(intersection.second, closestPointToCurrentIntersection) < Distance(bestIntersection.second, closestPointToBestIntersection));
            bool thisOneHits = (!bestHitsBox && currentHitsBox); // the current best misses, this one hits
            bool hitsSooner = (bestHitsBox && currentHitsBox && intersection.first < bestIntersection.first); // both hit, but one happens sooner on the line
            newBest = closerMiss || thisOneHits || hitsSooner;
        }

        if (newBest)
        {
            bestIntersection = intersection;
            closestPointToBestIntersection = closestPointToCurrentIntersection;
            bestHitsBox = currentHitsBox;
        }
    }

    return closestPointToBestIntersection;
}
} // namespace Geometric
} // namespace Core