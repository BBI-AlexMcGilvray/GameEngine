#include "Core/Geometric/2D/Headers/Circle.h"

#include "Core/Geometric/2D/Headers/Point.h"
#include "Core/Geometric/2D/Headers/Line.h"
#include "Core/Geometric/2D/Headers/Box.h"
#include "Core/Geometric/2D/Headers/Polygon.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

namespace Core
{
	namespace Geometric
	{
		Circle2D::Circle2D()
			: Circle2D(Float2(0.0f), 1.0f)
		{}

		Circle2D::Circle2D(const Float2& origin)
			: Circle2D(origin, 1.0f)
		{}

		Circle2D::Circle2D(const Float2& origin, const float& radius)
			: Origin(origin), Radius(radius)
		{}

		void Circle2D::SetPosition(const Float2& origin)
		{
			Origin = origin;
		}

		void Circle2D::AdjustPosition(const Float2& adjustment)
		{
			SetPosition(Origin + adjustment);
		}

		Float2 Circle2D::GetPosition() const
		{
			return Origin;
		}

		void Circle2D::SetRotation(const FQuaternion& rotation)
		{
			/* does nothing */
		}

		void Circle2D::AdjustRotation(const FQuaternion& adjustment)
		{
			/* does nothing */
		}

		FQuaternion Circle2D::GetRotation() const
		{
			return FQuaternion();
		}

		void Circle2D::SetScale(const float& scale)
		{
			Radius = scale;
		}

		void Circle2D::SetScale(const Float2& scale)
		{
			/* does nothing */
		}

		void Circle2D::AdjustScale(const float& adjustment)
		{
			SetScale(Radius + adjustment);
		}

		void Circle2D::AdjustScale(const Float2& adjustment)
		{
			/* does nothing */
		}

		Float2 Circle2D::GetScale() const
		{
			return Radius;
		}

		bool Circle2D::PointInCircle(const Point2D& point) const
		{
			return (MagnitudeSqr(point - Origin) <= Sqr(Radius));
		}

		bool Circle2D::Intersect(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersect(this);
		}
		bool Circle2D::Intersect(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersect(this, point);
		}
		bool Circle2D::Intersect(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersect(this, line);
		}
		bool Circle2D::Intersect(Ptr<const Box2D> Box2D) const
		{
			return GeometryFunctions2D::Intersect(this, Box2D);
		}
		bool Circle2D::Intersect(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersect(this, circle);
		}
		// Ptr<const Geometry2D> Circle2D::Intersection(Ptr<const Polygon2D> polygon) const
		// {
		// 	return GeometryFunctions2D::Intersection(this, polygon);
		// }
	}
}