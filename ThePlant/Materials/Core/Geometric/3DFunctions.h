#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
/*
NOTE: All DistanceSqr(...) methods return POSITIVE values
*/
    // SPOT
    float DistanceSqr(const ShapeOrientation<Spot3D>& spot1, const ShapeOrientation<Spot3D>& spot2);
    bool Engulfs(const ShapeOrientation<Spot3D>& spot1, const ShapeOrientation<Spot3D>& spot2);
    bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Line3D>& line);
    bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Plane>& plane);
    bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Sphere>& sphere);
    bool Engulfs(const ShapeOrientation<Spot3D>& spot, const ShapeOrientation<Box>& box);

    // LINE
    float DistanceSqr(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot);
    float DistanceSqr(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2);
    bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Spot3D>& spot);
    bool Engulfs(const ShapeOrientation<Line3D>& line1, const ShapeOrientation<Line3D>& line2);
    bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Plane>& plane);
    bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Sphere>& sphere);
    bool Engulfs(const ShapeOrientation<Line3D>& line, const ShapeOrientation<Box>& box);

    // PLANE
    float DistanceSqr(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot);
    float DistanceSqr(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line);
    float DistanceSqr(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2);
    bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Spot3D>& spot);
    bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Line3D>& line);
    bool Engulfs(const ShapeOrientation<Plane>& plane1, const ShapeOrientation<Plane>& plane2);
    bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Sphere>& sphere);
    bool Engulfs(const ShapeOrientation<Plane>& plane, const ShapeOrientation<Box>& box);
    
    // SPHERE
    float DistanceSqr(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Spot3D>& spot);
    float DistanceSqr(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line);
    float DistanceSqr(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane);
    float DistanceSqr(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Spot3D>& spot);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Line3D>& line);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Plane>& plane);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere1, const ShapeOrientation<Sphere>& sphere2);
    bool Engulfs(const ShapeOrientation<Sphere>& sphere, const ShapeOrientation<Box>& box);

    // BOX
    float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot);
    float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line);
    float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane);
    float DistanceSqr(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere);
    float DistanceSqr(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Spot3D>& spot);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Line3D>& line);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Plane>& plane);
    bool Engulfs(const ShapeOrientation<Box>& box, const ShapeOrientation<Sphere>& sphere);
    bool Engulfs(const ShapeOrientation<Box>& box1, const ShapeOrientation<Box>& box2);

    // AABB - only against other AABBs for now as this is just used in oct trees for now
    bool Intersect(const ShapeOrientation<AABB>& aabb1, const ShapeOrientation<AABB>& aabb2);
    bool Engulfs(const ShapeOrientation<AABB>& aabb1, const ShapeOrientation<AABB>& aabb2);
}// namespace Geometric
}// namespace Core