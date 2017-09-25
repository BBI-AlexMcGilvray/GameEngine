#pragma once

#include "Vector.h"

namespace Math
{
	template <typename T>
	struct VectorA<T, 2>
	{
		union
		{
			struct
			{
				T X;
				T Y;
			};
			T Axes[2];
		};

		VectorA(T d = 0)
			: X(d), Y(d)
		{}

		VectorA(T x, T y)
			: X(x), Y(y)
		{}

		VectorA(VectorA<T, 2> const& v)
			: X(v.X), Y(v.Y)
		{}

		T Dot(VectorA<T, 2> const& v)
		{
			auto temp = v;
			temp * (*this);

			return (temp.X + temp.Y);
		}

		template <typename T>
		VectorA<T, 2> Min(VectorA<T, 2> const& v, T d)
		{
			VectorA<T, 2> minV(Min(v.X, d), Min(v.Y, d));

			return minV;
		}

		template <typename T>
		VectorA<T, 2> Min(VectorA<T, 2> const& v1, VectorA<T, 2> const& v2)
		{
			VectorA<T, 2> minV(Min(v1.X, v2.X), Min(v1.Y, v2.Y));

			return minV;
		}

		template <typename T>
		VectorA<T, 2> Max(VectorA<T, 2> const& v, T d)
		{
			VectorA<T, 2> maxV(Max(v.X, d), Max(v.Y, d));

			return maxV;
		}

		template <typename T>
		VectorA<T, 2> Max(VectorA<T, 2> const& v1, VectorA<T, 2> const& v2)
		{
			VectorA<T, 2> maxV(Max(v1.X, v2.X), Max(v1.Y, v2.Y));

			return maxV;
		}


		template <typename T>
		VectorA<T, 2> Clamp(VectorA<T, 2> const& v, T d1, T d2)
		{
			VectorA<T, 2> clampV(Clamp(v1.X, d1, d2), Clamp(v1.Y, d1, d2));

			return clampV;
		}

		template <typename T>
		VectorA<T, 2> Clamp(VectorA<T, 2> const& v1, VectorA<T, 2> const& v2, VectorA<T, 2> const& v3)
		{
			VectorA<T, 2> clampV(Clamp(v1.X, v2.X, v3.X), Clamp(v1.Y, v2.Y, v3.Y));

			return clampV;
		}

		VectorA<T, 2>& operator-(VectorA<T, 2> const& v)
		{
			X -= v.X;
			Y -= v.Y;

			return *this;
		}

		VectorA<T, 2>& operator+(VectorA<T, 2> const& v)
		{
			X += v.X;
			Y += v.Y;

			return *this;
		}

		VectorA<T, 2>& operator*(T d)
		{
			X *= d;
			Y *= d;

			return *this;
		}

		VectorA<T, 2>& operator*(VectorA<T, 2> const& v)
		{
			X *= v.X;
			Y *= v.Y;

			return *this;
		}

		VectorA<T, 2>& operator/(T d)
		{
			X /= d;
			Y /= d;

			return *this;
		}

		VectorA<T, 2>& operator/(VectorA<T, 2> const& v)
		{
			X /= v.X;
			Y /= v.Y;

			return *this;
		}

		VectorA<T, 2>& operator=(T d)
		{
			X = d;
			Y = d;

			return *this;
		}

		VectorA<T, 2>& operator=(VectorA<T, 2> const& v)
		{
			X = v.X;
			Y = v.Y;

			return *this;
		}

		bool operator==(VectorA<T, 2> const& v)
		{
			return (X == v.X && Y == v.Y);
		}

		T& operator[](int axis)
		{
			return Axes[axis];
		}
	};

/*	TYPE DEFS	*/
	template <typename T>
	using Vector2 = VectorA<T, 2>;

	using Float2 = Vector2<float>;
	using Int2 = Vector2<int>;
	using Uint2 = Vector2<uint>;
};