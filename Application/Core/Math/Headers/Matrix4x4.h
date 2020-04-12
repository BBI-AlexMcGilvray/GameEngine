#pragma once

#include "Matrix.h"

#include "Vector4.h"

#include "Core/Headers/ListDefs.h"

#include "VectorFunctions.h"

namespace Core
{
	namespace Math
	{
		/*
			Our matrices are column - major, NOT row - major.
		*/
		template <typename T>
		struct MatrixAxB<T, 4, 4>
		{
			union
			{
				struct
				{
					union
					{
						struct
						{
							union
							{
								struct
								{
									Vector4<T> E1;
									Vector4<T> E2;
								};
								Vector4<T> E1E2[2];
							};
							Vector4<T> E3;
						};
						Vector4<T> E1E2E3[3];
					};
					Vector4<T> E4;
				};
				Vector4<T> Bases[4];
			};

			MatrixAxB()
				: MatrixAxB(II())
			{}

			MatrixAxB(MatrixAxB<T, 2, 2> const& m, Vector4<T> e3 = Vector4<T>(0), Vector4<T> e4 = Vector4<T>(0))
				: E1(m.E1), E2(m.E2), E3(e3), E4(e4)
			{}

			MatrixAxB(MatrixAxB<T, 3, 3> const& m, Vector4<T> e4 = Vector4<T>(0))
				: E1(m.E1), E2(m.E2), E3(m.E3), E4(e4)
			{}

			MatrixAxB(MatrixAxB<T, 4, 4> const& m)
				: E1(m.E1), E2(m.E2), E3(m.E3), E4(m.E4)
			{}

			MatrixAxB(VectorA<T, 4> const& e1, VectorA<T, 4> const& e2, VectorA<T, 4> const& e3, VectorA<T, 4> const& e4)
				: E1(e1), E2(e2), E3(e3), E4(e4)
			{}

			MatrixAxB(II i)
				: E1(T(i), T(0), T(0), T(0)), E2(T(0), T(i), T(0), T(0)), E3(T(0), T(0), T(i), T(0)), E4(T(0), T(0), T(0), T(i))
			{}

			MatrixAxB(T d)
				: E1(d), E2(d), E3(d), E4(d)
			{}

			MatrixAxB(T d1, T d2, T d3 = 0, T d4 = 0, T d5 = 0, T d6 = 0, T d7 = 0, T d8 = 0, T d9 = 0, T d10 = 0, T d11 = 0, T d12 = 0, T d13 = 0, T d14 = 0, T d15 = 0, T d16 = 0)
				: E1(d1, d2, d3, d4), E2(d5, d6, d7, d8), E3(d9, d10, d11, d12), E4(d13, d14, d15, d16)
			{}

			// conversions
			operator MatrixAxB<T, 2, 2>()
			{
				return MatrixAxB<T, 2, 2>(E1, E2);
			}

			operator MatrixAxB<T, 3, 3>()
			{
				return MatrixAxB<T, 3, 3>(VectorA<T, 3>(E1), VectorA<T, 3>(E2), VectorA<T, 3>(E3));
			}

			// methods
			Pair<Dimension<4>, Dimension<4>> Dimensions() const
			{
				return Pair<Dimension<4>, Dimension<4>>(4, 4);
			}

			void SetColumn(int column, VectorA<T, 4> columnVector)
			{
				(*this)[column] = columnVector;
			}

			VectorA<T, 4> GetColumn(int column) const
			{
				return (*this)[column];
			}

			void SetRow(int row, VectorA<T, 4> rowVector)
			{
				for (int i = 0; i < 4; i++)
				{
					(*this)[i][row] = rowVector[i];
				}
			}

			VectorA<T, 4> GetRow(int row) const
			{
				VectorA<T, 4> rowV;
				for (int i = 0; i < 4; i++)
				{
					rowV[i] = (*this)[i][row];
				}

				return rowV;
			}

			// operators
			MatrixAxB<T, 4, 4>& operator-=(MatrixAxB<T, 4, 4> const& m)
			{
				E1 -= m.E1;
				E2 -= m.E2;
				E3 -= m.E3;
				E4 -= m.E4;

				return *this;
			}

			MatrixAxB<T, 4, 4>& operator+=(MatrixAxB<T, 4, 4> const& m)
			{
				E1 += m.E1;
				E2 += m.E2;
				E3 += m.E3;
				E4 += m.E4;

				return *this;
			}

			MatrixAxB<T, 4, 4>& operator*=(T d)
			{
				E1 *= d;
				E2 *= d;
				E3 *= d;
				E4 *= d;

				return *this;
			}

