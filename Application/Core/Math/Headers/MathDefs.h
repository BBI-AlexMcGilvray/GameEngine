#pragma once

#include <cmath>

namespace Math
{
	template <typename int D>
	struct Dimension { static const int d = D; operator int() const { return d; } };
	using R1 = Dimension<1>;
	using R2 = Dimension<2>;
	using R3 = Dimension<3>;
	using R4 = Dimension<4>;

	template <typename int A>
	struct Axis { static const int a = A;  operator int() const { return a; } };
	using X = Axis<0>;
	using Y = Axis<1>;
	using Z = Axis<2>;
	using W = Axis<3>;

	template <typename int B>
	struct Basis { static const int b = B; operator int() const { return b; } };
	using E1 = Basis<0>;
	using E2 = Basis<1>;
	using E3 = Basis<2>;
	using E4 = Basis<3>;

	struct II { static const int i = 1; operator int() const { return i; } };

	const double PI_D = 3.1415926535897;
	const float PI_F = 3.1415927f;
	const int PI_I = 3;
};