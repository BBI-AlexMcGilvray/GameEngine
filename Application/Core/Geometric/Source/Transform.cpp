#pragma once

#include "Core/Geometric/Headers/Transform.h"

#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

using namespace Core::Math;

namespace Core
{
	namespace Geometric
	{
		Transform::Transform()
			: Transform(nullptr)
		{}

		Transform::Transform(Ptr<Transform> parent)
			: Transform(parent, Float3(0.0f), FQuaternion(II{}), Float3(II{}))
		{}

		Transform::Transform(Float3 position, FQuaternion rotation, Float3 scale, bool settingLocal)
			: Transform(nullptr, position, rotation, scale, settingLocal)
		{}

		Transform::Transform(Ptr<Transform> parent, Float3 position, FQuaternion rotation, Float3 scale, bool settingLocal)
			: ParentDirtied([this]
		{
			Dirty();
			return false;
		})
		{
			SetParent(parent);

			if (settingLocal)
			{
				SetPosition(position);
				SetRotation(rotation);
				SetScale(scale);
			}
			else
			{
				SetWorldPosition(position);
				SetWorldRotation(rotation);
				SetWorldScale(scale);
			}
		}

		Float4x4 Transform::GetLocalTransformationMatrix()
		{
			RecalculateLocalTransformationMatrix();

			return LocalTransformationMatrix;
		}

		Float4x4 Transform::GetInverseLocalTransformationMatrix()
		{
			return Math::Inverse(GetLocalTransformationMatrix());
		}

		Float4x4 Transform::GetWorldTransformationMatrix()
		{
			RecalculateWorldTransformationMatrix();

			return WorldTransformationMatrix;
		}

		Float4x4 Transform::GetWorldInverseTransformationMatrix()
		{
			return Math::Inverse(GetWorldTransformationMatrix());
		}

		void Transform::SetPosition(const Float3& position)
		{
			Position = position;
			Dirty();
		}

		void Transform::AdjustPosition(const Float3& movement)
		{
			SetPosition(Position + movement);
		}

		Float3 Transform::GetPosition() const
		{
			return Position;
		}

		void Transform::SetWorldPosition(const Float3& position)
		{
			if (Parent == nullptr)
			{
				SetPosition(position);
			}
			else
			{
				Float3 finalPosition = (Parent->GetWorldInverseTransformationMatrix() * Float4(position, 1.0f)).XYZ;
				SetPosition(finalPosition);
			}
		}

		void Transform::AdjustWorldPosition(const Float3& movement)
		{
			// adjusting world is the same as adjusting local
			AdjustPosition(movement);
		}

		Float3 Transform::GetWorldPosition()
		{
			RecalculateWorldInformation();

			return WorldPosition;
		}

		void Transform::SetRotation(const FQuaternion& rotation)
		{
			Rotation = rotation;
			Dirty(true);
		}

		void Transform::AdjustRotation(const FQuaternion& rotation)
		{
			SetRotation(rotation * Rotation);
		}

		FQuaternion Transform::GetRotation() const
		{
			return Rotation;
		}

		void Transform::SetWorldRotation(const FQuaternion& rotation)
		{
			FQuaternion ParentRotation = (Parent != nullptr) ? Parent->GetWorldRotation() : FQuaternion();
			FQuaternion finalRotation = rotation / ParentRotation;

			SetRotation(finalRotation);
		}

		void Transform::AdjustWorldRotation(const FQuaternion& rotation)
		{
			// adjusting world is the same as adjusting local
			AdjustRotation(rotation);
		}

		FQuaternion Transform::GetWorldRotation()
		{
			RecalculateWorldInformation();

			return WorldRotation;
		}

		void Transform::SetScale(const float& scale)
		{
			Scale = scale;
			Dirty();
		}

		void Transform::SetScale(const Float3& scale)
		{
			Scale = scale;
			Dirty();
		}

		void Transform::AdjustScale(const float& scale)
		{
			SetScale(Scale * scale);
		}

		void Transform::AdjustScale(const Float3& scale)
		{
			SetScale(Scale * scale);
		}

