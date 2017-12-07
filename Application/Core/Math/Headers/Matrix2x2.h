#pragma once

#include "Matrix.h"
#include "Vector2.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct MatrixAxB<T, 2, 2>
		{
			union
			{
				struct
				{
					VectorA<T, 2> E1;
					VectorA<T, 2> E2;
				};
				VectorA<T, 2> Bases[2];
			};

			// constructors
			MatrixAxB(MatrixAxB<T, 2, 2> const& m)
				: E1(m.E1), E2(m.E2)
			{}

			MatrixAxB(VectorA<T, 2> const& e1, VectorA<T, 2> const& e2)
				: E1(e1), E2(e2)
			{}

			MatrixAxB(II i)
				: E1(T(i), T(0)), E2(T(0), T(i))
			{}

			MatrixAxB(T d)
				: E1(d), E2(d)
			{}

			MatrixAxB(T d1 = 0, T d2 = 0, T d3 = 0, T d4 = 0)
				: E1(d1, d2), E2(d3, d4)
			{}

			// methods
			Pair<Dimension<2>, Dimension<2>> Dimensions()
			{
				return Pair<Dimension<2>, Dimension<2>>(2, 2);
			}

			void Transpose()
			{
				for (int a = 0; a < 2; a++)
				{
					for (int b = 0; b < 2; b++)
					{
						T temp = this[b][a];
						this[b][a] = this[a][b];
						this[b][a] = temp;
					}
				}
			}

			void SetColumn(int column, VectorA<T, 2> columnVector)
			{
				(*this)[column] = columnVector;
			}

			void SetRow(int row, VectorA<T, 2> rowVector)
			{
				for (int i = 0; i < rowVector.Dimensions(); i++)
				{
					(*this)[row][i] = rowVector[i];
				}
			}

			// operators
			MatrixAxB<T, 2, 2>& operator-=(MatrixAxB<T, 2, 2> const& m)
			{
				E1 -= m.E1;
				E2 -= m.E2;
				E3 -= m.E3;
				E4 -= m.E4;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator+=(MatrixAxB<T, 2, 2> const& m)
			{
				E1 += m.E1;
				E2 += m.E2;
				E3 += m.E3;
				E4 += m.E4;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator*=(T d)
			{
				E1 *= d;
				E2 *= d;
				E3 *= d;
				E4 *= d;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator*=(MatrixAxB<T, 2, 2> const& m)
			{
				auto Copy = (*this);
				Copy.Transpose();

				E1 = VectorA<T, 4>(Copy.E1.Dot(m.E1), Copy.E1.Dot(m.E2), Copy.E1.Dot(m.E3), Copy.E1.Dot(m.E4));
				E2 = VectorA<T, 4>(Copy.E2.Dot(m.E1), Copy.E2.Dot(m.E2), Copy.E2.Dot(m.E3), Copy.E2.Dot(m.E4));
				E3 = VectorA<T, 4>(Copy.E3.Dot(m.E1), Copy.E3.Dot(m.E2), Copy.E3.Dot(m.E3), Copy.E3.Dot(m.E4));
				E4 = VectorA<T, 4>(Copy.E4.Dot(m.E1), Copy.E4.Dot(m.E2), Copy.E4.Dot(m.E3), Copy.E4.Dot(m.E4));

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator/=(T d)
			{
				E1 /= d;
				E2 /= d;
				E3 /= d;
				E4 /= d;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator/=(MatrixAxB<T, 2, 2> const& m)
			{
				auto mI = m.Inverse();

				return ((*this) * mI);
			}

			MatrixAxB<T, 2, 2>& operator=(T d)
			{
				E1 = VectorA<T, 4>(d);
				E2 = VectorA<T, 4>(d);
				E3 = VectorA<T, 4>(d);
				E4 = VectorA<T, 4>(d);

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator=(MatrixAxB<T, 2, 2> const& m)
			{
				E1 = m.E1;
				E2 = m.E2;
				E3 = m.E3;
				E4 = m.E4;

				return *this;
			}

			friend MatrixAxB<T, 2, 2> operator-(MatrixAxB<T, 2, 2> m, T d)
			{
				m -= d;
				return m;
			}

			friend MatrixAxB<T, 2, 2> operator-(MatrixAxB<T, 2, 2> m, MatrixAxB<T, 2, 2> const& oM)
			{
				m -= oM;
				return m;
			}

			friend MatrixAxB<T, 2, 2> operator+(MatrixAxB<T, 2, 2> m, T d)
			{
				m += d;
				return m;
			}

			friend MatrixAxB<T, 2, 2> operator+(MatrixAxB<T, 2, 2> m, MatrixAxB<T, 2, 2> const& oM)
			{
				m += oM;
				return m;
			}

			friend MatrixAxB<T, 2, 2> operator*(MatrixAxB<T, 2, 2> m, T d)
			{
				m *= d;
				return m;
			}

			friend MatrixAxB<T, 2, 2> operator*(MatrixAxB<T, 2, 2> m, MatrixAxB<T, 2, 2> const& oM)
			{
				m *= oM;
				return m;
			}

			friend VectorA<T, 2> operator*(MatrixAxB<T, 2, 2> m, VectorA<T, 2> const& v)
			{
				VectorA<T, 2> nV(m.E1.Dot(v), m.E2.Dot(v));

				return nV;
			}

			friend MatrixAxB<T, 2, 2> operator/(MatrixAxB<T, 2, 2> m, T d)
			{
				m /= d;
				return m;
			}

			friend MatrixAxB<T, 2, 2> operator/(MatrixAxB<T, 2, 2> m, MatrixAxB<T, 2, 2> const& oM)
			{
				m /= oM;
				return m;
			}

			bool operator==(MatrixAxB<T, 2, 2> const& m)
			{
				return (E1 == m.E1 && E2 == m.E2);
			}

			VectorA<T, 2>& operator[](int basis)
			{
				return Bases[basis];
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Matrix2x2 = MatrixAxB<T, 2, 2>;

		using Float2x2 = Matrix2x2<float>;
		using Int2x2 = Matrix2x2<int>;
		using Uint2x2 = Matrix2x2<uint>;
	}
}