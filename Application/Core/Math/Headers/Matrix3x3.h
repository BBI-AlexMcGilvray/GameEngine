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

			MatrixAxB(T d1 = 0, T d2 = 0, T d3 = 0, T d4 = 0, T d5 = 0, T d6 = 0, T d7 = 0, T d8 = 0, T d9 = 0)
				: E1(d1, d2, d3), E2(d4, d5, d6), E3(d7, d8, d9)
			{}

			// methods
			Pair<Dimension<3>, Dimension<3>> Dimensions()
			{
				return Pair<Dimension<3>, Dimension<3>>(3, 3);
			}

			void Transpose()
			{
				for (int a = 0; a < 3; a++)
				{
					for (int b = 0; b < 3; b++)
					{
						T temp = this[b][a];
						this[b][a] = this[a][b];
						this[b][a] = temp;
					}
				}
			}

			void SetColumn(int column, VectorA<T, 3> columnVector)
			{
				(*this)[column] = columnVector;
			}

			void SetRow(int row, VectorA<T, 3> rowVector)
			{
				for (int i = 0; i < rowVector.Dimensions(); i++)
				{
					(*this)[row][i] = rowVector[i];
				}
			}

			// operators
			MatrixAxB<T, 3, 3>& operator-=(MatrixAxB<T, 3, 3> const& m)
			{
				E1 -= m.E1;
				E2 -= m.E2;
				E3 -= m.E3;
				E4 -= m.E4;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator+=(MatrixAxB<T, 3, 3> const& m)
			{
				E1 += m.E1;
				E2 += m.E2;
				E3 += m.E3;
				E4 += m.E4;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator*=(T d)
			{
				E1 *= d;
				E2 *= d;
				E3 *= d;
				E4 *= d;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator*=(MatrixAxB<T, 3, 3> const& m)
			{
				auto Copy = (*this);
				Copy.Transpose();

				E1 = VectorA<T, 4>(Copy.E1.Dot(m.E1), Copy.E1.Dot(m.E2), Copy.E1.Dot(m.E3), Copy.E1.Dot(m.E4));
				E2 = VectorA<T, 4>(Copy.E2.Dot(m.E1), Copy.E2.Dot(m.E2), Copy.E2.Dot(m.E3), Copy.E2.Dot(m.E4));
				E3 = VectorA<T, 4>(Copy.E3.Dot(m.E1), Copy.E3.Dot(m.E2), Copy.E3.Dot(m.E3), Copy.E3.Dot(m.E4));
				E4 = VectorA<T, 4>(Copy.E4.Dot(m.E1), Copy.E4.Dot(m.E2), Copy.E4.Dot(m.E3), Copy.E4.Dot(m.E4));

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator/=(T d)
			{
				E1 /= d;
				E2 /= d;
				E3 /= d;
				E4 /= d;

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator/=(MatrixAxB<T, 3, 3> const& m)
			{
				auto mI = m.Inverse();

				return ((*this) * mI);
			}

			MatrixAxB<T, 3, 3>& operator=(T d)
			{
				E1 = VectorA<T, 4>(d);
				E2 = VectorA<T, 4>(d);
				E3 = VectorA<T, 4>(d);
				E4 = VectorA<T, 4>(d);

				return *this;
			}

			MatrixAxB<T, 3, 3>& operator=(MatrixAxB<T, 3, 3> const& m)
			{
				E1 = m.E1;
				E2 = m.E2;
				E3 = m.E3;
				E4 = m.E4;

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

			VectorA<T, 3>& operator[](int basis)
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
