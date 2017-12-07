#pragma once

#include "Quaternion.h"

#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

#include "VectorFunctions.h"

#include "Core/Math/Headers/MathUtils.h"

#include "Core/Debugging/Headers/Declarations.h"

namespace Core
{
	namespace Math
	{
		// from rotation matrix
		/*
		template <typename T>
		Quaternion<T> QuatFromRotationMatrix(Matrix3x3<T> const& m)
		{
			// Leaving this empty for now - not convinced this method would ever (or should ever) be used.
			// should only really need the transformation TO matrices for shaders - the matrix itself is not as efficient otherwise
		}
		*/

		template <typename T>
		MatrixAxB<T, 3, 3> GetRotationMatrix(Quaternion<T> quaternion)
		{
			MatrixAxB<T, 3, 3> rotationMatrix;

			auto sqrW = Sqr(quaternion.W);
			auto sqrX = Sqr(quaternion.X);
			auto sqrY = Sqr(quaternion.Y);
			auto sqrZ = Sqr(quaternion.Z);

			auto inverse = 1 / (sqrX + sqrY + sqrZ + sqrW);

			rotationMatrix[0][0] = (sqrX - sqrY - sqrZ + sqrW) * inverse;
			rotationMatrix[1][1] = (-sqrX + sqrY - sqrZ + sqrW) * inverse;
			rotationMatrix[2][2] = (sqrX - sqrY + sqrZ + sqrW) * inverse;

			auto temp1 = quaternion.X * quaternion.Y;
			auto temp2 = quaternion.Z * quaternion.W;

			rotationMatrix[1][0] = 2.0f * (temp1 + temp2) * inverse;
			rotationMatrix[0][1] = 2.0f * (temp1 - temp2) * inverse;

			temp1 = quaternion.X * quaternion.Z;
			temp2 = quaternion.Y * quaternion.W;

			rotationMatrix[2][0] = 2.0f * (temp1 - temp2) * inverse;
			rotationMatrix[0][2] = 2.0f * (temp1 + temp2) * inverse;

			temp1 = quaternion.Y * quaternion.Z;
			temp2 = quaternion.X * quaternion.W;

			rotationMatrix[2][1] = 2.0f * (temp1 + temp2) * inverse;
			rotationMatrix[1][2] = 2.0f * (temp1 - temp2) * inverse;

			return rotationMatrix;
		}

		template <typename T>
		MatrixAxB<T, 4, 4> TransformationMatrix(Quaternion<T> quaternion)
		{
			MatrixAxB<T, 4, 4> rotationMatrix(GetRotationMatrix(quaternion));

			return rotationMatrix;
		}

		template <typename T>
		Quaternion<T> RotationBetweenVectors(Vector3<T> const& v1, Vector3<T> const& v2)
		{
			Quaternion<T> rotation;
			Vector3<T> crossProduct = CrossProduct(v1, v2);
			rotation.W = Sqrt(v1.Magnitude() * v2.Magnitude()) + Dot(v1, v2);
			rotation.X = crossProduct.X;
			rotation.Y = crossProduct.Y;
			rotation.Z = crossProduct.Z;

			rotation.Normalize();

			return rotation;
		}

		// rotate vector
		template <typename T>
		Vector3<T> RotateVectorBy(Vector3<T> const& v, Quaternion<T> const& q)
		{
			// conjugate of q
			auto qC = q.Inverse();
			qC *= v;
			qC *= q;

			// at this point qC.W == 0
			VERIFY(Within(qC.W, T(0.0f), T(0.001f)));
			return Vector3<T>(qC.X, qC.Y, qC.Z);
		}

		// several rotations (applied first to last)
		template <typename T, typename ...Ts>
		Vector3<T> RotateVectorBy(Vector3<T> const& v, Quaternion<T> const& firstQ, Ts ...restQs)
		{
			auto rotatedVector = RotateVectorBy(v, firstQ);
			return RotateVectorBy(rotatedVector, restQs...);
		}

		// undo rotation
		template <typename T>
		Vector3<T> UndoRotationBy(Vector3<T> const& v, Quaternion<T> const& q)
		{
			return RotateVectorBy(v, q.Inverse());
		}

		// undo several rotations (applied first to last)
		// NOTE: order of RotateVectorBy needs to be opposite this on to undo applied rotations
		template <typename T, typename ...Ts>
		Vector3<T> UndoRotationBy(Vector3<T> const& v, Quaternion<T> const& firstQ, Ts ...restQs)
		{
			auto rotatedVector = UndoRotationBy(v, firstQ);
			return UndoRotationBy(rotatedVector, restQs...);
		}

#if DEBUG
		template <typename T>
		String QuaternionString(Quaternion<T> const& q)
		{
			String quaternionInfo;

			quaternionInfo += "(";
			for (auto i = 0; i < 4; i++)
			{
				quaternionInfo += q[i];

				if (i != 3)
				{
					quaternionInfo += ", ";
				}
			}
			quaternionInfo += ")";

			return quaternionInfo;
		}
#endif
	}
}