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

			Transform(Float3 position, FQuaternion rotation = FQuaternion(II{}), Float3 scale = Float3(1.0f), bool settingLocal = false);
			Transform(Ptr<Transform> parent, Float3 position, FQuaternion rotation = FQuaternion(II{}), Float3 scale = Float3(1.0f), bool settingLocal = false);

			// parent-relative
			Float4x4 GetLocalTransformationMatrix();
			Float4x4 GetInverseLocalTransformationMatrix();
			// world-relative
			Float4x4 GetWorldTransformationMatrix();
			Float4x4 GetWorldInverseTransformationMatrix();

			// parent-relative
			void SetPosition(const Float3& position) override;
			void AdjustPosition(const Float3& movement) override;
			Float3 GetPosition() const override;
			// world-relative
			void SetWorldPosition(const Float3& position);
			void AdjustWorldPosition(const Float3& movement);
			Float3 GetWorldPosition();

			// parent-relative
			void SetRotation(const FQuaternion& rotation) override;
			void AdjustRotation(const FQuaternion& rotation) override;
			FQuaternion GetRotation() const override;
			// world-relative
			void SetWorldRotation(const FQuaternion& rotation);
			void AdjustWorldRotation(const FQuaternion& rotation);
			FQuaternion GetWorldRotation();

			// parent-relative
			void SetScale(const float& scale) override;
			void SetScale(const Float3& scale) override;
			void AdjustScale(const float& scale) override;
			void AdjustScale(const Float3& scale) override;
			Float3 GetScale() const override;
			// world-relative
			void SetWorldScale(const float& scale);
			void SetWorldScale(const Float3& scale);
			void AdjustWorldScale(const float& scale);
			void AdjustWorldScale(const Float3& scale);
			Float3 GetWorldScale();

			void SetParent(Ptr<Transform> parent);
			Ptr<Transform> GetParent() const;

			void Dirty(bool rotation = false);
			bool IsDirty() const;

		protected:
			Ptr<Transform> Parent = nullptr;
			Functionality::Delegate<> ParentDirtied;

			bool RotationMatrixDirty = false;
			bool LocalTransformationMatrixDirty = false;
			bool WorldTransformationMatrixDirty = false;
			bool WorldInformationDirty = false;

			// parent-relative
			Float3 Position;
			FQuaternion Rotation;
			Float3 Scale;

			// world-relative
			Float3 WorldPosition;
			FQuaternion WorldRotation;
			Float3 WorldScale;

			Float3x3 LocalRotationMatrix;

			Float4x4 LocalTransformationMatrix;
			Float4x4 WorldTransformationMatrix;

			Float3x3 GetRotationMatrix();

			void RecalculateLocalRotationMatrix();
			void RecalculateLocalTransformationMatrix();
			void RecalculateWorldTransformationMatrix();

			void RecalculateWorldInformation();
		};
	}
}