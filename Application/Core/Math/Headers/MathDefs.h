#pragma once

#include <cmath>

#include "Axis.h"
#include "Basis.h"

namespace Core
{
	namespace Math
	{
		template <typename int D>
		struct Precision
		{
			const float p = (1.0f / float(D));
			constexpr operator float() const { return p; }
		};
		using Tenth = Precision<10>;
		using Hundredth = Precision<100>;
		using Thousandth = Precision<1000>;

		template <typename int D>
		struct Dimension 
		{
			const int d = D;
			constexpr operator int() const { return d; }
		};
		using R1 = Dimension<1>;
		using R2 = Dimension<2>;
		using R3 = Dimension<3>;
		using R4 = Dimension<4>;

		struct II
		{
			const int i = 1;
			constexpr operator int() const { return i; }
			constexpr operator float() const { return float(i); }
		};

		const double PI_D = 3.1415926535897;
		const float PI_F = 3.1415927f;
		const int PI_I = 3;
	}
}