#pragma once

#include "Matrix.h"
#include "Vector3.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct MatrixAxB<T, 3, 3>
		{
			union
			{
				struct
				{
					union
					{
						struct
						{
							VectorA<T, 3> E1;
							VectorA<T, 3> E2;
						};
						VectorA<T, 3> E1E2[2];
					};
					VectorA<T, 3> E3;
				};
				VectorA<T, 3> Bases[3];
			};

			MatrixAxB()
				: MatrixAxB(II())
			{}

			MatrixAxB(MatrixAxB<T, 2, 2> const& m, Vector3<T> e3 = Vector3<T>(0))
				: E1(m.E1), E2(m.E2), E3(e3)
			{}

			MatrixAxB(MatrixAxB<T, 3, 3> const& m)
				: E1(m.E1), E2(m.E2), E3(m.E3)
			{}

			MatrixAxB(VectorA<T, 3> const& e1, VectorA<T, 3> const& e2, VectorA<T, 3> const& e3)
				: E1(e1), E2(e2), E3(e3)
			{}

			MatrixAxB(II i)
				: E1(T(1), T(0), T(0)), E2(T(0), T(i), T(0)), E3(T(0), T(0), T(i))
			{}

			MatrixAxB(T d)
				: E1(d), E2(d), E3(d)
			{}

			MatrixAxB(T d1, T d2, T d3 = 0, T d4 = 0, T d5 = 0, T d6 = 0, T d7 = 0, T d8 = 0, T d9 = 0)
				: E1(d1, d2, d3), E2(d4, d5, d6), E3(d7, d8, d9)
			{}

			// conversions
			operator MatrixAxB<T, 2, 2>()
			{
				return MatrixAxB<T, 2, 2>(E1, E2);
			}

			operator MatrixAxB<T, 4, 4>()
			{
				return MatrixAxB<T, 4, 4>(E1, E2, E3, T(0));
			}

			// methods
			Pair<Dimension<3>, Dimension<3>> Dimensions() const
			{
				return Pair<Dimension<3>, Dimension<3>>(3, 3);
			}

			void SetColumn(int column, VectorA<T, 3> columnVector)
			{
				(*this)[column] = columnVector;
			}

			VectorA<T, 3> GetColumn(int column) const
			{
				return (*this)[column];
			}

			void SetRow(int row, VectorA<T, 3> rowVector)
			{
				for (int i = 0; i < 3; i++)
				{
					(*this)[i][row] = rowVector[i];
				}
			}

			VectorA<T, 3> GetRow(int row) const
			{
				VectorA<T, 3> rowV;
				for (int i = 0; i < 3; i++)
				{
					rowV[i] = (*this)[i][row];
				}

				return rowV;
			}

			// operators
			MatrixAxB<T, 3, 3>& operator-=(MatrixAxB<T, 3, 3> const& m)
			{
				E1 -= m.E1;
				E2 -= m.E2;
				E3 -= m.E3;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator+=(MatrixAxB<T, 3, 3> const& m)
			{
				E1 += m.E1;
				E2 += m.E2;
				E3 += m.E3;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator*=(T d)
			{
				E1 *= d;
				E2 *= d;
				E3 *= d;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator*=(MatrixAxB<T, 3, 3> const& m)
			{
				auto newCol1 = VectorA<T, 3>(Dot((*this).GetRow(0), m.E1), Dot((*this).GetRow(0), m.E2), Dot((*this).GetRow(0), m.E3));
				auto newCol2 = VectorA<T, 3>(Dot((*this).GetRow(1), m.E1), Dot((*this).GetRow(1), m.E2), Dot((*this).GetRow(1), m.E3));
				auto newCol3 = VectorA<T, 3>(Dot((*this).GetRow(2), m.E1), Dot((*this).GetRow(2), m.E2), Dot((*this).GetRow(2), m.E3));

				E1 = VectorA<T, 3>(newCol1.X, newCol2.X, newCol3.X);
				E2 = VectorA<T, 3>(newCol1.Y, newCol2.Y, newCol3.Y);
				E3 = VectorA<T, 3>(newCol1.Z, newCol2.Z, newCol3.Z);

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator/=(T d)
			{
				E1 /= d;
				E2 /= d;
				E3 /= d;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator/=(MatrixAxB<T, 3, 3> const& m)
			{
				E1 /= m.E1;
				E2 /= m.E2;
				E3 /= m.E3;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator=(T d)
			{
				E1 = VectorA<T, 4>(d);
				E2 = VectorA<T, 4>(d);
				E3 = VectorA<T, 4>(d);

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator=(MatrixAxB<T, 3, 3> const& m)
			{
				E1 = m.E1;
				E2 = m.E2;
				E3 = m.E3;

				return *this;
			}

			friend MatrixAxB<T, 3, 3> operator-(MatrixAxB<T, 3, 3> m, T d)
			{
				m -= d;
				return m;
			}

			friend MatrixAxB<T, 3, 3> operator-(MatrixAxB<T, 3, 3> m, MatrixAxB<T, 3, 3> const& oM)
			{
				m -= oM;
				return m;
			}

			friend MatrixAxB<T, 3, 3> operator+(MatrixAxB<T, 3, 3> m, T d)
			{
				m += d;
				return m;
			}

			friend MatrixAxB<T, 3, 3> operator+(MatrixAxB<T, 3, 3> m, MatrixAxB<T, 3, 3> const& oM)
			{
				m += oM;
				return m;
			}

			friend MatrixAxB<T, 3, 3> operator*(MatrixAxB<T, 3, 3> m, T d)
			{
				m *= d;
				return m;
			}

			friend MatrixAxB<T, 3, 3> operator*(MatrixAxB<T, 3, 3> m, MatrixAxB<T, 3, 3> const& oM)
			{
				m *= oM;
				return m;
			}

			friend VectorA<T, 3> operator*(MatrixAxB<T, 3, 3> m, VectorA<T, 3> const& v)
			{
				VectorA<T, 3> nV(Dot(m.GetRow(0), v), Dot(m.GetRow(1), v), Dot(m.GetRow(2), v));

				return nV;
			}

			friend MatrixAxB<T, 3, 3> operator/(MatrixAxB<T, 3, 3> m, T d)
			{
				m /= d;
				return m;
			}

			friend MatrixAxB<T, 3, 3> operator/(MatrixAxB<T, 3, 3> m, MatrixAxB<T, 3, 3> const& oM)
			{
				m /= oM;
				return m;
			}

			bool operator==(MatrixAxB<T, 3, 3> const& m)
			{
				return (E1 == m.E1 && E2 == m.E2 && E3 == m.E3);
			}

			// other comparison operators have no meaning

			VectorA<T, 3>& operator[](int basis)
			{
				return Bases[basis];
			}

			VectorA<T, 3> operator[](int basis) const
			{
				return Bases[basis];
			}

			// operators
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Matrix3x3 = MatrixAxB<T, 3, 3>;

		using Float3x3 = Matrix3x3<float>;
		using Int3x3 = Matrix3x3<int>;
		using Uint3x3 = Matrix3x3<uint>;
	}
}
