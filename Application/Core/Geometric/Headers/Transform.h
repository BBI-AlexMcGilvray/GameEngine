#pragma once

#include "Core/Geometric/Headers/GeometryDefs.h"

#include "Core/Math/Headers/Matrix4x4.h"

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

			void SetPosition(const Float3& position) override;
			void AdjustPosition(const Float3& movement) override;
			Float3 GetPosition() const override;

			void SetRotation(const FQuaternion& rotation) override;
			void AdjustRotation(const FQuaternion& rotation) override;
			FQuaternion GetRotation() const override;
			Float3x3 GetRotationMatrix() const;

			void SetScale(const float& scale) override;
			void SetScale(const Float3& scale) override;
			void AdjustScale(const float& scale) override;
			void AdjustScale(const Float3& scale) override;
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