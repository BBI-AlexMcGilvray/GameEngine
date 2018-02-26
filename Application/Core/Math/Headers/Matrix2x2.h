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
			MatrixAxB()
				: MatrixAxB(II())
			{}

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

			MatrixAxB(T d1, T d2, T d3 = 0, T d4 = 0)
				: E1(d1, d2), E2(d3, d4)
			{}

			// conversions
			operator MatrixAxB<T, 3, 3>()
			{
				return MatrixAxB<T, 3, 3>(E1, E2, T(0));
			}

			operator MatrixAxB<T, 4, 4>()
			{
				return MatrixAxB<T, 4, 4>(E1, E2, T(0), T(0));
			}

			// methods
			Pair<Dimension<2>, Dimension<2>> Dimensions() const
			{
				return Pair<Dimension<2>, Dimension<2>>(2, 2);
			}

			void SetColumn(int column, VectorA<T, 2> columnVector)
			{
				(*this)[column] = columnVector;
			}

			VectorA<T, 2> GetColumn(int column) const
			{
				return (*this)[column];
			}

			void SetRow(int row, VectorA<T, 2> rowVector)
			{
				for (int i = 0; i < 2; i++)
				{
					(*this)[i][row] = rowVector[i];
				}
			}

			VectorA<T, 2> GetRow(int row) const
			{
				VectorA<T, 2> rowV;
				for (int i = 0; i < 2; i++)
				{
					rowV[i] = (*this)[i][row];
				}

				return rowV;
			}

			// operators
			MatrixAxB<T, 2, 2>& operator-=(MatrixAxB<T, 2, 2> const& m)
			{
				E1 -= m.E1;
				E2 -= m.E2;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator+=(MatrixAxB<T, 2, 2> const& m)
			{
				E1 += m.E1;
				E2 += m.E2;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator*=(T d)
			{
				E1 *= d;
				E2 *= d;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator*=(MatrixAxB<T, 2, 2> const& m)
			{
				auto newE1 = VectorA<T, 4>(Dot((*this).GetRow(0), m.E1), Dot((*this).GetRow(0), m.E2));
				auto newE2 = VectorA<T, 4>(Dot((*this).GetRow(1), m.E1), Dot((*this).GetRow(1), m.E2));

				E1 = newE1;
				E2 = newE2;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator/=(T d)
			{
				E1 /= d;
				E2 /= d;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator/=(MatrixAxB<T, 2, 2> const& m)
			{
				E1 /= m.E1;
				E2 /= m.E2;

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator=(T d)
			{
				E1 = VectorA<T, 4>(d);
				E2 = VectorA<T, 4>(d);

				return *this;
			}

			MatrixAxB<T, 2, 2>& operator=(MatrixAxB<T, 2, 2> const& m)
			{
				E1 = m.E1;
				E2 = m.E2;

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
				VectorA<T, 2> nV(Dotr(m.GetRow(0), v), Dot(m.GetRow(1), v));

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

			// other comparison operators have no meaning

			VectorA<T, 2>& operator[](int basis)
			{
				return Bases[basis];
			}

			VectorA<T, 2> operator[](int basis) const
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