#pragma once

#include "Core/Geometric/Headers/GeometryDefs.h"

using namespace Core::Math;

namespace Core
{
	namespace Geometric
	{
		struct Transform : ITranslatable3D, IRotatable3D, IScalable3D
		{
			Transform();

			Transform(Float3 position, FQuaternion rotation = FQuaternion(II{}), Float3 scale = Float3(1.0f));

			Float4x4 GetTransformationMatrix() const;

			void SetPosition(Float3 const& position) override;
			void AdjustPosition(Float3 const& movement) override;
			Float3 GetPosition() const override;

			void SetRotation(FQuaternion const& rotation) override;
			void AdjustRotation(FQuaternion const& rotation) override;
			FQuaternion GetRotation() const override;
			Float3x3 GetRotationMatrix() const;

			void SetScale(Float3 const& scale) override;
			void AdjustScale(Float3 const& scale) override;
			Float3 GetScale() const override;

		protected:
			Float3 Position;
			FQuaternion Rotation;
			Float3 Scale;

			Float3x3 RotationMatrix;

			void RecalculateRotationMatrix();
		};
	}
}