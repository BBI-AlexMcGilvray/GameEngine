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
						VectorA<T, 2> XY[2];
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

			VectorA(VectorA<T, 3> const& v)
				: X(v.X), Y(v.Y), Z(v.Z)
			{}

			// methods
			Dimension<3> Dimensions()
			{
				return Dimension<3>;
			}

			T MagnitudeSqr()
			{
				return Dot(*this);
			}

			T Magnitude()
			{
				return sqrt(MagnitudeSqr);
			}

			VectorA<T, 3>& Normalize()
			{
				return ((*this) /= (Magnitude()));
			}

			T Dot(VectorA<T, 3> const& v)
			{
				auto temp = v;
				temp * (*this);

				return (temp.X + temp.Y + temp.X);
			}

			template <typename T>
			VectorA<T, 3>& Min(T d)
			{
				X = Min(X, d);
				Y = Min(Y, d);
				Z = Min(Z, d);

				return (*this);
			}

			template <typename T>
			VectorA<T, 3>& Min(VectorA<T, 3> const& v1)
			{
				X = Min(X, v1.X);
				Y = Min(Y, v1.Y);
				Z = Min(Z, v1.Z);

				return (*this);
			}

			template <typename T>
			VectorA<T, 3>& Max(T d)
			{
				X = Max(X, d);
				Y = Max(Y, d);
				Z = Max(Z, d);

				return (*this);
			}

			template <typename T>
			VectorA<T, 3>& Max(VectorA<T, 3> const& v1)
			{
				X = Max(X, v1.X);
				Y = Max(Y, v1.Y);
				Z = Max(Z, v1.Z);

				return (*this);
			}


			template <typename T>
			VectorA<T, 3>& Clamp(T d1, T d2)
			{
				X = Clamp(X, d1, d2);
				Y = Clamp(Y, d1, d2);
				Z = Clamp(Z, d1, d2);

				return (*this);
			}

			template <typename T>
			VectorA<T, 3>& Clamp(VectorA<T, 3> const& v1, VectorA<T, 3> const& v2)
			{
				X = Clamp(X, v1.X, v2.X);
				Y = Clamp(Y, v1.Y, v2.Y);
				Z = Clamp(Z, v1.Z, v2.Z);

				return (*this);
			}

			// operators
			VectorA<T, 3>& operator-=(T d)
			{
				return (this = this - d);
			}

			VectorA<T, 3>& operator-=(VectorA<T, 3> const& v)
			{
				return (this = this - v);
			}

			VectorA<T, 3>& operator+=(T d)
			{
				return (this = this + d);
			}

			VectorA<T, 3>& operator+=(VectorA<T, 3> const& v)
			{
				return (this = this + v);
			}

			VectorA<T, 3>& operator*=(T d)
			{
				return (this = this * d);
			}

			VectorA<T, 3>& operator*=(VectorA<T, 3> const& v)
			{
				return (this = this * v);
			}

			VectorA<T, 3>& operator/=(T d)
			{
				return (this = this / d);
			}

			VectorA<T, 3>& operator/=(VectorA<T, 3> const& v)
			{
				return (this = this / v);
			}

			VectorA<T, 3>& operator-(VectorA<T, 3> const& v)
			{
				X -= v.X;
				Y -= v.Y;
				Z -= v.Z;

				return *this;
			}

			VectorA<T, 3>& operator+(VectorA<T, 3> const& v)
			{
				X += v.X;
				Y += v.Y;
				Z += v.Z;

				return *this;
			}

			VectorA<T, 3>& operator*(T d)
			{
				X *= d;
				Y *= d;
				Z *= d;

				return *this;
			}

			VectorA<T, 3>& operator*(VectorA<T, 3> const& v)
			{
				X *= v.X;
				Y *= v.Y;
				Z *= v.Z;

				return *this;
			}

			VectorA<T, 3>& operator/(T d)
			{
				X /= d;
				Y /= d;
				Z /= d;

				return *this;
			}

			VectorA<T, 3>& operator/(VectorA<T, 3> const& v)
			{
				X /= v.X;
				Y /= v.Y;
				Z /= v.Z;

				return *this;
			}

			VectorA<T, 3>& operator=(T d)
			{
				X = d;
				Y = d;
				Z = d;

				return *this;
			}

			VectorA<T, 3>& operator=(VectorA<T, 3> const& v)
			{
				X = v.X;
				Y = v.Y;
				Z = v.Z;

				return *this;
			}

			bool operator==(VectorA<T, 3> const& v)
			{
				return (X == v.X && Y == v.Y && Z == v.Z);
			}

			T& operator[](int axis)
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
