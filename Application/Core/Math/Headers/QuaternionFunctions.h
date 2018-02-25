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
		template <typename T, typename int A>
		T EulerAngle(Quaternion<T> const& q, Axis<A> axis)
		{
			switch (axis)
			{
			case X{}:
			{
				T sinX = T(2) * (q.W * q.X + q.Y * q.Z);
				T cosX = T(1) - T(2) * (q.X * q.X + q.Y * q.Y);

				return atan2(sinX, cosX);
				break;
			}
			case Y{}:
			{
				T sinY = T(2) * (q.W * q.Y - q.X * q.Z);
				if (fabs(sinY) >= T(1))
				{
					return copysign(T(PI_F) / T(2), sinY);
				}
				else
				{
					return asin(sinY);
				}
				break;
			}
			case Z{}:
			{
				T sinZ = T(2) * (q.W * q.Z + q.X * q.Y);
				T cosZ = T(1) - (T(2) * q.Y * q.Y + q.Z * q.Z);
				return atan2(sinZ, cosZ);

				break;
			}
			default:
				return T(0);
			}
		}

		template <typename T>
		Quaternion<T> Inverse(Quaternion<T> const& q)
		{
			return (Conjugate(q) / Magnitude(q));
		}

		template <typename T>
		Quaternion<T> Conjugate(Quaternion<T> const& q)
		{
			Quaternion<T> conjugate(q.W, -q.X, -q.Y, -q.Z);

			return conjugate;
		}

		template <typename T>
		T MagnitudeSqr(Quaternion<T> const& q)
		{
			auto magnitudeSqr = ((q.W * q.W) + (q.X * q.X) + (q.Y * q.Y) + (q.Z * q.Z));

			return magnitudeSqr;
		}

		template <typename T>
		T Magnitude(Quaternion<T> const& q)
		{
			return sqrt(MagnitudeSqr(q));
		}

		template <typename T>
		Quaternion<T> Normalize(Quaternion<T> const& q)
		{
			return (q / Magnitude(q));
		}

		/*
		template <typename T>
		Quaternion<T> QuatFromRotationMatrix(Matrix3x3<T> const& m)
		{
			// Leaving this empty for now - not convinced this method would ever (or should ever) be used.
			// should only really need the transformation TO matrices for shaders - the matrix itself is not as efficient otherwise
		}
		*/

		template <typename T>
		Matrix3x3<T> GetRotationMatrix(Quaternion<T> quaternion)
		{
			Matrix3x3<T> rotationMatrix;

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
		Matrix4x4<T> GetTransformationMatrix(Quaternion<T> quaternion)
		{
			Matrix4x4<T> rotationMatrix(GetRotationMatrix(quaternion), Vector4<T>(0, 0, 0, 1));

			return rotationMatrix;
		}

		template <typename T>
		Quaternion<T> RotationBetweenVectors(Vector3<T> const& v1, Vector3<T> const& v2)
		{
			Quaternion<T> rotation;

			// handle case where vectors are parrallel
			if (Dot(Normalize(v1), Normalize(v2)) >= (1.0f - Hundredth()))
			{
				return rotation;
			}

			Vector3<T> crossProduct = CrossProduct(v1, v2);
			rotation.W = Sqrt(MagnitudeSqr(v1) * MagnitudeSqr(v2)) + Dot(v1, v2);
			rotation.X = crossProduct.X;
			rotation.Y = crossProduct.Y;
			rotation.Z = crossProduct.Z;

			rotation = Normalize(rotation);

			return rotation;
		}

		// rotate vector
		template <typename T>
		Vector3<T> RotateNormalVectorBy(Vector3<T> const& v, Quaternion<T> const& q)
		{
			// conjugate of q
			auto qI = Inverse(q);
			qI *= v;
			qI *= q;

			Vector3<T> rV = Normalize(Vector3<T>(qI.X, qI.Y, qI.Z));

			return rV;
		}

		/*
			NOTE: This function does NOT preserve magnitude
		*/
		template <typename T>
		Vector3<T> RotateVectorBy(Vector3<T> const& v, Quaternion<T> const& q)
		{
			// conjugate of q
			auto qI = Inverse(q);
			qI *= v;
			qI *= q;

			Vector3<T> rV = Vector3<T>(qI.X, qI.Y, qI.Z);

			return rV;
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
				quaternionInfo += std::to_string(q[i]);

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