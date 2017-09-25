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

		// operators
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
