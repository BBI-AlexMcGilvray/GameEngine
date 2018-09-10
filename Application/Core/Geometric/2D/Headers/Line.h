#pragma once

#include "Core/Geometric/2D/Headers/Geometry.h"

namespace Core
{
	namespace Geometric
	{
		struct Line2D : Geometry2D
		{
			Line2D();
			Line2D(const Float2& origin, const Float2& end);
			Line2D(const Float2& origin, const Float2& direction, const float& length);

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

			Ptr<const Geometry2D> Intersection(Ptr<const Geometry2D> geometry) const override;
			Ptr<const Geometry2D> Intersection(Ptr<const Point2D> point) const override;
			Ptr<const Geometry2D> Intersection(Ptr<const Line2D> line) const override;
			Ptr<const Geometry2D> Intersection(Ptr<const Box2D> box) const override;
			Ptr<const Geometry2D> Intersection(Ptr<const Circle2D> circle) const override;
			Ptr<const Geometry2D> Intersection(Ptr<const Polygon2D> polygon) const override;

		private:
			Float2 Origin;
			Float2 MaxAddition; // this is as far in the given direction the line can go
		};
	}
}