#pragma once

#include "Core/Geometric/Headers/GeometryDefs.h"

namespace Core
{
	namespace Geometric
	{
		struct Point2D;
		struct Line2D;
		struct Box2D;
		struct Circle2D;
		struct Polygon2D;

		struct Geometry2D : Geometry, ITranslatable2D, IRotatable2D, IScalable2D
		{
			virtual bool Intersect(Ptr<const Geometry2D> geometry) const = 0;

			virtual bool Intersect(Ptr<const Point2D> point) const = 0;
			virtual bool Intersect(Ptr<const Line2D> line) const = 0;
			virtual bool Intersect(Ptr<const Box2D> box) const = 0;
			virtual bool Intersect(Ptr<const Circle2D> circle) const = 0;
			// virtual Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon) const = 0;
		};
	}
}