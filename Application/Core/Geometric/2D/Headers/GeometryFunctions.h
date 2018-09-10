#pragma once

#include "Core/Geometric/Headers/GeometryDefs.h"

#include "Core/Geometric/2D/Headers/Point.h"
#include "Core/Geometric/2D/Headers/Line.h"
#include "Core/Geometric/2D/Headers/Box.h"
#include "Core/Geometric/2D/Headers/Circle.h"
#include "Core/Geometric/2D/Headers/Polygon.h"

#include "Core/Headers/PtrDefs.h"

namespace Core
{
	namespace Geometric
	{
		namespace GeometryFunctions2D
		{
			Ptr<const Geometry2D> Intersection(Ptr<const Geometry2D> g1, Ptr<const Geometry2D> g2);

			Ptr<const Geometry2D> Intersection(Ptr<const Point2D> point1, Ptr<const Point2D> point2);
			Ptr<const Geometry2D> Intersection(Ptr<const Point2D> point, Ptr<const Line2D> line);
			Ptr<const Geometry2D> Intersection(Ptr<const Point2D> point, Ptr<const Box2D> box);
			Ptr<const Geometry2D> Intersection(Ptr<const Point2D> point, Ptr<const Circle2D> circle);
			Ptr<const Geometry2D> Intersection(Ptr<const Point2D> point, Ptr<const Polygon2D> polygon);

			Ptr<const Geometry2D> Intersection(Ptr<const Line2D> line, Ptr<const Point2D> point);
			Ptr<const Geometry2D> Intersection(Ptr<const Line2D> line1, Ptr<const Line2D> line2);
			Ptr<const Geometry2D> Intersection(Ptr<const Line2D> line, Ptr<const Box2D> box);
			Ptr<const Geometry2D> Intersection(Ptr<const Line2D> line, Ptr<const Circle2D> circle);
			Ptr<const Geometry2D> Intersection(Ptr<const Line2D> line, Ptr<const Polygon2D> polygon);

			Ptr<const Geometry2D> Intersection(Ptr<const Box2D> box, Ptr<const Point2D> point);
			Ptr<const Geometry2D> Intersection(Ptr<const Box2D> box, Ptr<const Line2D> line);
			Ptr<const Geometry2D> Intersection(Ptr<const Box2D> box1, Ptr<const Box2D> box2);
			Ptr<const Geometry2D> Intersection(Ptr<const Box2D> box, Ptr<const Circle2D> circle);
			Ptr<const Geometry2D> Intersection(Ptr<const Box2D> box, Ptr<const Polygon2D> polygon);

			Ptr<const Geometry2D> Intersection(Ptr<const Circle2D> circle, Ptr<const Point2D> point);
			Ptr<const Geometry2D> Intersection(Ptr<const Circle2D> circle, Ptr<const Line2D> line);
			Ptr<const Geometry2D> Intersection(Ptr<const Circle2D> circle, Ptr<const Box2D> box);
			Ptr<const Geometry2D> Intersection(Ptr<const Circle2D> circle1, Ptr<const Circle2D> circle2);
			Ptr<const Geometry2D> Intersection(Ptr<const Circle2D> circle, Ptr<const Polygon2D> polygon);

			Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon, Ptr<const Point2D> point);
			Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon, Ptr<const Line2D> line);
			Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon, Ptr<const Box2D> box);
			Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon, Ptr<const Circle2D> circle);
			Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon1, Ptr<const Polygon2D> polygon2);
		}
	}
}