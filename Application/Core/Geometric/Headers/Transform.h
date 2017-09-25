#pragma once

#include "../../Headers/AllCore.h"

#include "../../Math/Headers/AllMath.h"

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
			Matrix4x4<T> transformationMatrix = MAtrix4x4<T>(Vector4<T>(Scale.X), Vector4<T>(Scale.Y), Vector4<T>(Scale.Z), Vector4<T>(II{}));
			// rotation
			transformationMatrix = Rotation.GetTransformationMatrix() * transformationMatrix;
			// position
			transformationMatrix.E4.XYZ = Position;

			return trransformationMatrix;
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

		Vector3<T> Scale(Vector3<T> scaleRatio)
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
};