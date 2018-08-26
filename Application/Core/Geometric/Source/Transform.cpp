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

		Float3 Transform::AdjustPosition(Float3 const& movement)
		{
			return SetPosition(Position + movement);
		}

		Float3 Transform::SetPosition(Float3 const& position)
		{
			Position = position;

			return Position;
		}

		Float3 Transform::GetPosition() const
		{
			return Position;
		}

		FQuaternion Transform::AdjustRotatation(FQuaternion const& rotation)
		{
			return SetRotation(rotation * Rotation);
		}

		FQuaternion Transform::SetRotation(FQuaternion const& rotation)
		{
			Rotation = rotation;

			RecalculateRotationMatrix();

			return Rotation;
		}

		FQuaternion Transform::GetRotation() const
		{
			return Rotation;
		}

		Float3x3 Transform::GetRotationMatrix() const
		{
			return RotationMatrix;
		}

		Float3 Transform::AdjustScale(Float3 const& scale)
		{
			return SetScale(Scale * scale);
		}

		Float3 Transform::SetScale(Float3 const& scale)
		{
			Scale = scale;

			return Scale;
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