#pragma once

#include "Matrix.h"
#include "Vector2.h"

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

		MatrixAxB(MatrixAxB<T, 2, 2> const& m)
			: E1(m.E1), E2(m.E2)
		{}

		MatrixAxB(VectorA<T, 2> const& e1, VectorA<T, 2> const& e2)
			: E1(e1), E2(e2)
		{}

		MatrixAxB(II i)
			: E1(T(i), T(0)), E2(T(0), T(i))
		{}

		MatrixAxB<T, 2, 2> Inverse()
		{
			MatrixAxB<2, 2> swappedMatrix(E2.Y, -E1.Y, -E2.X, E1.X);
			swappedMatrix /= Determinant();

			return swappedMatrix;
		}

		// operators
		MatrixAxB<T, 2, 2>& operator-(MatrixAxB<T, 2, 2> const& m)
		{
			E1 -= m.E1;
			E2 -= m.E2;

			return *this;
		}

		MatrixAxB<T, 2, 2>& operator+(MatrixAxB<T, 2, 2> const& m)
		{
			E1 += m.E1;
			E2 += m.E2;

			return *this;
		}

		MatrixAxB<T, 2, 2>& operator*(T d)
		{
			E1 *= d;
			E2 *= d;

			return *this;
		}

		MatrixAxB<T, 2, 2>& operator*(MatrixAxB<T, 2, 2> const& m)
		{
			auto T = Transpose();

			E1 = VectorA<T, 2>(T.E1.Dot(m.E1), T.E1.Dot(m.E2));
			E2 = VectorA<T, 2>(T.E2.Dot(m.E1), T.E2.Dot(m.E2));

			return *this;
		}

		MatrixAxB<T, 2, 2>& operator/(T d)
		{
			E1 /= d;
			E2 /= d;

			return *this;
		}

		MatrixAxB<T, 2, 2>& operator/(MatrixAxB<T, 2, 2> const& m)
		{
			auto mI = m.Inverse();

			return ((*this) * mI);
		}

		MatrixAxB<T, 2, 2>& operator=(T d)
		{
			E1 = VectorA<T, 2>(d);
			E2 = VectorA<T, 2>(d);

			return *this;
		}

		MatrixAxB<T, 2, 2>& operator=(MatrixAxB<T, 2, 2> const& m)
		{
			E1 = m.E1;
			E2 = m.E2;

			return *this;
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
};