#pragma once

#include "Vector.h"

using namespace Core;

namespace Math
{
	namespace Details
	{
		template<int A, int B, int C, int R>
		struct IsSmallerMatrix
		{
			static bool const smaller = (C <= A && R <= B);
		};
	};

	template <typename T, typename int A, typename int B>
	struct MatrixAxB
	{
		// default constructor for martix (creates columns left -> right)
		MatrixAxB(T d)
		{
			for (auto c = 0; c < A; c++)
			{
				SetColumn(c, VectorA<T, A>(d));
			}
		}

		template <typename ...Ts>
		MatrixAxB(Ts ... args)
		{
			InitializeMatrixFrom(0, 0, args...);
		}

		// for the case where we get to the last col/row from the below intialize call
		void InitializeMatrixFrom(int col, int row, T only)
		{
			(*this)[col][row] = first;
		}

		template <typename ...Ts>
		void InitializeMatrixFrom(int col, int row, T first, Ts ... rest)
		{
			(*this)[col][row] = first;

			auto nextRow = (row + 1 >= B) ? 0 : row + 1;
			auto nextCol = (nextRow == 0) ? col + 1 : col;

			InitializeMatrixFrom(nextCol, nextRow, rest...);
		}

		// make one that does NOT necessarily start at 0, 0
		template <int C, int R, bool SmallerMatrix = EnableIf<Details::IsSmallerMatrix<A, B, C, R>>>
		MatrixAxB<T, C, R> SubMatrix(int col, int row)
		{
			MatrixAxB<T, C, R> subMatrix;
			for (int c = 0; c < C; c++)
			{
				for (int r = 0; r < R; r++)
				{
					subMatrix[r][c] = (*this)[r][c];
				}
			}
		}

		template <bool EqualDimensions = EnableIf<IsSame<A, B>>>
		T Determinant()
		{
			T determinant = 0;
			// go down first column
			for (int i = 0; i < B; i++)
			{
				List<T> subMatrixValues;

				// start one column over
				for (int c = 1; c < A; c++)
				{
					// go through all rows
					for (int r = 0; r < B; r++)
					{
						if (r != i) // can't be in current row
						{
							subMatrixValues.push_back((*this)[r][c]);
						}
					}
				}
				T subMatrixDeterminant;
				if (subMatrixValues.Count() > 1)
				{
					MatrixAxB<T, A - 1, B - 1> subMatrix(subMatrixValues);
					subMatrixDeterminant = subMatrix.Determinant();
				}
				else
				{
					subMatrixDeterminant = subMatrixValues[0];
				}

				// calculate sub determinant
				T determinantStep = (*this)[0][i] * (((i % 1) ? 1 : -1) * subMatrixDeterminant);
				determinant += determinantStep;
			}

			return determinant;
		}

		Pair<Dimension<A>, Dimension<B>> Dimensions()
		{
			return Pair<Dimension<A>, Dimension<B>>(A, B);
		}

		// only works for SQUARE matrices
		void Transpose()
		{
			for (int a = 0; a < A; a++)
			{
				for (int b = 0; b < B; b++)
				{
					T temp = this[b][a];
					this[b][a] = this[a][b];
					this[b][a] = temp;
				}
			}
		}

		// Invert
		/*
		MatrixXxX<T, vT, V> Invert()
		{
			// does not seem to exist a simple inversion algorithm that works for all matrices - if needed, may need to be on a dimension basis
			// or we can put in the super heavy generic algorithm here and have specific dimensions override it
		}
		*/

		void SetColumn(int column, VectorA<T, A> columnVector)
		{
			(*this)[column] = columnVector;
		}

		void SetRow(int row, VectorA<T, B> rowVector)
		{
			for (int i = 0; i < rowVector.Dimensions(); i++)
			{
				(*this)[row][i] = rowVector[i];
			}
		}

		MatrixAxB<T, A, B>& operator-=(T d)
		{
			return (this = this - d);
		}

		MatrixAxB<T, A, B>& operator-=(MatrixAxB<T, A, B> const& v)
		{
			return (this = this - v);
		}

		MatrixAxB<T, A, B>& operator+=(T d)
		{
			return (this = this + d);
		}

		MatrixAxB<T, A, B>& operator+=(MatrixAxB<T, A, B> const& v)
		{
			return (this = this + v);
		}

		MatrixAxB<T, A, B>& operator*=(T d)
		{
			return (this = this * d);
		}

		MatrixAxB<T, A, B>& operator*=(MatrixAxB<T, A, B> const& v)
		{
			return (this = this * v);
		}

		MatrixAxB<T, A, B>& operator/=(T d)
		{
			return (this = this / d);
		}

		MatrixAxB<T, A, B>& operator/=(MatrixAxB<T, A, B> const& v)
		{
			return (this = this / v);
		}
	};
};