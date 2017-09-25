#pragma once

#include "Quaternion.h"

#include "Vector3.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

#include "../../Debugging/Headers/Declarations.h"

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

	// get rotation 3x3 matrix
	template <typename T>
	Matrix3x3<T> RotationMatrixFromQuat(Quaternion<T> const& q)
	{
		T xw = q.X * q.W;
		T xx = q.X * q.X;
		T xy = q.X * q.Y;
		T xz = q.X * q.Z;

		T yw = q.Y * q.W;
		T yy = q.Y * q.Y;
		T yz = q.Y * q.Z;

		T zw = q.Z * q.W;
		T zz = q.Z * q.Z;

		Vector3<T> c1((T(1) - (T(2) * xx) - (T(2) * zz)), ((T(2) * xy) + (T(2) * zw)), ((T(2) * xz) - (T(2) * yw)));
		Vector3<T> c2(((T(2) * xy) - (T(2) * zw)), (T(1) - (T(2) * xx) - (T(2) * zz)), ((T(2) * yz) + (T(2) * xw)));
		Vector3<T> c3(((T(2) * xz) + (T(2) * yw)), ((T(2) * yz) - (T(2) * xw)), (T(1) - (T(2) * xx) - (T(2) * yy)));

		return Matrix3x3<T>(c1, c2, c3);
	}

	// get rotation 4x4 matrix
	template <typename T>
	Matrix4x4<T> TransformationMatrixFromQuat(Quaternion<T> const& q)
	{
		T xw = q.X * q.W;
		T xx = q.X * q.X;
		T xy = q.X * q.Y;
		T xz = q.X * q.Z;

		T yw = q.Y * q.W;
		T yy = q.Y * q.Y;
		T yz = q.Y * q.Z;

		T zw = q.Z * q.W;
		T zz = q.Z * q.Z;

		Vector4<T> c1((T(1) - (T(2) * xx) - (T(2) * zz)), ((T(2) * xy) + (T(2) * zw)), ((T(2) * xz) - (T(2) * yw)), T(0));
		Vector4<T> c2(((T(2) * xy) - (T(2) * zw)), (T(1) - (T(2) * xx) - (T(2) * zz)), ((T(2) * yz) + (T(2) * xw)), T(0));
		Vector4<T> c3(((T(2) * xz) + (T(2) * yw)), ((T(2) * yz) - (T(2) * xw)), (T(1) - (T(2) * xx) - (T(2) * yy)), T(0));
		Vector4<T> c4(T(0), T(0), T(0), T(1));

		return Matrix4x4<T>(c1, c2, c3, c4);
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
	template <typename T, typename Ts...>
	Vector3<T> RotateVectorBy(Vector3<T> const& v, Quaternion<T> const& firstQ, Ts ... restQs)
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
	template <typename T, typename Ts...>
	Vector3<T> UndoRotationBy(Vector3<T> const& v, Quaternion<T> const& firstQ, Ts ... restQs)
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
};