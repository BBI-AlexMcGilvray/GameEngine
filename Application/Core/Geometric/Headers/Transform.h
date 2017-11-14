#pragma once

#include "Core/Math/Headers/MathDefs.h"

#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

using namespace Core::Math;

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct TransformBase
		{
			TransformBase()
				: Position(II{}), Rotation(II{}), Scale(II{})
			{}

			TransformBase(Vector3<T> position, Quaternion<T> rotation, Vector3<T> scale)
				: Position(position), Rotation(rotation), Scale(scale)
			{}

			Matrix4x4<T> GetTransformationMatrix()
			{
				// scale
				Matrix4x4<T> transformationMatrix = Matrix4x4<T>(Vector4<T>(Scale.X), Vector4<T>(Scale.Y), Vector4<T>(Scale.Z), Vector4<T>(II{}));
				// rotation
				transformationMatrix = TransformationMatrixFromQuat(Rotation) * transformationMatrix;
				// position
				transformationMatrix.E4.X = Position.X;
				transformationMatrix.E4.Y = Position.Y;
				transformationMatrix.E4.Z = Position.Z;

				return transformationMatrix;
			}

			Quaternion<T> Rotate(Quaternion<T> additionalRotation)
			{
				Rotation = additionalRotation * Rotation;

				return Rotation;
			}

			Vector3<T> Move(Vector3<T> movement)
			{
				Position += movement;

				return Position;
			}

			void SetScale(Vector3<T> scale)
			{
				Scale = scale;
			}

			Vector3<T> ApplyScale(Vector3<T> scaleRatio)
			{
				Scale *= scaleRatio;

				return Scale;
			}

		public:
			Vector3<T> Position;
			Quaternion<T> Rotation;
			Vector3<T> Scale;
		};

		/*	TYPE DEFS	*/
		using Transform = TransformBase<float>;
	}
}