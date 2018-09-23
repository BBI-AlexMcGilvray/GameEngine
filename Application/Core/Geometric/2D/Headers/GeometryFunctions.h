#pragma once

#include "Core/Geometric/Headers/GeometryDefs.h"

#include "Core/Geometric/2D/Headers/Geometry.h"

#include "Core/Headers/PtrDefs.h"

namespace Core
{
	namespace Geometric
	{
		namespace GeometryFunctions2D
		{
			bool Intersect(Ptr<const Geometry2D> geometry1, Ptr<const Geometry2D> geometry2);

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Point2D> point);
			bool Intersect(Ptr<const Point2D> point, Ptr<const Geometry2D> geometry);

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Line2D> line);
			bool Intersect(Ptr<const Line2D> line, Ptr<const Geometry2D> geometry);

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Box2D> box);
			bool Intersect(Ptr<const Box2D> box, Ptr<const Geometry2D> geometry);

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Circle2D> circle);
			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Geometry2D> geometry);

			// bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Polygon2D> polygon)
			// { return geometry->Intersect(polygon); }
			// bool Intersect(Ptr<const Polygon2D> polygon, Ptr<const Geometry2D> geometry)
			// { return geometry->Intersect(polygon); }

			bool Intersect(Ptr<const Point2D> point1, Ptr<const Point2D> point2);
			bool Intersect(Ptr<const Point2D> point, Ptr<const Line2D> line);
			bool Intersect(Ptr<const Point2D> point, Ptr<const Box2D> box);
			bool Intersect(Ptr<const Point2D> point, Ptr<const Circle2D> circle);
			// bool Intersect(Ptr<const Point2D> point, Ptr<const Polygon2D> polygon);

			bool Intersect(Ptr<const Line2D> line, Ptr<const Point2D> point);
			bool Intersect(Ptr<const Line2D> line1, Ptr<const Line2D> line2);
			bool Intersect(Ptr<const Line2D> line, Ptr<const Box2D> box);
			bool Intersect(Ptr<const Line2D> line, Ptr<const Circle2D> circle);
			// bool Intersect(Ptr<const Line2D> line, Ptr<const Polygon2D> polygon);

			bool Intersect(Ptr<const Box2D> box, Ptr<const Point2D> point);
			bool Intersect(Ptr<const Box2D> box, Ptr<const Line2D> line);
			bool Intersect(Ptr<const Box2D> box1, Ptr<const Box2D> box2);
			bool Intersect(Ptr<const Box2D> box, Ptr<const Circle2D> circle);
			// bool Intersect(Ptr<const Box2D> box, Ptr<const Polygon2D> polygon);

			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Point2D> point);
			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Line2D> line);
			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Box2D> box);
			bool Intersect(Ptr<const Circle2D> circle1, Ptr<const Circle2D> circle2);
			// bool Intersect(Ptr<const Circle2D> circle, Ptr<const Polygon2D> polygon);

			// bool Intersect(Ptr<const Polygon2D> polygon, Ptr<const Point2D> point)
			// { return Intersect(point, polygon); }
			// bool Intersect(Ptr<const Polygon2D> polygon, Ptr<const Line2D> line)
			// { return Intersect(line, polygon); }
			// bool Intersect(Ptr<const Polygon2D> polygon, Ptr<const Box2D> box)
			// { return Intersect(box, polygon); }
			// bool Intersect(Ptr<const Polygon2D> polygon, Ptr<const Circle2D> circle)
			// { return Intersect(circle, polygon); }
			// bool Intersect(Ptr<const Polygon2D> polygon1, Ptr<const Polygon2D> polygon2);
		}
	}
}