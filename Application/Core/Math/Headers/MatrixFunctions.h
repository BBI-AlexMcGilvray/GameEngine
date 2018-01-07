#pragma once

#include "Matrix.h"
#include "Matrix2x2.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"
#include "Quaternion.h"

#include "VectorFunctions.h"

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
					mTranspose[b][a] = this[a][b];
				}
			}
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