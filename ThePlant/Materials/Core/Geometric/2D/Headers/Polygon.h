#pragma once
/*
#include "Core/Geometric/2D/Headers/Geometry.h"
#include "Core/Headers/ListDefs.h"

namespace Core
{
	namespace Geometric
	{
		struct Polygon2D
		{
			Polygon2D(List<Float2> vertices);
			Polygon2D(Float2 origin, List<Float2> vertices);

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

		private:
			Float2 Origin;
			FQuaternion Rotation;
			Float2 Scale;

			List<Float2> Vertices;
		};
	}
}
*/