			MatrixAxB<T, 4, 4>& operator*=(MatrixAxB<T, 4, 4> const& m)
			{
				auto newCol1 = VectorA<T, 4>(Dot((*this).GetRow(0), m.E1), Dot((*this).GetRow(0), m.E2), Dot((*this).GetRow(0), m.E3), Dot((*this).GetRow(0), m.E4));
				auto newCol2 = VectorA<T, 4>(Dot((*this).GetRow(1), m.E1), Dot((*this).GetRow(1), m.E2), Dot((*this).GetRow(1), m.E3), Dot((*this).GetRow(1), m.E4));
				auto newCol3 = VectorA<T, 4>(Dot((*this).GetRow(2), m.E1), Dot((*this).GetRow(2), m.E2), Dot((*this).GetRow(2), m.E3), Dot((*this).GetRow(2), m.E4));
				auto newCol4 = VectorA<T, 4>(Dot((*this).GetRow(3), m.E1), Dot((*this).GetRow(3), m.E2), Dot((*this).GetRow(3), m.E3), Dot((*this).GetRow(3), m.E4));

				E1 = VectorA<T, 4>(newCol1.X, newCol2.X, newCol3.X, newCol4.X);
				E2 = VectorA<T, 4>(newCol1.Y, newCol2.Y, newCol3.Y, newCol4.Y);
				E3 = VectorA<T, 4>(newCol1.Z, newCol2.Z, newCol3.Z, newCol4.Z);
				E4 = VectorA<T, 4>(newCol1.W, newCol2.W, newCol3.W, newCol4.W);

				return *this;
			}

			MatrixAxB<T, 4, 4>& operator/=(T d)
			{
				E1 /= d;
				E2 /= d;
				E3 /= d;
				E4 /= d;

				return *this;
			}

			MatrixAxB<T, 4, 4>& operator/=(MatrixAxB<T, 4, 4> const& m)
			{
				E1 /= m.E1;
				E2 /= m.E2;
				E3 /= m.E3;
				E4 /= m.E4;

				return *this;
			}

			MatrixAxB<T, 4, 4>& operator=(T d)
			{
				E1 = VectorA<T, 4>(d);
				E2 = VectorA<T, 4>(d);
				E3 = VectorA<T, 4>(d);
				E4 = VectorA<T, 4>(d);

				return *this;
			}

			MatrixAxB<T, 4, 4>& operator=(MatrixAxB<T, 4, 4> const& m)
			{
				E1 = m.E1;
				E2 = m.E2;
				E3 = m.E3;
				E4 = m.E4;

				return *this;
			}

			friend MatrixAxB<T, 4, 4> operator-(MatrixAxB<T, 4, 4> m, T d)
			{
				m -= d;
				return m;
			}

			friend MatrixAxB<T, 4, 4> operator-(MatrixAxB<T, 4, 4> m, MatrixAxB<T, 4, 4> const& oM)
			{
				m -= oM;
				return m;
			}

			friend MatrixAxB<T, 4, 4> operator+(MatrixAxB<T, 4, 4> m, T d)
			{
				m += d;
				return m;
			}

			friend MatrixAxB<T, 4, 4> operator+(MatrixAxB<T, 4, 4> m, MatrixAxB<T, 4, 4> const& oM)
			{
				m += oM;
				return m;
			}

			friend MatrixAxB<T, 4, 4> operator*(MatrixAxB<T, 4, 4> m, T d)
			{
				m *= d;
				return m;
			}

			friend MatrixAxB<T, 4, 4> operator*(MatrixAxB<T, 4, 4> m, MatrixAxB<T, 4, 4> const& oM)
			{
				m *= oM;
				return m;
			}

			friend VectorA<T, 4> operator*(MatrixAxB<T, 4, 4> m, VectorA<T, 4> const& v)
			{
				VectorA<T, 4> nV(Dot(m.GetRow(0), v), Dot(m.GetRow(1), v), Dot(m.GetRow(2), v), Dot(m.GetRow(3), v));

				return nV;
			}

			friend MatrixAxB<T, 4, 4> operator/(MatrixAxB<T, 4, 4> m, T d)
			{
				m /= d;
				return m;
			}

			friend MatrixAxB<T, 4, 4> operator/(MatrixAxB<T, 4, 4> m, MatrixAxB<T, 4, 4> const& oM)
			{
				m /= oM;
				return m;
			}

			bool operator==(MatrixAxB<T, 4, 4> const& m)
			{
				return (E1 == m.E1 && E2 == m.E2 && E3 == m.E3 && E4 == m.E4);
			}

			// other comparison operators have no meaning

			VectorA<T, 4>& operator[](int basis)
			{
				return Bases[basis];
			}

			VectorA<T, 4> operator[](int basis) const
			{
				return Bases[basis];
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Matrix4x4 = MatrixAxB<T, 4, 4>;

		using Float4x4 = Matrix4x4<float>;
		using Int4x4 = Matrix4x4<int>;
		using Uint4x4 = Matrix4x4<uint>;
	}
}
