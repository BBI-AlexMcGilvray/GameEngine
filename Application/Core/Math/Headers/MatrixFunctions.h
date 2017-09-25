#pragma once

#include "Matrix.h"

#include "VectorFunctions.h"

namespace Math
{
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
	MatrixAxB<T, A, B> Multiply(VectorA<T, B> const% v1, VectorA<T, A> const& v2)
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
	String MatrixString(Matrix<T, A, B> m)
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
};