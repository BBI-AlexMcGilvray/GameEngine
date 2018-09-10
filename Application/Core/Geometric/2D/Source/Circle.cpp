#include "Core/Geometric/2D/Headers/Circle.h"

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

		Ptr<const Geometry2D> Circle2D::Intersection(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersection(this);
		}
		Ptr<const Geometry2D> Circle2D::Intersection(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersection(this, point);
		}
		Ptr<const Geometry2D> Circle2D::Intersection(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersection(this, line);
		}
		Ptr<const Geometry2D> Circle2D::Intersection(Ptr<const Box2D> Box2D) const
		{
			return GeometryFunctions2D::Intersection(this, Box2D);
		}
		Ptr<const Geometry2D> Circle2D::Intersection(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersection(this, circle);
		}
		Ptr<const Geometry2D> Circle2D::Intersection(Ptr<const Polygon2D> polygon) const
		{
			return GeometryFunctions2D::Intersection(this, polygon);
		}
	}
}