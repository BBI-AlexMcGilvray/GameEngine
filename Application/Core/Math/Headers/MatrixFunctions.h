#pragma once

#include "Matrix.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

#include "VectorFunctions.h"
#include "QuaternionFunctions.h"

namespace Core
{
	namespace Math
	{
		template <typename T, typename int A, typename int B>
		MatrixAxB<T, B, A> Transpose(MatrixAxB<T, A, B> const& m)
		{
			MatrixAxB<T, B, A> mTranspose;

			for (int a = 0; a < A; a++)
			{
				for (int b = 0; b < B; b++)
				{
					mTranspose[b][a] = m[a][b];
				}
			}

			return mTranspose;
		}

		template <typename T>
		T Determinant(Matrix2x2<T> m)
		{
			return (m.E1.X * m.E2.Y) - (m.E1.Y * m.E2.X);
		}

		template <typename T>
		T Determinant(Matrix3x3<T> m)
		{
			T det1 = m.E1.X * Determinant(Matrix2x2<T>(m.E2.Y, m.E2.Z, m.E3.Y, m.E3.Z));
			T det2 = m.E1.Y * Determinant(Matrix2x2<T>(m.E2.X, m.E2.Z, m.E3.X, m.E3.Z));
			T det3 = m.E1.Z * Determinant(Matrix2x2<T>(m.E2.X, m.E2.Y, m.E3.X, m.E3.Y));

			return (det1 + det2 + det3);
		}

		template <typename T>
		Matrix2x2<T> Inverse(Matrix2x2<T> const& m)
		{
			T det = Determinant(m);

			Matrix2x2<T> mInverse(m.E2.Y, -m.E1.Y, -m.E2.X, m.E1.X);

			return (mInverse / det);
		}

		template <typename T>
		Matrix3x3<T> Inverse(Matrix3x3<T> const& m)
		{
			T det = Determinant(m);

			T e1X = Determinant(Matrix2x2<T>(m.E2.Y, m.E2.Z, m.E3.Y, m.E3.Z));
			T e1Y = -Determinant(Matrix2x2<T>(m.E2.X, m.E2.Z, m.E3.X, m.E3.Z));
			T e1Z = Determinant(Matrix2x2<T>(m.E2.X, m.E2.Y, m.E3.X, m.E3.Y));

			T e2X = -Determinant(Matrix2x2<T>(m.E1.Y, m.E1.Z, m.E3.Y, m.E3.Z));
			T e2Y = Determinant(Matrix2x2<T>(m.E1.X, m.E1.Z, m.E3.X, m.E3.Z));
			T e2Z = -Determinant(Matrix2x2<T>(m.E1.X, m.E1.Y, m.E3.X, m.E3.Y));

			T e3X = Determinant(Matrix2x2<T>(m.E1.Y, m.E1.Z, m.E2.Y, m.E2.Z));
			T e3Y = -Determinant(Matrix2x2<T>(m.E1.X, m.E1.Z, m.E2.X, m.E2.Z));
			T e3Z = Determinant(Matrix2x2<T>(m.E1.X, m.E1.Y, m.E2.X, m.E2.Y));

			Matrix3x3<T> mInverse(e1X, e1Y, e1Z, e2X, e2Y, e2Z, e3X, e3Y, e3Z);

			return (mInverse / det);
		}

