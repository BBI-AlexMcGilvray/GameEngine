#pragma once

#include "Vector.h"

namespace Core
{
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
			/*
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
			*/

			// Invert
			/*
			MatrixXxX<T, vT, V> Invert()
			{
				// does not seem to exist a simple inversion algorithm that works for all matrices - if needed, may need to be on a dimension basis
				// or we can put in the super heavy generic algorithm here and have specific dimensions override it
			}
			*/
		};
	}
}