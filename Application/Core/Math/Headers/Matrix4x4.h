#pragma once

#include "Matrix.h"
#include "Vector4.h"

namespace Math
{
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
								VectorA<T, 4> E1;
								VectorA<T, 4> E2;
							};
							VectorA<T, 4> E1E2[2];
						};
						VectorA<T, 4> E3;
					};
					VectorA<T, 4> E1E2E3[3];
				};
				VectorA<T, 4> E4;
			};
			VectorA<T, 4> Bases[4];
		};

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

		MatrixAxB(T d1 = 0, T d2 = 0, T d3 = 0, T d4 = 0, T d5 = 0, T d6 = 0, T d7 = 0, T d8 = 0, T d9 = 0, T d10 = 0, T d11 = 0, T d12 = 0, T d13 = 0, T d14 = 0, T d15 = 0, T d16 = 0)
			: E1(d1, d2, d3, d4), E2(d5, d6, d7, d8), E3(d9, d10, d11, d12), E4(d13, d14, d15, d16)
		{}

		// methods
		Pair<Dimension<4>, Dimension<4>> Dimensions()
		{
			return Pair<Dimension<4>, Dimension<4>>(4, 4);
		}

		void Transpose()
		{
			for (int a = 0; a < 4; a++)
			{
				for (int b = 0; b < 4; b++)
				{
					T temp = this[b][a];
					this[b][a] = this[a][b];
					this[b][a] = temp;
				}
			}
		}

		void SetColumn(int column, VectorA<T, 4> columnVector)
		{
			(*this)[column] = columnVector;
		}

		void SetRow(int row, VectorA<T, 4> rowVector)
		{
			for (int i = 0; i < rowVector.Dimensions(); i++)
			{
				(*this)[row][i] = rowVector[i];
			}
		}

		// operators
		MatrixAxB<T, 4, 4>& operator-=(T d)
		{
			return (this = this - d);
		}

		MatrixAxB<T, 4, 4>& operator-=(MatrixAxB<T, 4, 4> const& v)
		{
			return (this = this - v);
		}

		MatrixAxB<T, 4, 4>& operator+=(T d)
		{
			return (this = this + d);
		}

		MatrixAxB<T, 4, 4>& operator+=(MatrixAxB<T, 4, 4> const& v)
		{
			return (this = this + v);
		}

		MatrixAxB<T, 4, 4>& operator*=(T d)
		{
			return (this = this * d);
		}

		MatrixAxB<T, 4, 4>& operator*=(MatrixAxB<T, 4, 4> const& v)
		{
			return (this = this * v);
		}

		MatrixAxB<T, 4, 4>& operator/=(T d)
		{
			return (this = this / d);
		}

		MatrixAxB<T, 4, 4 >& operator/=(MatrixAxB<T, 4, 4> const& v)
		{
			return (this = this / v);
		}

		MatrixAxB<T, 4, 4>& operator-(MatrixAxB<T, 4, 4> const& m)
		{
			E1 -= m.E1;
			E2 -= m.E2;
			E3 -= m.E3;
			E4 -= m.E4;

			return *this;
		}

		MatrixAxB<T, 4, 4>& operator+(MatrixAxB<T, 4, 4> const& m)
		{
			E1 += m.E1;
			E2 += m.E2;
			E3 += m.E3;
			E4 += m.E4;

			return *this;
		}

		MatrixAxB<T, 4, 4>& operator*(T d)
		{
			E1 *= d;
			E2 *= d;
			E3 *= d;
			E4 *= d;

			return *this;
		}

		MatrixAxB<T, 4, 4>& operator*(MatrixAxB<T, 4, 4> const& m)
		{
			auto T = Transpose();

			E1 = VectorA<T, 4>(T.E1.Dot(m.E1), T.E1.Dot(m.E2), T.E1.Dot(m.E3), T.E1.Dot(m.E4));
			E2 = VectorA<T, 4>(T.E2.Dot(m.E1), T.E2.Dot(m.E2), T.E2.Dot(m.E3), T.E2.Dot(m.E4));
			E3 = VectorA<T, 4>(T.E3.Dot(m.E1), T.E3.Dot(m.E2), T.E3.Dot(m.E3), T.E3.Dot(m.E4));
			E4 = VectorA<T, 4>(T.E4.Dot(m.E1), T.E4.Dot(m.E2), T.E4.Dot(m.E3), T.E4.Dot(m.E4));

			return *this;
		}

		MatrixAxB<T, 4, 4>& operator/(T d)
		{
			E1 /= d;
			E2 /= d;
			E3 /= d;
			E4 /= d;

			return *this;
		}

		MatrixAxB<T, 4, 4>& operator/(MatrixAxB<T, 4, 4> const& m)
		{
			auto mI = m.Inverse();

			return ((*this) * mI);
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

		bool operator==(MatrixAxB<T, 4, 4> const& m)
		{
			return (E1 == m.E1 && E2 == m.E2 && E3 == m.E3 && E4 == m.E4);
		}

		VectorA<T, 4>& operator[](int basis)
		{
			return Bases[basis];
		}

		// operators
	};

	/*	TYPE DEFS	*/
	template <typename T>
	using Matrix4x4 = MatrixAxB<T, 4, 4>;

	using Float4x4 = Matrix4x4<float>;
	using Int4x4 = Matrix4x4<int>;
	using Uint4x4 = Matrix4x4<uint>;
};