		// Taken from Ogre3D (https://bitbucket.org/sinbad/ogre/src/67a17b4dc55037f9d816df3fdfc80f6b1365f7ae/OgreMain/src/OgreMatrix4.cpp?at=default&fileviewer=file-view-default)
		// but some changes since they are row-major and we are column-major
		template <typename T>
		Matrix4x4<T> Inverse(Matrix4x4<T> const& m)
		{
			T m00 = m[0][0], m01 = m[1][0], m02 = m[2][0], m03 = m[3][0];
			T m10 = m[0][1], m11 = m[1][1], m12 = m[2][1], m13 = m[3][1];
			T m20 = m[0][2], m21 = m[1][2], m22 = m[2][2], m23 = m[3][2];
			T m30 = m[0][3], m31 = m[1][3], m32 = m[2][3], m33 = m[3][3];

			T v0 = m20 * m31 - m21 * m30;
			T v1 = m20 * m32 - m22 * m30;
			T v2 = m20 * m33 - m23 * m30;
			T v3 = m21 * m32 - m22 * m31;
			T v4 = m21 * m33 - m23 * m31;
			T v5 = m22 * m33 - m23 * m32;

			T t00 = +(v5 * m11 - v4 * m12 + v3 * m13);
			T t10 = -(v5 * m10 - v2 * m12 + v1 * m13);
			T t20 = +(v4 * m10 - v2 * m11 + v0 * m13);
			T t30 = -(v3 * m10 - v1 * m11 + v0 * m12);

			T invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

			T d00 = t00 * invDet;
			T d10 = t10 * invDet;
			T d20 = t20 * invDet;
			T d30 = t30 * invDet;

			T d01 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			T d11 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			T d21 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			T d31 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m10 * m31 - m11 * m30;
			v1 = m10 * m32 - m12 * m30;
			v2 = m10 * m33 - m13 * m30;
			v3 = m11 * m32 - m12 * m31;
			v4 = m11 * m33 - m13 * m31;
			v5 = m12 * m33 - m13 * m32;

			T d02 = +(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			T d12 = -(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			T d22 = +(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			T d32 = -(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			v0 = m21 * m10 - m20 * m11;
			v1 = m22 * m10 - m20 * m12;
			v2 = m23 * m10 - m20 * m13;
			v3 = m22 * m11 - m21 * m12;
			v4 = m23 * m11 - m21 * m13;
			v5 = m23 * m12 - m22 * m13;

			T d03 = -(v5 * m01 - v4 * m02 + v3 * m03) * invDet;
			T d13 = +(v5 * m00 - v2 * m02 + v1 * m03) * invDet;
			T d23 = -(v4 * m00 - v2 * m01 + v0 * m03) * invDet;
			T d33 = +(v3 * m00 - v1 * m01 + v0 * m02) * invDet;

			return Matrix4x4<T>(
				d00, d10, d20, d30,
				d01, d11, d21, d31,
				d02, d12, d22, d32,
				d03, d13, d23, d33);
		}

		// Vector * Matrix
		template <typename T, typename int A, typename int B>
		VectorA<T, A> Multiply(VectorA<T, B> const& v, MatrixAxB<T, A, B> const& m)
		{
			VectorA<T, A> newV;
			for (auto i = 0; i < A; i++)
			{
				newV[i] = v.Dot(m[i]);
			}

			return newV;
		}

		// Matrix * Vector
		template <typename T, typename int A, typename int B>
		VectorA<T, B> Multiply(MatrixAxB<T, A, B> const& m, VectorA<T, A> const& v)
		{
			auto mT = m.Transpose();

			VectorA<T, B> newV;
			for (auto i = 0; i < B; i++)
			{
				newV[i] = v.Dot(mT[i]);
			}

			return newV;
		}

		// Multiply vectors
		template <typename T, typename int A, typename int B>
		MatrixAxB<T, A, B> Multiply(VectorA<T, B> const& v1, VectorA<T, A> const& v2)
		{
			MatrixAxB<T, A, B> newMatrix;

			for (int r = 0; r < B; r++)
			{
				for (int c = 0; c < A; c++)
				{
					newMatrix[c][r] = (v1[r] * v2[c]);
				}
			}

			return newMatrix;
		}

		// Decompose matrices
		// Taken from Ogre3D (https://bitbucket.org/sinbad/ogre/src/67a17b4dc55037f9d816df3fdfc80f6b1365f7ae/OgreMain/src/OgreMatrix3.cpp?at=default&fileviewer=file-view-default)
		// but changes slightly as they are row-major and we are column-major
		template <typename T>
		void DecomposeQDU(Matrix3x3<T> const& m, Matrix3x3<T>& q, Vector3<T>& d, Vector3<T>& u)
		{
			// Factor M = QR = QDU where Q is orthogonal, D is diagonal,
			// and U is upper triangular with ones on its diagonal.  Algorithm uses
			// Gram-Schmidt orthogonalization (the QR algorithm).
			//
			// If M = [ m0 | m1 | m2 ] and Q = [ q0 | q1 | q2 ], then
			//
			//   q0 = m0/|m0|
			//   q1 = (m1-(q0*m1)q0)/|m1-(q0*m1)q0|
			//   q2 = (m2-(q0*m2)q0-(q1*m2)q1)/|m2-(q0*m2)q0-(q1*m2)q1|
			//
			// where |V| indicates length of vector V and A*B indicates dot
			// product of vectors A and B.  The matrix R has entries
			//
			//   r00 = q0*m0  r01 = q0*m1  r02 = q0*m2
			//   r10 = 0      r11 = q1*m1  r12 = q1*m2
			//   r20 = 0      r21 = 0      r22 = q2*m2
			//
			// so D = diag(r00,r11,r22) and U has entries u01 = r01/r00,
			// u02 = r02/r00, and u12 = r12/r11.

			// Q = rotation
			// D = scaling
			// U = shear

			// D stores the three diagonal entries r00, r11, r22
			// U stores the entries U[0] = u01, U[1] = u02, U[2] = u12

			// build orthogonal matrix Q
			T fInvLength = T(1) / Sqrt(m[0][0] * m[0][0] + m[0][1] * m[0][1] + m[0][2] * m[0][2]);

			q[0][0] = m[0][0] * fInvLength;
			q[0][1] = m[0][1] * fInvLength;
			q[0][2] = m[0][2] * fInvLength;

			T fDot = q[0][0] * m[1][0] + q[0][1] * m[1][1] + q[0][2] * m[1][2];
			q[1][0] = m[1][0] - fDot * q[0][0];
			q[1][1] = m[1][1] - fDot * q[0][1];
			q[1][2] = m[1][2] - fDot * q[0][2];
			fInvLength =T(1) / Sqrt(q[1][0] * q[1][0] + q[1][1] * q[1][1] + q[1][2] * q[1][2]);

			q[1][0] *= fInvLength;
			q[1][1] *= fInvLength;
			q[1][2] *= fInvLength;

			fDot = q[0][0] * m[2][0] + q[0][1] * m[2][1] + q[0][2] * m[2][2];
			q[2][0] = m[2][0] - fDot * q[0][0];
			q[2][1] = m[2][1] - fDot * q[0][1];
			q[2][2] = m[2][2] - fDot * q[0][2];
			fDot = q[1][0] * m[2][0] + q[1][1] * m[2][1] + q[1][2] * m[2][2];
			q[2][0] -= fDot * q[1][0];
			q[2][1] -= fDot * q[1][1];
			q[2][2] -= fDot * q[1][2];
			fInvLength = T(1) / Sqrt(q[2][0] * q[2][0] + q[2][1] * q[2][1] + q[2][2] * q[2][2]);

			q[2][0] *= fInvLength;
			q[2][1] *= fInvLength;
			q[2][2] *= fInvLength;

			// guarantee that orthogonal matrix has determinant 1 (no reflections)
			T fDet = q[0][0] * q[1][1] * q[2][2] + q[1][0] * q[2][1] * q[0][2] +
				q[2][0] * q[0][1] * q[1][2] - q[2][0] * q[1][1] * q[0][2] -
				q[1][0] * q[0][1] * q[2][2] - q[0][0] * q[2][1] * q[1][2];

			if (fDet < 0.0)
			{
				for (size_t iRow = 0; iRow < 3; iRow++)
					for (size_t iCol = 0; iCol < 3; iCol++)
						q[iCol][iRow] = -q[iCol][iRow];
			}

			// build "right" matrix R
			Matrix3x3<T> r;
			r[0][0] = q[0][0] * m[0][0] + q[0][1] * m[0][1] + q[0][2] * m[0][2];
			r[1][0] = q[0][0] * m[1][0] + q[0][1] * m[1][1] + q[0][2] * m[1][2];
			r[1][1] = q[1][0] * m[1][0] + q[1][1] * m[1][1] + q[1][2] * m[1][2];
			r[2][0] = q[0][0] * m[2][0] + q[0][1] * m[2][1] + q[0][2] * m[2][2];
			r[2][1] = q[1][0] * m[2][0] + q[1][1] * m[2][1] + q[1][2] * m[2][2];
			r[2][2] = q[2][0] * m[2][0] + q[2][1] * m[2][1] + q[2][2] * m[2][2];

			// the scaling component
			d[0] = r[0][0];
			d[1] = r[1][1];
			d[2] = r[2][2];

			// the shear component
			T fInvD0 = T(1) / d[0];
			u[0] = r[1][0] * fInvD0;
			u[1] = r[2][0] * fInvD0;
			u[2] = r[2][1] / d[1];
		}

		// Taken from Ogre3D (https://bitbucket.org/sinbad/ogre/src/67a17b4dc55037f9d816df3fdfc80f6b1365f7ae/OgreMain/src/OgreMatrix4.cpp?at=default&fileviewer=file-view-default)
		// with some changes since they are row-major and we are column-major
		template <typename T>
		void TransformationMatrixDecomposition(Matrix4x4<T>& m, Vector3<T>& position, Vector3<T>& scale, Quaternion<T>& rotation)
		{
			Matrix3x3<T> matQ;
			Vector3<T> vecU;
			// this rotation matrix needs to also be gotten from the QDU decomposition...
			Matrix3x3<T> rotationMatrix = Matrix3x3<T>(m);
			DecomposeQDU(rotationMatrix, matQ, scale, vecU);

			rotation = QuatFromRotationMatrix(matQ);
			position = Vector3<T>(m[3][0], m[3][1], m[3][2]);
		}
#if DEBUG

		template <typename T, typename int A, typename int B>
		String MatrixString(MatrixAxB<T, A, B> m)
		{
			String matrixInfo;

			matrixInfo += "[";
			for (auto i = 0; i < A; i++)
			{
				matrixInfo += VectorString(m[i]);

				if (i != A - 1)
				{
					matrixInfo += ", ";
				}
			}
			matrixInfo += "]";

			return matrixInfo;
		}
#endif
	}
}