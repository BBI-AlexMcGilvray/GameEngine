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
    const auto relativeSpot = point - box.orientation.GetPosition();
    const auto counterRotatedSpot = RotateVectorBy(relativeSpot, box.orientation.GetRotation().Inverse());

    const auto effectiveDimensions = EffectiveDimensions(box);
    return PointInBox(Box(effectiveDimensions), counterRotatedSpot);
}

bool PointInBox(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    return PointInBox(box, spot.orientation.GetPosition());
}

Math::Float3 BoxMax(const Box& box)
{
    return box.dimensions * 0.5f;
}

Math::Float3 BoxMin(const Box& box)
{
    return box.dimensions * -0.5f;
}

Math::Float3 BoxMaxAtOrigin(const ShapeOrientation<Box>& box)
{
    return BoxMax(Box(EffectiveDimensions(box)));
}

Math::Float3 BoxMinAtOrigin(const ShapeOrientation<Box>& box)
{
    return BoxMin(Box(EffectiveDimensions(box)));
}

// if this logic is changed, BoxEdges will need to be as well
std::array<Math::Float3, 8> BoxCorners(const ShapeOrientation<Box>& box)
{
    std::array<Math::Float3, 8> corners;

    const auto max = BoxMaxAtOrigin(box);
    const auto min = BoxMinAtOrigin(box);

    // 'bottom'
    corners[0] = box.orientation.GetPosition() + RotateVectorBy(min, box.orientation.GetRotation());
    corners[1] = box.orientation.GetPosition() + RotateVectorBy(Math::Float3(max.X, min.Y, min.Z), box.orientation.GetRotation());
    corners[2] = box.orientation.GetPosition() + RotateVectorBy(Math::Float3(min.X, min.Y, max.Z), box.orientation.GetRotation());
    corners[3] = box.orientation.GetPosition() + RotateVectorBy(Math::Float3(max.X, min.Y, max.Z), box.orientation.GetRotation());
    // 'top'
    corners[4] = box.orientation.GetPosition() + RotateVectorBy(Math::Float3(min.X, max.Y, min.Z), box.orientation.GetRotation());
    corners[5] = box.orientation.GetPosition() + RotateVectorBy(Math::Float3(max.X, max.Y, min.Z), box.orientation.GetRotation());
    corners[6] = box.orientation.GetPosition() + RotateVectorBy(Math::Float3(min.X, max.Y, max.Z), box.orientation.GetRotation());
    corners[7] = box.orientation.GetPosition() + RotateVectorBy(max, box.orientation.GetRotation());

    return corners;
}

std::array<ShapeOrientation<Line3D>, 12> BoxEdges(const ShapeOrientation<Box>& box)
{
    std::array<ShapeOrientation<Line3D>, 12> edges;

    // if the 'BoxCorners' logic is changed, this will need to as well
    const auto corners = BoxCorners(box);

    // 'bottom'
    edges[0] = LineFromPoints(corners[0], corners[1]);
    edges[1] = LineFromPoints(corners[0], corners[2]);
    edges[2] = LineFromPoints(corners[1], corners[3]);
    edges[3] = LineFromPoints(corners[2], corners[3]);

    // 'top'
    edges[4] = LineFromPoints(corners[4], corners[5]);
    edges[5] = LineFromPoints(corners[4], corners[6]);
    edges[6] = LineFromPoints(corners[5], corners[7]);
    edges[7] = LineFromPoints(corners[6], corners[7]);

    // 'sides'
    edges[8] = LineFromPoints(corners[0], corners[4]);
    edges[9] = LineFromPoints(corners[1], corners[5]);
    edges[10] = LineFromPoints(corners[2], corners[6]);
    edges[11] = LineFromPoints(corners[3], corners[7]);

    return edges;
}

// we always assume boxes are not rotated, instead rotated the other shape
Math::Float3 LastPointOnBoxInDirection(const ShapeOrientation<Box>& box, const Math::Float3& direction)
{
    const Line3D lineInDirection(RotateVectorBy(direction, box.orientation.GetRotation().Inverse()));
    ShapeOrientation<Line3D> lineOrientation(box.orientation.GetPosition(), lineInDirection);

    const auto boxMax = BoxMaxAtOrigin(box);
    const auto boxMin = BoxMinAtOrigin(box);

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

Math::Float3 ClosestPointToPoint(const Box& box, const Point3D& point)
{
    const auto halfDimensions = box.dimensions * 0.5f;
    return Math::Clamp(point, halfDimensions * -1.0f, halfDimensions); // closest point is in bounds in that direction
}

Math::Float3 ClosestPointToPoint(const ShapeOrientation<Box>& box, const Point3D& point)
{
    const auto relativeSpot = point - box.orientation.GetPosition();
    const auto counterRotatedSpot = RotateVectorBy(relativeSpot, box.orientation.GetRotation().Inverse());

    auto closestRelativeSpot = ClosestPointToPoint(Box(EffectiveDimensions(box)), counterRotatedSpot);
    return box.orientation.GetPosition() + RotateVectorBy(closestRelativeSpot, box.orientation.GetRotation());
}

Math::Float3 ClosestPointToPoint(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot)
{
    return ClosestPointToPoint(box, spot.orientation.GetPosition());
}

// probably not the most efficient, but can deal with that later
Math::Float3 ClosestPointToLine(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    ShapeOrientation<Line3D> counterRotatedLine = line;
    counterRotatedLine.orientation.SetPosition(RotateVectorBy(counterRotatedLine.orientation.GetPosition() - box.orientation.GetPosition(), box.orientation.GetRotation().Inverse())); // must also counter-rotate the line origin
    counterRotatedLine.orientation.AdjustRotation(box.orientation.GetRotation().Inverse()); // must alter the line's direction

    const auto lineOriginToBox = box.orientation.GetPosition() - counterRotatedLine.orientation.GetPosition();

    const auto linePointingToBox = Math::Dot(EffectiveDirection(counterRotatedLine), lineOriginToBox);
    if (linePointingToBox <= 0.0f) // pointing away/not at box, modified line origin will be closest
    {
        return ClosestPointToPoint(box, counterRotatedLine.orientation.GetPosition());
    }

    const auto boxMax = BoxMaxAtOrigin(box);
    const auto boxMin = BoxMinAtOrigin(box);
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
    Math::Float3 closestPointToBestIntersection = ClosestPointToPoint(box.shape, bestIntersection.second);
    bool bestHitsBox = closestPointToBestIntersection == bestIntersection.second;
    for (const auto intersection : planeIntersections)
    {
        bool newBest = false;

        const auto closestPointToCurrentIntersection = ClosestPointToPoint(box.shape, intersection.second);
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

    return box.orientation.GetPosition() + RotateVectorBy(closestPointToBestIntersection, box.orientation.GetRotation());
}
} // namespace Geometric
} // namespace Core