#pragma once

#include "Vector.h"

#include "VectorFunctions.h"

namespace Core
{
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

			// methods
			Dimension<2> Dimensions()
			{
				return Dimension<2>;
			}

			T MagnitudeSqr()
			{
				return Dot(*this, *this);
			}

			T Magnitude()
			{
				return sqrt(MagnitudeSqr);
			}

			VectorA<T, 2>& Normalize()
			{
				return ((*this) /= (Magnitude()));
			}

			template <typename T>
			VectorA<T, 2>& Min(T d)
			{
				X = Min(X, d);
				Y =Min(Y, d);

				return (*this);
			}

			template <typename T>
			VectorA<T, 2>& Min(VectorA<T, 2> const& v1)
			{
				X = Min(X, v1.X);
				Y = Min(Y, v1.Y);

				return (*this);
			}

			template <typename T>
			VectorA<T, 2>& Max(T d)
			{
				X = Max(X, d);
				Y = Max(Y, d);

				return (*this);
			}

			template <typename T>
			VectorA<T, 2>& Max(VectorA<T, 2> const& v1)
			{
				X = Max(X, v1.X);
				Y = Max(Y, v1.Y);

				return (*this);
			}


			template <typename T>
			VectorA<T, 2>& Clamp(T d1, T d2)
			{
				X = Clamp(X, d1, d2);
				Y = Clamp(Y, d1, d2);

				return (*this);
			}

			template <typename T>
			VectorA<T, 2>& Clamp(VectorA<T, 2> const& v1, VectorA<T, 2> const& v2)
			{
				X = Clamp(X, v1.X, v2.X);
				Y = Clamp(Y, v1.Y, v2.Y);

				return (*this);
			}

			// operators
			VectorA<T, 2>& operator-=(VectorA<T, 2> const& v)
			{
				X -= v.X;
				Y -= v.Y;

				return (*this);
			}

			VectorA<T, 2>& operator+=(VectorA<T, 2> const& v)
			{
				X += v.X;
				Y += v.Y;

				return (*this);
			}

			VectorA<T, 2>& operator*=(T d)
			{
				X *= d;
				Y *= d;

				return (*this);
			}

			VectorA<T, 2>& operator*=(VectorA<T, 2> const& v)
			{
				X *= v.X;
				Y *= v.Y;

				return (*this);
			}

			VectorA<T, 2>& operator/=(T d)
			{
				X /= d;
				Y /= d;

				return (*this);
			}

			VectorA<T, 2>& operator/=(VectorA<T, 2> const& v)
			{
				X /= v.X;
				Y /= v.Y;

				return (*this);
			}

			VectorA<T, 2>& operator=(T d)
			{
				X = d;
				Y = d;

				return (*this);
			}

			VectorA<T, 2>& operator=(VectorA<T, 2> const& v)
			{
				if (this != &v)
				{
					X = v.X;
					Y = v.Y;
				}

				return (*this);
			}

			friend VectorA<T, 2> operator-(VectorA<T, 2> v, T d)
			{
				v -= d;
				return v;
			}

			friend VectorA<T, 2> operator-(VectorA<T, 2> v, VectorA<T, 2> const& oV)
			{
				v -= oV;
				return v;
			}

			friend VectorA<T, 2> operator+(VectorA<T, 2> v, T d)
			{
				v += d;
				return v;
			}

			friend VectorA<T, 2> operator+(VectorA<T, 2> v, VectorA<T, 2> const& oV)
			{
				v += oV;
				return v;
			}

			friend VectorA<T, 2> operator*(VectorA<T, 2> v, T d)
			{
				v *= d;
				return v;
			}

			friend VectorA<T, 2> operator*(VectorA<T, 2> v, VectorA<T, 2> const& oV)
			{
				v *= oV;
				return v;
			}

			friend VectorA<T, 2> operator/(VectorA<T, 2> v, T d)
			{
				v /= d;
				return v;
			}

			friend VectorA<T, 2> operator/(VectorA<T, 2> v, VectorA<T, 2> const& oV)
			{
				v /= oV;
				return v;
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
	}
}