#pragma once

#include <cmath>

#include "Axis.h"

namespace Core
{
	namespace Math
	{
		template <typename int D>
		struct Precision
		{
			const float p = (1.0f / float(D));
			operator float() const { return p; }
		};
		using Tenth = Precision<10>;
		using Hundredth = Precision<100>;
		using Thousandth = Precision<1000>;

		template <typename int D>
		struct Dimension 
		{
			const int d = D;
			operator int() const { return d; }
		};
		using R1 = Dimension<1>;
		using R2 = Dimension<2>;
		using R3 = Dimension<3>;
		using R4 = Dimension<4>;

		template <typename int B>
		struct Basis
		{
			const int b = B;
			operator int() const { return b; }
		};
		using E1 = Basis<0>;
		using E2 = Basis<1>;
		using E3 = Basis<2>;
		using E4 = Basis<3>;

		struct II
		{
			const int i = 1;
			operator int() const { return i; }
			operator float() const { return float(i); }
		};

		const double PI_D = 3.1415926535897;
		const float PI_F = 3.1415927f;
		const int PI_I = 3;
	}
}