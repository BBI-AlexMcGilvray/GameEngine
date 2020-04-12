#pragma once

#include "Core/Geometric/Headers/GeometryDefs.h"

#include "Core/Math/Headers/Matrix4x4.h"
#include "Core/Functionality/Headers/Event.h"

// testing
#include "Core/Debugging/Headers/Macros.h"

using namespace Core::Math;

namespace Core
{
	namespace Geometric
	{
		struct Transform : ITranslatable3D, IRotatable3D, IScalable3D
		{
			Functionality::Event<> Dirtied;

			Transform();
			Transform(Ptr<Transform> parent);

			Transform(Float3 position, FQuaternion rotation = FQuaternion(II{}), Float3 scale = Float3(1.0f));
			Transform(Ptr<Transform> parent, Float3 position, FQuaternion rotation = FQuaternion(II{}), Float3 scale = Float3(1.0f));

			Float4x4 GetTransformationMatrix();
			Float4x4 GetInverseTransformationMatrix();

			// Should have world-relative equivalents for the below
			void SetPosition(const Float3& position) override;
			void AdjustPosition(const Float3& movement) override;
			Float3 GetPosition() const override;

			// Should have world-relative equivalents for the below
			void SetRotation(const FQuaternion& rotation) override;
			void AdjustRotation(const FQuaternion& rotation) override;
			FQuaternion GetRotation() const override;
			Float3x3 GetRotationMatrix() const;

			// Should have world-relative equivalents for the below
			void SetScale(const float& scale) override;
			void SetScale(const Float3& scale) override;
			void AdjustScale(const float& scale) override;
			void AdjustScale(const Float3& scale) override;
			Float3 GetScale() const override;

			void SetParent(Ptr<Transform> parent);
			Ptr<Transform> GetParent() const;

			void SetLocal(bool local);
			bool IsLocal() const;

			void Dirty(bool rotation = false);
			bool IsDirty() const;

		protected:
			Ptr<Transform> Parent = nullptr;
			Functionality::Delegate<> ParentDirtied;

			bool IsLocalTransformation = true;
			bool TransformationMatrixDirty = false;
			bool RotationMatrixDirty = false;

			Float3 Position;
			FQuaternion Rotation;
			Float3 Scale;

			Float3x3 LocalRotationMatrix;
			Float4x4 WorldTransformationMatrix;

			void RecalculateLocalRotationMatrix();
			Float4x4 LocalTransformationMatrix();
			void RecalculateWorldTransformationMatrix();
		};
	}
}