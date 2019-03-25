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

		Transform::Transform(Float3 position, FQuaternion rotation, Float3 scale)
			: Transform(nullptr, position, rotation, scale)
		{}

		Transform::Transform(Ptr<Transform> parent, Float3 position, FQuaternion rotation, Float3 scale)
			: ParentDirtied([this]
		{
			Dirty();
			return false;
		})
		{
			SetParent(parent);
			SetPosition(position);
			SetRotation(rotation);
			SetScale(scale);
		}

		Float4x4 Transform::GetTransformationMatrix()
		{
			if (IsDirty())
			{
				RecalculateWorldTransformationMatrix();
			}

			return WorldTransformationMatrix;
		}

		Float4x4 Transform::GetInverseTransformationMatrix() const
		{
			/*
			// Reference: http://www.ntu.edu.sg/home/ehchua/programming/opengl/cg_basicstheory.html
			Float4x4 inverseTransformationMatrix(II{});

			// rotation
			Float3x3 rotationMatrix = LocalRotationMatrix;
			Float4x4 inverseRotationMatrix = Float4x4(Transpose(rotationMatrix), Float4(0.0f, 0.0f, 0.0f, 1.0f));
			inverseTransformationMatrix = inverseRotationMatrix * inverseTransformationMatrix; // can probably just set the transformation matrix to tbe the inverse rotation matrix, doing this for clarity

			// translation
			//Float4 rotatedPosition = inverseRotationMatrix * Float4(-1.0f * Position, 1.0f);
			//transformationMatrix.E4 = rotatedPosition;
			inverseTransformationMatrix.E4 = Float4(-Dot(rotationMatrix.E1, Position), -Dot(rotationMatrix.E2, Position), -Dot(rotationMatrix.E3, Position), 1.0f);

			// projection
			inverseTransformationMatrix = inverseTransformationMatrix;

			return inverseTransformationMatrix;
			*/

			return Math::Inverse(WorldTransformationMatrix);
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

		Float3x3 Transform::GetRotationMatrix() const
		{
			return LocalRotationMatrix;
		}

		void Transform::SetScale(const float& scale)
		{
			Scale = scale;
			Dirty();
		}

		void Transform::SetScale(const Float3& scale)
		{
			Scale = scale;
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

		void Transform::SetLocal(bool local)
		{
			IsLocalTransformation = local;
			if (!IsLocalTransformation)
			{
				SetParent(nullptr);
			}

			Dirty();
		}

		bool Transform::IsLocal() const
		{
			return IsLocalTransformation;
		}

		void Transform::SetParent(Ptr<Transform> parent)
		{
			if (Parent == parent)
			{
				return;
			}

			if (Parent != nullptr)
			{
				//Parent->Dirtied -= ParentDirtied;
			}

			Parent = parent;

			if (Parent != nullptr)
			{
				//Parent->Dirtied += ParentDirtied;
			}

			Dirty();
		}

		Ptr<Transform> Transform::GetParent() const
		{
			return Parent;
		}

		void Transform::Dirty(bool rotation)
		{
			TransformationMatrixDirty = true;
			RotationMatrixDirty |= rotation;

			Dirtied();
		}

		bool Transform::IsDirty() const
		{
			return TransformationMatrixDirty || RotationMatrixDirty;
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

		Float4x4 Transform::LocalTransformationMatrix()
		{
			Float4x4 localTransformationMatrix = Float4x4(II{});

			// scale
			localTransformationMatrix.E1.X = Scale.X;
			localTransformationMatrix.E2.Y = Scale.Y;
			localTransformationMatrix.E3.Z = Scale.Z;

			// rotation
			localTransformationMatrix = Float4x4(LocalRotationMatrix, Float4(0.0f, 0.0f, 0.0f, 1.0f)) * localTransformationMatrix;

			// position
			localTransformationMatrix.E4.X = Position.X;
			localTransformationMatrix.E4.Y = Position.Y;
			localTransformationMatrix.E4.Z = Position.Z;

			return localTransformationMatrix;
		}

		void Transform::RecalculateWorldTransformationMatrix()
		{
			if (!IsDirty())
			{
				return;
			}

			if (RotationMatrixDirty)
			{
				RecalculateLocalRotationMatrix();
			}

			Float4x4 localTransformationMatrix = LocalTransformationMatrix();
			Float4x4 parentTransformationMatrix = (Parent == nullptr || !IsLocal()) ? Float4x4(II{}) : Parent->GetTransformationMatrix();

			WorldTransformationMatrix = parentTransformationMatrix * localTransformationMatrix;

			TransformationMatrixDirty = false;
		}
	}
}