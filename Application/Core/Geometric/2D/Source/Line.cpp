#include "Core/Geometric/2D/Headers/Line.h"

#include "Core/Geometric/2D/Headers/Point.h"
#include "Core/Geometric/2D/Headers/Box.h"
#include "Core/Geometric/2D/Headers/Circle.h"
#include "Core/Geometric/2D/Headers/Polygon.h"

#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

#include "Core/Math/Headers/QuaternionFunctions.h"

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

		bool Line2D::PointOnLine(const Point2D& point) const
		{
			if (MaxAddition.X == 0.0f && MaxAddition.Y == 0.0f)
			{
				return (point.Axes == Origin.Axes);
			}

			if (MaxAddition.X == 0.0f)
			{
				if (Origin.X != point.X)
				{
					return false;
				}

				float additionScale = (point.Y - Origin.Y) / MaxAddition.Y;
				return InRange(additionScale, 0.0f, 1.0f);
			}

			if (MaxAddition.Y == 0.0f)
			{
				if (Origin.Y != point.Y)
				{
					return false;
				}

				float additionScale = (point.X - Origin.X) / MaxAddition.X;
				return InRange(additionScale, 0.0f, 1.0f);
			}

			float additionScaleX = (point.X - Origin.X) / MaxAddition.X;
			float additionScaleY = (point.Y - Origin.Y) / MaxAddition.Y;
			return (additionScaleX == additionScaleY && InRange(additionScaleX, 0.0f, 1.0f));
		}

		Point2D Line2D::PointAtScale(float scale) const
		{
			if (InRange(scale, 0.0f, 1.0f))
			{
				Float2 point = Origin + (scale * MaxAddition);
				return Point2D(point.X, point.Y);
			}
			else if (scale < 0.0f)
			{
				return Origin;
			}
			return (Origin + MaxAddition);
		}

		Point2D Line2D::ClosestPointToPoint(const Point2D& point) const
		{
			Float2 closestPoint = Origin + Project(point - Origin, MaxAddition);
			return Point2D(closestPoint.X, closestPoint.Y);
		}

		float Line2D::DistanceToPoint(const Point2D& point) const
		{
			return Sqrt(DistanceToPointSqr(point));
		}

		float Line2D::DistanceToPointSqr(const Point2D& point) const
		{
			return MagnitudeSqr(Perp(point - Origin, MaxAddition));
		}

		float Line2D::GetSlope() const
		{
			return (MaxAddition.Y - Origin.Y) / (MaxAddition.X - Origin.X);
		}

		float Line2D::GetIntercept() const
		{
			return Origin.Y - (GetSlope() * Origin.X);
		}

		bool Line2D::Intersect(Ptr<const Geometry2D> geometry) const
		{
			return geometry->Intersect(this);
		}
		bool Line2D::Intersect(Ptr<const Point2D> point) const
		{
			return GeometryFunctions2D::Intersect(this, point);
		}
		bool Line2D::Intersect(Ptr<const Line2D> line) const
		{
			return GeometryFunctions2D::Intersect(this, line);
		}
		bool Line2D::Intersect(Ptr<const Box2D> box) const
		{
			return GeometryFunctions2D::Intersect(this, box);
		}
		bool Line2D::Intersect(Ptr<const Circle2D> circle) const
		{
			return GeometryFunctions2D::Intersect(this, circle);
		}
		// Ptr<const Geometry2D> Line2D::Intersection(Ptr<const Polygon2D> polygon) const
		// {
		// 	return GeometryFunctions2D::Intersection(this, polygon);
		// }
	}
}