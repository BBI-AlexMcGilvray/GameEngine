#pragma once

#include "Vector.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct VectorA<T, 3>
		{
			union
			{
				struct
				{
					union
					{
						struct
						{
							T X;
							T Y;
						};
						VectorA<T, 2> XY;
					};
					T Z;
				};
				T Axes[3];
			};

			VectorA(T d = 0)
				: X(d), Y(d), Z(d)
			{}

			VectorA(T x, T y, T z)
				:X(x), Y(y), Z(z)
			{}

			VectorA(VectorA<T, 2> const& v, T d1 = 0)
				: XY(v), Z(d1)
			{}

			VectorA(VectorA<T, 3> const& v)
				: X(v.X), Y(v.Y), Z(v.Z)
			{}

			// conversions
			operator VectorA<T, 2>()
			{
				return XY;
			}

			operator VectorA<T, 4>()
			{
				return VectorA<T, 4>(X, Y, Z, T(0));
			}

			// methods
			Dimension<3> Dimensions() const
			{
				return Dimension<3>();
			}

			// operators
			VectorA<T, 3>& operator-=(VectorA<T, 3> const& v)
			{
				X -= v.X;
				Y -= v.Y;
				Z -= v.Z;

				return (*this);
			}

			VectorA<T, 3>& operator+=(VectorA<T, 3> const& v)
			{
				X += v.X;
				Y += v.Y;
				Z += v.Z;

				return (*this);
			}

			VectorA<T, 3>& operator*=(T d)
			{
				X *= d;
				Y *= d;
				Z *= d;

				return (*this);
			}

			VectorA<T, 3>& operator*=(VectorA<T, 3> const& v)
			{
				X *= v.X;
				Y *= v.Y;
				Z *= v.Z;

				return (*this);
			}

			VectorA<T, 3>& operator/=(T d)
			{
				X /= d;
				Y /= d;
				Z /= d;

				return (*this);
			}

			VectorA<T, 3>& operator/=(VectorA<T, 3> const& v)
			{
				X /= v.X;
				Y /= v.Y;
				Z /= v.Z;

				return (*this);
			}

			VectorA<T, 3>& operator=(T d)
			{
				X = d;
				Y = d;
				Z = d;

				return (*this);
			}

			// do not need other = operators, since each vector type has the conversion operators
			VectorA<T, 3>& operator=(VectorA<T, 3> const& v)
			{
				if (this != &v)
				{
					X = v.X;
					Y = v.Y;
					Z = v.Z;
				}

				return (*this);
			}
			
			friend VectorA<T, 3> operator-(VectorA<T, 3> v, T d)
			{
				v -= d;
				return v;
			}

			friend VectorA<T, 3> operator-(VectorA<T, 3> v, VectorA<T, 3> const& oV)
			{
				v -= oV;
				return v;
			}

			friend VectorA<T, 3> operator+(VectorA<T, 3> v, T d)
			{
				v += d;
				return v;
			}

			friend VectorA<T, 3> operator+(VectorA<T, 3> v, VectorA<T, 3> const& oV)
			{
				v += oV;
				return v;
			}

			friend VectorA<T, 3> operator*(VectorA<T, 3> v, T d)
			{
				v *= d;
				return v;
			}

			friend VectorA<T, 3> operator*(VectorA<T, 3> v, VectorA<T, 3> const& oV)
			{
				v *= oV;
				return v;
			}

			friend VectorA<T, 3> operator/(VectorA<T, 3> v, T d)
			{
				v /= d;
				return v;
			}

			friend VectorA<T, 3> operator/(VectorA<T, 3> v, VectorA<T, 3> const& oV)
			{
				v /= oV;
				return v;
			}

			bool operator==(VectorA<T, 3> const& v)
			{
				return (X == v.X && Y == v.Y && Z == v.Z);
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
		using Vector3 = VectorA<T, 3>;

		using Float3 = Vector3<float>;
		using Int3 = Vector3<int>;
		using Uint3 = Vector3<uint>;
	}
}
