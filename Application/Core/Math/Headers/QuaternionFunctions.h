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
			return q.Inverse();
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

		template <typename T>
		Quaternion<T> QuatFromRotationMatrix(Matrix3x3<T> const& m)
		{
			/*
				Note: Code taken from here: http://www.euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm

				but changed because our matrices are column-major, NOT row-major.
			*/
			Quaternion<T> quaternion;

			T trace = m[0][0] + m[1][1] + m[2][2];

			T root = (T(1) / T(2)) / Sqrt(trace + T(1));

			if (trace > 0)
			{
				quaternion.W = (T(1) / T(4)) / root;
				quaternion.X = (m[1][2] - m[2][1]) * root;
				quaternion.Y = (m[2][0] - m[0][2]) * root;
				quaternion.Z = (m[0][1] - m[1][0]) * root;
			}
			else
			{
				if (m[0][0] > m[1][1] && m[0][0] > m[2][2])
				{
					root = T(2) * Sqrt(T(1) + m[0][0] - m[1][1] - m[2][2]);

					quaternion.W = (m[1][2] - m[2][1]) / root;
					quaternion.X = (T(1) / T(4)) * root;
					quaternion.Y = (m[1][0] + m[0][1]) / root;
					quaternion.Z = (m[2][0] + m[0][2]) / root;
				}
				else if (m[1][1] > m[2][2])
				{
					root = T(2) * Sqrt(T(1) + m[1][1] - m[0][0] - m[2][2]);

					quaternion.W = (m[2][0] - m[0][2]) / root;
					quaternion.X = (m[1][0] + m[0][1]) / root;
					quaternion.Y = (T(1) / T(4)) * root;
					quaternion.Z = (m[2][1] + m[1][2]) / root;
				}
				else
				{
					root = T(2) * Sqrt(T(1) + m[2][2] - m[0][0] - m[1][1]);

					quaternion.W = (m[0][1] - m[1][0]) / root;
					quaternion.X = (m[2][0] + m[0][2]) / root;
					quaternion.Y = (m[2][1] + m[1][2]) / root;
					quaternion.Z = (T(1) / T(4)) * root;
				}
			}

			return quaternion;
		}

		template <typename T>
		Matrix3x3<T> CalculateRotationMatrix(const Quaternion<T>& quaternion)
		{
			Matrix3x3<T> rotationMatrix;

			auto sqrW = Sqr(quaternion.W);
			auto sqrX = Sqr(quaternion.X);
			auto sqrY = Sqr(quaternion.Y);
			auto sqrZ = Sqr(quaternion.Z);

			auto inverse = T(1) / (sqrX + sqrY + sqrZ + sqrW);

			rotationMatrix[0][0] = (T(1) - (T(2) * (sqrY + sqrZ))) * inverse;
			rotationMatrix[0][1] = (T(2) * ((quaternion.X * quaternion.Y) + (quaternion.Z * quaternion.W))) * inverse;
			rotationMatrix[0][2] = (T(2) * ((quaternion.X * quaternion.Z) - (quaternion.Y * quaternion.W))) * inverse;

			rotationMatrix[1][0] = (T(2) * ((quaternion.X * quaternion.Y) - (quaternion.Z * quaternion.W))) * inverse;
			rotationMatrix[1][1] = (T(1) - (T(2) * (sqrX + sqrZ))) * inverse;
			rotationMatrix[1][2] = (T(2) * ((quaternion.Y * quaternion.Z) + (quaternion.X * quaternion.W))) * inverse;

			rotationMatrix[2][0] = (T(2) * ((quaternion.X * quaternion.Z) + (quaternion.Y * quaternion.W))) * inverse;
			rotationMatrix[2][1] = (T(2) * ((quaternion.Y * quaternion.Z) - (quaternion.X * quaternion.W))) * inverse;
			rotationMatrix[2][2] = (T(1) - (T(2) * (sqrX + sqrY))) * inverse;

			return rotationMatrix;
		}

		template <typename T>
		Matrix4x4<T> CalculateTransformationMatrix(Quaternion<T> quaternion)
		{
			Matrix4x4<T> rotationMatrix(CalculateTransformationMatrix(quaternion), Vector4<T>(0, 0, 0, 1));

			return rotationMatrix;
		}

		template <typename T, int A = 0>
		Quaternion<T> RotationBetweenVectors(Vector3<T> const& v1, Vector3<T> const& v2, const Axis<A>& fallbackAxis = XAxis())
		{
			Quaternion<T> rotation;

			Vector3<T> nV1 = Normalize(v1);
			Vector3<T> nV2 = Normalize(v2);

			T dot = Dot(nV1, nV2);

			if (dot >= (T(1) - Hundredth()))
			{
				return rotation;
			}
			if (dot <= Hundredth() - T(1))
			{
				return Quaternion<T>(Rad(PI_F), fallbackAxis);
			}

			T sqrt = Sqrt((T(1) + dot) * T(2));
			T inverseSqrt = T(1) / sqrt;

			Vector3<T> crossProduct = CrossProduct(nV1, nV2);

			rotation.X = crossProduct.X * inverseSqrt;
			rotation.Y = crossProduct.Y * inverseSqrt;
			rotation.Z = crossProduct.Z * inverseSqrt;

			rotation.W = sqrt * 0.5f;

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

		template <typename T>
		Vector2<T> RotateNormalVectorBy(Vector2<T> const& v, Quaternion<T> const& q)
		{
			return RotateNormalVectorBy(Vector3<T>(v), q).XY;
		}

		/*
			NOTE: This function DOES preserve magnitude 
		*/
		template <typename T>
		Vector3<T> RotateVectorBy(Vector3<T> const& v, Quaternion<T> const& q)
		{
			T vMagnitude = Magnitude(v);

			// conjugate of q
			auto rotatedV = q;
			Quaternion<T> vAsQuaternion = Quaternion<T>(v);
			rotatedV *= vAsQuaternion;
			rotatedV *= q.Inverse();

			Vector3<T> rV = Vector3<T>(rotatedV.X * vMagnitude, rotatedV.Y * vMagnitude, rotatedV.Z * vMagnitude);

			return rV;
		}

		template <typename T>
		Vector2<T> RotateVectorBy(Vector2<T> const& v, Quaternion<T> const& q)
		{
			return RotateVectorBy(Vector3<T>(v), q).XY;
		}

		// several rotations (applied first to last)
		template <typename T, typename ...Ts>
		Vector3<T> RotateVectorBy(Vector3<T> const& v, Quaternion<T> const& firstQ, Ts ...restQs)
		{
			auto rotatedVector = RotateVectorBy(v, firstQ);
			return RotateVectorBy(rotatedVector, restQs...);
		}

		template <typename T, typename ...Ts>
		Vector2<T> RotateVectorBy(Vector2<T> const& v, Quaternion<T> const& firstQ, Ts ...restQs)
		{
			auto rotatedVector = RotateVectorBy(v, firstQ);
			return RotateVectorBy(rotatedVector, restQs...).XY;
		}

		// undo rotation
		template <typename T>
		Vector3<T> UndoRotationBy(Vector3<T> const& v, Quaternion<T> const& q)
		{
			return RotateVectorBy(v, q.Inverse());
		}

		template <typename T>
		Vector2<T> UndoRotationBy(Vector2<T> const& v, Quaternion<T> const& q)
		{
			return UndoRotationBy(Vector3<T>(v), q).XY;
		}

		// undo several rotations (applied first to last)
		// NOTE: order of RotateVectorBy needs to be opposite this on to undo applied rotations
		template <typename T, typename ...Ts>
		Vector3<T> UndoRotationBy(Vector3<T> const& v, Quaternion<T> const& firstQ, Ts ...restQs)
		{
			auto rotatedVector = UndoRotationBy(v, firstQ);
			return UndoRotationBy(rotatedVector, restQs...);
		}

		template <typename T, typename ...Ts>
		Vector2<T> UndoRotationBy(Vector2<T> const& v, Quaternion<T> const& firstQ, Ts ...restQs)
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