#pragma once

#include <cmath>
#include <limits>

#include "Axis.h"
#include "Basis.h"

namespace Core
{
	namespace Math
	{
		constexpr double PI_D = 3.1415926535897;
		constexpr float PI_F = 3.1415927f;
		constexpr int PI_I = 3;

		constexpr double Inf_D = std::numeric_limits<double>::max();
		constexpr float Inf_F = std::numeric_limits<float>::max();
		constexpr int Inf_I = std::numeric_limits<int>::max();

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

		struct Rad;

		template <typename T = float>
		struct Deg
		{
			constexpr Deg(T degrees = T(0))
				: Degrees(degrees)
			{}

			constexpr Deg(Rad radians)
				: Degrees(radians * T(180) / T(PI_F))
			{}

			T Degrees = T(0);
			constexpr operator T() const { return Degrees; }
		};

		struct Rad
		{
			constexpr Rad(float radians = 0.0f)
				: Radians(radians)
			{}

			template <typename T>
			constexpr Rad(Deg<T> degrees)
				: Radians(float(degrees) * PI_F / 180.0f)
			{}

			float Radians = 0.0f;
			constexpr operator float() const { return Radians; }
		};
	}
}