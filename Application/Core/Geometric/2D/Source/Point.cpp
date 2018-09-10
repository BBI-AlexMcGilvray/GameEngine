#include "Core/Geometric/2D/Headers/Point.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

namespace Core
{
	namespace Geometric
	{
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

		Ptr<const Geometry2D> Point2D::Intersection(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersection(this);
		}
		Ptr<const Geometry2D> Point2D::Intersection(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersection(this, point);
		}
		Ptr<const Geometry2D> Point2D::Intersection(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersection(this, line);
		}
		Ptr<const Geometry2D> Point2D::Intersection(Ptr<const Box2D> box) const
		{
			return GeometryFunctions2D::Intersection(this, box);
		}
		Ptr<const Geometry2D> Point2D::Intersection(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersection(this, circle);
		}
		Ptr<const Geometry2D> Point2D::Intersection(Ptr<const Polygon2D> polygon) const
		{
			return GeometryFunctions2D::Intersection(this, polygon);
		}
	}
}