#pragma once

#include "Core/Geometric/2D/Headers/Geometry.h"

namespace Core
{
	namespace Geometric
	{
		struct Point2D : Float2, Geometry2D
		{
			using Float2::Float2;
			Point2D(Float2 point);

			void SetPosition(const Float2& position) override;
			void AdjustPosition(const Float2& adjustment) override;
			Float2 GetPosition() const override;

			void SetRotation(const FQuaternion& rotation) override;
			void AdjustRotation(const FQuaternion& adjustment) override;
			FQuaternion GetRotation() const override;

			void SetScale(const float& scale) override;
			void SetScale(const Float2& scale) override;
			void AdjustScale(const float& adjustment) override;
			void AdjustScale(const Float2& adjustment) override;
			Float2 GetScale() const override;

			bool Intersect(Ptr<const Geometry2D> geometry) const override;
			bool Intersect(Ptr<const Point2D> point) const override;
			bool Intersect(Ptr<const Line2D> line) const override;
			bool Intersect(Ptr<const Box2D> box) const override;
			bool Intersect(Ptr<const Circle2D> circle) const override;
			// Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon) const override;
		};
	}
}