#include "Core/Geometric/2D/Headers/Box.h"

#include "Core/Geometric/2D/Headers/Point.h"
#include "Core/Geometric/2D/Headers/Line.h"
#include "Core/Geometric/2D/Headers/Circle.h"
#include "Core/Geometric/2D/Headers/Polygon.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

#include "Core/Math/Headers/QuaternionFunctions.h"

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

		Float2 Box2D::GetTopLeftCorner() const
		{
			Float2 corner = Float2(Origin.X - Scale.X, Origin.Y + Scale.Y);
			return RotateVectorBy(corner, Rotation);
		}

		Float2 Box2D::GetTopRightCorner() const
		{
			Float2 corner = Float2(Origin.X + Scale.X, Origin.Y + Scale.Y);
			return RotateVectorBy(corner, Rotation);
		}

		Float2 Box2D::GetBottomLeftCorner() const
		{
			Float2 corner = Float2(Origin.X - Scale.X, Origin.Y - Scale.Y);
			return RotateVectorBy(corner, Rotation);
		}

		Float2 Box2D::GetBottomRightCorner() const
		{
			Float2 corner = Float2(Origin.X + Scale.X, Origin.Y - Scale.Y);
			return RotateVectorBy(corner, Rotation);
		}

		Float2 Box2D::GetRelativeHeightAxis() const
		{
			Float2 axis = (GetTopRightCorner() - GetBottomRightCorner());
			return RotateVectorBy(axis, Rotation);
		}

		Float2 Box2D::GetRelativeWidthAxis() const
		{
			Float2 axis = (GetTopRightCorner() - GetTopLeftCorner());
			return RotateVectorBy(axis, Rotation);
		}

		bool Box2D::Intersect(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersect(this);
		}
		bool Box2D::Intersect(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersect(this, point);
		}
		bool Box2D::Intersect(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersect(this, line);
		}
		bool Box2D::Intersect(Ptr<const Box2D> box) const
		{
			return GeometryFunctions2D::Intersect(this, box);
		}
		bool Box2D::Intersect(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersect(this, circle);
		}
		// Ptr<const Geometry2D> Box2D::Intersection(Ptr<const Polygon2D> polygon) const
		// {
		// 	return GeometryFunctions2D::Intersection(this, polygon);
		// }
	}
}