		Float3 Transform::GetScale() const
		{
			return Scale;
		}

		void Transform::SetWorldScale(const float& scale)
		{
			SetWorldScale(Float3(scale));
		}

		void Transform::SetWorldScale(const Float3& scale)
		{
			Float3 ParentScale = (Parent != nullptr) ? Parent->GetWorldScale() : Float3(1.0f);

			SetScale(scale / ParentScale);
		}

		void Transform::AdjustWorldScale(const float& scale)
		{
			AdjustWorldScale(Float3(scale));
		}

		void Transform::AdjustWorldScale(const Float3& scale)
		{
			// adjusting world is the same as adjusting local
			AdjustScale(scale);
		}

		Float3 Transform::GetWorldScale()
		{
			RecalculateWorldInformation();

			return WorldScale;
		}

		void Transform::SetParent(Ptr<Transform> parent)
		{
			if (Parent == parent)
			{
				return;
			}

			Float3 oldWorldPosition = GetWorldPosition();
			FQuaternion oldWorldRotation = GetWorldRotation();
			Float3 oldWorldScale = GetWorldScale();

			if (Parent != nullptr)
			{
				Parent->Dirtied -= ParentDirtied;
			}

			Parent = parent;

			if (Parent != nullptr)
			{
				Parent->Dirtied += ParentDirtied;
			}

			Dirty();

			SetWorldPosition(oldWorldPosition);
			SetWorldRotation(oldWorldRotation);
			SetWorldScale(oldWorldScale);
		}

		Ptr<Transform> Transform::GetParent() const
		{
			return Parent;
		}

		void Transform::Dirty(bool rotation)
		{
			RotationMatrixDirty |= rotation;
			WorldTransformationMatrixDirty = true;
			LocalTransformationMatrixDirty = true;
			WorldInformationDirty = true;

			Dirtied();
		}

		bool Transform::IsDirty() const
		{
			return WorldInformationDirty || WorldTransformationMatrixDirty || LocalTransformationMatrixDirty || RotationMatrixDirty;
		}

		Float3x3 Transform::GetRotationMatrix()
		{
			RecalculateLocalRotationMatrix();

			return LocalRotationMatrix;
		}

		void Transform::RecalculateLocalRotationMatrix()
		{
			if (!RotationMatrixDirty)
			{
				return;
			}

			LocalRotationMatrix = CalculateRotationMatrix(Rotation);
			RotationMatrixDirty = false;
		}

		void Transform::RecalculateLocalTransformationMatrix()
		{
			if (!IsDirty())
			{
				return;
			}

			LocalTransformationMatrix = Float4x4(II{});

			// scale
			LocalTransformationMatrix.E1.X = Scale.X;
			LocalTransformationMatrix.E2.Y = Scale.Y;
			LocalTransformationMatrix.E3.Z = Scale.Z;

			// rotation
			LocalTransformationMatrix = Float4x4(GetRotationMatrix(), Float4(0.0f, 0.0f, 0.0f, 1.0f)) * LocalTransformationMatrix;

			// position
			LocalTransformationMatrix.E4.X = Position.X;
			LocalTransformationMatrix.E4.Y = Position.Y;
			LocalTransformationMatrix.E4.Z = Position.Z;

			LocalTransformationMatrixDirty = false;
		}

		void Transform::RecalculateWorldTransformationMatrix()
		{
			if (!IsDirty())
			{
				return;
			}

			Float4x4 parentTransformationMatrix = (Parent == nullptr) ? Float4x4(II{}) : Parent->GetWorldTransformationMatrix();

			WorldTransformationMatrix = parentTransformationMatrix * GetLocalTransformationMatrix();

			WorldTransformationMatrixDirty = false;
		}

		void Transform::RecalculateWorldInformation()
		{
			if (!IsDirty())
			{
				return;
			}

			TransformationMatrixDecomposition(GetWorldTransformationMatrix(), WorldPosition, WorldScale, WorldRotation);

			WorldInformationDirty = false;
		}
	}
}