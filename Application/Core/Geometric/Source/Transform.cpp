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
		{
			SetPosition(Float3(0.0f));
			SetRotation(FQuaternion(II{}));
			SetScale(Float3(II{}));
		}

		Transform::Transform(Float3 position, FQuaternion rotation, Float3 scale)
		{
			SetPosition(position);
			SetRotation(rotation);
			SetScale(scale);
		}

		Float4x4 Transform::GetTransformationMatrix() const
		{
			Float4x4 transformationMatrix = Float4x4(II{});

			// scale
			transformationMatrix.E1.X = Scale.X;
			transformationMatrix.E2.Y = Scale.Y;
			transformationMatrix.E3.Z = Scale.Z;

			// rotation
			transformationMatrix = Float4x4(RotationMatrix, Float4(0.0f, 0.0f, 0.0f, 1.0f)) * transformationMatrix;

			// position
			transformationMatrix.E4.X = Position.X;
			transformationMatrix.E4.Y = Position.Y;
			transformationMatrix.E4.Z = Position.Z;

			return transformationMatrix;
		}

		void Transform::SetPosition(const Float3& position)
		{
			Position = position;
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

			RecalculateRotationMatrix();
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
			return RotationMatrix;
		}

		void Transform::SetScale(const float& scale)
		{
			Scale = scale;
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

		void Transform::RecalculateRotationMatrix()
		{
			RotationMatrix = CalculateRotationMatrix(Rotation);
		}
	}
}