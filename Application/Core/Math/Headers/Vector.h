#pragma once

#include "MathDefs.h"
#include "../../Headers/CoreDefs.h"

using namespace Core;

namespace Math
{
	template <typename T, typename int A>
	struct VectorA
	{
		Dimension Dimensions()
		{
			return A;
		}

		T MagnitudeSqr()
		{
			return Dot(*this);
		}

		T Magnitude()
		{
			return sqrt(MagnitudeSqr);
		}

		VectorA<T, A>& Normalize()
		{
			return ((*this) /= (Magnitude()));
		}

		VectorA<T, A>& operator-=(T d)
		{
			return (this = this - d);
		}

		VectorA<T, A>& operator-=(VectorA<T, A> const& v)
		{
			return (this = this - v);
		}

		VectorA<T, A>& operator+=(T d)
		{
			return (this = this + d);
		}

		VectorA<T, A>& operator+=(VectorA<T, A> const& v)
		{
			return (this = this + v);
		}

		VectorA<T, A>& operator*=(T d)
		{
			return (this = this * d);
		}

		VectorA<T, A>& operator*=(VectorA<T, A> const& v)
		{
			return (this = this * v);
		}

		VectorA<T, A>& operator/=(T d)
		{
			return (this = this / d);
		}

		VectorA<T, A>& operator/=(VectorA<T, A> const& v)
		{
			return (this = this / v);
		}
	};
};