#pragma once

#include "Vector.h"

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

			// conversions
			operator VectorA<T, 3>()
			{
				return VectorA<T, 3>(X, Y, T(0));
			}

			operator VectorA<T, 4>()
			{
				return VectorA<T, 3>(X, Y, T(0), T(0));
			}

			// methods
			Dimension<2> Dimensions() const
			{
				return Dimension<2>();
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

			// do not need other = operators, since each vector type has the conversion operators
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

			// add in other comparison operaators

			T& operator[](int axis)
			{
				return Axes[axis];
			}

			T operator[](int axis) const
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