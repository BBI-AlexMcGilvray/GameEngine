#pragma once

#include <cmath>

namespace Core
{
	namespace Math
	{
		template <typename T>
		T Sqr(T a)
		{
			return (a * a);
		}

		template <typename T>
		T Sqrt(T a)
		{
			return sqrt(a);
		}

		template <typename T>
		T Cos(T a)
		{
			return cos(a);
		}

		template <typename T>
		T Sin(T a)
		{
			return sin(a);
		}

		template <typename T>
		T Tan(T a)
		{
			return tan(a);
		}
	}
}