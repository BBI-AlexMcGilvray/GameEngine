#include "Core/Geometric/2D/Headers/Line.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

namespace Core
{
	namespace Geometric
	{
		Line2D::Line2D()
			: Line2D(Float2(0.0f), Float2(II{}), 1.0f)
		{}

		Line2D::Line2D(const Float2& origin, const Float2& end)
			: Line2D(origin, end - origin, Magnitude(end - origin))
		{}

		Line2D::Line2D(const Float2& origin, const Float2& direction, const float& length)
			: Origin(origin), MaxAddition(Normalize(direction) * length)
		{}

		void Line2D::SetPosition(const Float2& origin)
		{
			Origin = origin;
		}

		void Line2D::AdjustPosition(const Float2& adjustment)
		{
			SetPosition(Origin + adjustment);
		}

		Float2 Line2D::GetPosition() const
		{
			return Origin;
		}

		void Line2D::SetRotation(const FQuaternion& rotation)
		{
			MaxAddition = RotateVectorBy(Float3(MaxAddition, 0.0f), rotation);
		}

		void Line2D::AdjustRotation(const FQuaternion& adjustment)
		{
			SetRotation(adjustment);
		}

		FQuaternion Line2D::GetRotation() const
		{
			return FQuaternion();
		}

		void Line2D::SetScale(const float& scale)
		{
			MaxAddition = scale;
		}

		void Line2D::SetScale(const Float2& scale)
		{
			MaxAddition = scale;
		}

		void Line2D::AdjustScale(const float& adjustment)
		{
			SetScale(MaxAddition + adjustment);
		}

		void Line2D::AdjustScale(const Float2& adjustment)
		{
			SetScale(MaxAddition + adjustment);
		}

		Float2 Line2D::GetScale() const
		{
			return MaxAddition;
		}

		Ptr<const Geometry2D> Line2D::Intersection(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersection(this);
		}
		Ptr<const Geometry2D> Line2D::Intersection(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersection(this, point);
		}
		Ptr<const Geometry2D> Line2D::Intersection(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersection(this, line);
		}
		Ptr<const Geometry2D> Line2D::Intersection(Ptr<const Box2D> box) const
		{
			return GeometryFunctions2D::Intersection(this, box);
		}
		Ptr<const Geometry2D> Line2D::Intersection(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersection(this, circle);
		}
		Ptr<const Geometry2D> Line2D::Intersection(Ptr<const Polygon2D> polygon) const
		{
			return GeometryFunctions2D::Intersection(this, polygon);
		}
	}
}