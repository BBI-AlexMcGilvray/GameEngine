#include "Core/Geometric/2D/Headers/Point.h"

#include "Core/Geometric/2D/Headers/Line.h"
#include "Core/Geometric/2D/Headers/Box.h"
#include "Core/Geometric/2D/Headers/Circle.h"
#include "Core/Geometric/2D/Headers/Polygon.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

namespace Core
{
	namespace Geometric
	{
		Point2D::Point2D(Float2 point)
		{
			X = point.X;
			Y = point.Y;
		}

		void Point2D::SetPosition(const Float2& position)
		{
			X = position.X;
			Y = position.Y;
		}

		void Point2D::AdjustPosition(const Float2& adjustment)
		{
			X += adjustment.X;
			Y += adjustment.Y;
		}

		Float2 Point2D::GetPosition() const
		{
			return *this;
		}

		void Point2D::SetRotation(const FQuaternion& rotation)
		{
			/* does nothing */
		}

		void Point2D::AdjustRotation(const FQuaternion& adjustment)
		{
			/* does nothing */
		}

		FQuaternion Point2D::GetRotation() const
		{
			return FQuaternion();
		}

		void Point2D::SetScale(const float& scale)
		{
			/* does nothing */
		}

		void Point2D::SetScale(const Float2& scale)
		{
			/* does nothing */
		}

		void Point2D::AdjustScale(const float& adjustment)
		{
			/* does nothing */
		}

		void Point2D::AdjustScale(const Float2& adjustment)
		{
			/* does nothing */
		}

		Float2 Point2D::GetScale() const
		{
			return Float2{ 1.0f };
		}

		bool Point2D::Intersect(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersect(this);
		}
		bool Point2D::Intersect(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersect(this, point);
		}
		bool Point2D::Intersect(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersect(this, line);
		}
		bool Point2D::Intersect(Ptr<const Box2D> box) const
		{
			return GeometryFunctions2D::Intersect(this, box);
		}
		bool Point2D::Intersect(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersect(this, circle);
		}
		// Ptr<const Geometry2D> Point2D::Intersection(Ptr<const Polygon2D> polygon) const
		// {
		// 	return GeometryFunctions2D::Intersection(this, polygon);
		// }
	}
}