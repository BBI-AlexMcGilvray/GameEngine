#pragma once

#include "Core/Math/Headers/MathDefs.h"

#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"
#include "Core/Math/Headers/MatrixFunctions.h"

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
			constexpr TransformBase()
			{
				SetPosition(Vector3<T>(II{}));
				SetRotation(Quaternion<T>(II{}));
				SetScale(Vector3<T>(II{}));
			}

			constexpr TransformBase(Vector3<T> position, Quaternion<T> rotation = Quaternion<T>(II{}), Vector3<T> scale = Vector3<T>(T(1)))
			{
				SetPosition(position);
				SetRotation(rotation);
				SetScale(scale);
			}

			virtual Matrix4x4<T> GetTransformationMatrix() const
			{
				// scale
				Matrix4x4<T> transformationMatrix = Matrix4x4<T>(Vector4<T>(Scale.X, T(0), T(0), T(0)), Vector4<T>(T(0), Scale.Y, T(0), T(0)), Vector4<T>(T(0), T(0), Scale.Z, T(0)), Vector4<T>(T(0), T(0), T(0), II{}));
				//std::cout << "Scale: " << VectorString(Scale) << std::endl;
				//std::cout << "Transformation Matrix (Scale): " << MatrixString(transformationMatrix) << std::endl;

				// rotation
				transformationMatrix = Float4x4(RotationMatrix, Float4(T(0), T(0), T(0), T(1))) * transformationMatrix;
				//std::cout << "Rotation: " << QuaternionString(Rotation) << std::endl;
				//std::cout << "Transformation Matrix: " << MatrixString(transformationMatrix) << std::endl;
				//std::cout << "Transformation Matrix (Rotation): " << MatrixString(transformationMatrix) << std::endl;

				// position
				transformationMatrix.E4.X = Position.X;
				transformationMatrix.E4.Y = Position.Y;
				transformationMatrix.E4.Z = Position.Z;
				//std::cout << "Position: " << VectorString(Position) << std::endl;
				//std::cout << "Transformation Matrix (Position): " << MatrixString(transformationMatrix) << std::endl;

				return transformationMatrix;
			}

			virtual Vector3<T> AdjustPosition(Vector3<T> const& movement)
			{
				return SetPosition(Position + movement);
			}

			virtual Vector3<T> SetPosition(Vector3<T> const& position)
			{
				Position = position;

				return Position;
			}

			virtual Vector3<T> GetPosition() const
			{
				return Position;
			}

			virtual Quaternion<T> AdjustRotatation(Quaternion<T> const& rotation)
			{
				return SetRotation(rotation * Rotation);
			}

			virtual Quaternion<T> SetRotation(Quaternion<T> const& rotation)
			{
				Rotation = rotation;

				RecalculateRotationMatrix();

				return Rotation;
			}

			virtual Quaternion<T> GetRotation() const
			{
				return Rotation;
			}

			virtual Vector3<T> AdjustScale(Vector3<T> const& scale)
			{
				return SetScale(Scale * scale);
			}

			virtual Vector3<T> SetScale(Vector3<T> const& scale)
			{
				Scale = scale;

				return Scale;
			}

			virtual Vector3<T> GetScale() const
			{
				return Scale;
			}

		protected:
			Vector3<T> Position;
			Quaternion<T> Rotation;
			Vector3<T> Scale;

			Matrix3x3<T> RotationMatrix;

			virtual void RecalculateRotationMatrix()
			{
				RotationMatrix = GetRotationMatrix(Rotation);
			}
		};

		/*	TYPE DEFS	*/
		using Transform = TransformBase<float>;
	}
}