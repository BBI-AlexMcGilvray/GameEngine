/*
#include "Core/Geometric/2D/Headers/Polygon.h"

#include "Core/Geometric/2D/Headers/Point.h"
#include "Core/Geometric/2D/Headers/Line.h"
#include "Core/Geometric/2D/Headers/Box.h"
#include "Core/Geometric/2D/Headers/Circle.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

namespace Core
{
	namespace Geometric
	{
		Polygon2D::Polygon2D(List<Float2> vertices)
			: Polygon2D(Float2(0.0f), vertices)
		{}

		Polygon2D::Polygon2D(Float2 origin, List<Float2> vertices)
			: Origin(origin), Vertices(vertices)
		{

		}

		void Polygon2D::SetPosition(const Float2& position)
		{
			Origin = position;
		}

		void Polygon2D::AdjustPosition(const Float2& adjustment)
		{
			SetPosition(Origin + adjustment);
		}

		Float2 Polygon2D::GetPosition() const
		{
			return Origin;
		}

		void Polygon2D::SetRotation(const FQuaternion& rotation)
		{
			Rotation = rotation;
		}

		void Polygon2D::AdjustRotation(const FQuaternion& adjustment)
		{
			SetRotation(adjustment * Rotation);
		}

		FQuaternion Polygon2D::GetRotation() const
		{
			return Rotation;
		}

		void Polygon2D::SetScale(const float& scale)
		{
			Scale = scale;
		}

		void Polygon2D::SetScale(const Float2& scale)
		{
			Scale = scale;
		}

		void Polygon2D::AdjustScale(const float& adjustment)
		{
			SetScale(Scale + adjustment);
		}

		void Polygon2D::AdjustScale(const Float2& adjustment)
		{
			SetScale(Scale + adjustment);
		}

		Float2 Polygon2D::GetScale() const
		{
			return Scale;
		}

		Ptr<const Geometry2D> Polygon2D::Intersection(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersection(this);
		}
		Ptr<const Geometry2D> Polygon2D::Intersection(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersection(this, point);
		}
		Ptr<const Geometry2D> Polygon2D::Intersection(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersection(this, line);
		}
		Ptr<const Geometry2D> Polygon2D::Intersection(Ptr<const Box2D> Box2D) const
		{
			return GeometryFunctions2D::Intersection(this, Box2D);
		}
		Ptr<const Geometry2D> Polygon2D::Intersection(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersection(this, circle);
		}
		Ptr<const Geometry2D> Polygon2D::Intersection(Ptr<const Polygon2D> polygon) const
		{
			return GeometryFunctions2D::Intersection(this, polygon);
		}
	}
}
*/