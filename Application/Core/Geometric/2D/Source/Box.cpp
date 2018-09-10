#include "Core/Geometric/2D/Headers/Box.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

namespace Core
{
	namespace Geometric
	{
		Box2D::Box2D()
			: Box2D(Float2(0.0f), 1.0f, 1.0f, FQuaternion(II{}))
		{}

		Box2D::Box2D(const Float2& origin)
			: Box2D(origin, 1.0f, 1.0f, FQuaternion(II{}))
		{}

		Box2D::Box2D(const Float2& origin, const FQuaternion& rotation)
			: Box2D(origin, 1.0f, 1.0f, rotation)
		{}

		Box2D::Box2D(const Float2& origin, const float& width, const float& length)
			: Box2D(origin, width, length, FQuaternion(II{}))
		{}

		Box2D::Box2D(const Float2& origin, const float& width, const float& length, const FQuaternion& rotation)
			: Origin(origin), Scale(width, length), Rotation(rotation)
		{}

		void Box2D::SetPosition(const Float2& origin)
		{
			Origin = origin;
		}

		void Box2D::AdjustPosition(const Float2& adjustment)
		{
			SetPosition(Origin + adjustment);
		}

		Float2 Box2D::GetPosition() const
		{
			return Origin;
		}

		void Box2D::SetRotation(const FQuaternion& rotation)
		{
			Rotation = rotation;
		}

		void Box2D::AdjustRotation(const FQuaternion& adjustment)
		{
			SetRotation(adjustment * Rotation);
		}

		FQuaternion Box2D::GetRotation() const
		{
			return Rotation;
		}

		void Box2D::SetScale(const float& scale)
		{
			Scale = scale;
		}

		void Box2D::SetScale(const Float2& scale)
		{
			Scale = scale;
		}

		void Box2D::AdjustScale(const float& adjustment)
		{
			SetScale(Scale + adjustment);
		}

		void Box2D::AdjustScale(const Float2& adjustment)
		{
			SetScale(Scale + adjustment);
		}

		Float2 Box2D::GetScale() const
		{
			return Scale;
		}

		Ptr<const Geometry2D> Box2D::Intersection(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersection(this);
		}
		Ptr<const Geometry2D> Box2D::Intersection(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersection(this, point);
		}
		Ptr<const Geometry2D> Box2D::Intersection(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersection(this, line);
		}
		Ptr<const Geometry2D> Box2D::Intersection(Ptr<const Box2D> box) const
		{
			return GeometryFunctions2D::Intersection(this, box);
		}
		Ptr<const Geometry2D> Box2D::Intersection(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersection(this, circle);
		}
		Ptr<const Geometry2D> Box2D::Intersection(Ptr<const Polygon2D> polygon) const
		{
			return GeometryFunctions2D::Intersection(this, polygon);
		}
	}
}