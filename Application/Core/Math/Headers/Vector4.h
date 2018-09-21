#pragma once

#include "Vector.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct VectorA<T, 4>
		{
			union
			{
				struct
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
						VectorA<T, 3> XYZ;
					};
					T W;
				};
				T Axes[4];
			};

			VectorA(T d = 0)
				: X(d), Y(d), Z(d), W(d)
			{}

			VectorA(T x, T y, T z, T w)
				: X(x), Y(y), Z(z), W(w)
			{}

			VectorA(VectorA<T, 2> const& v, T d1 = 0, T d2 = 0)
				: XY(v), Z(d1), W(d2)
			{}

			VectorA(VectorA<T, 3> const& v, T d = 0)
				: XYZ(v), W(d)
			{}

			VectorA(VectorA<T, 4> const& v)
				: X(v.X), Y(v.Y), Z(v.Z), W(v.W)
			{}

			// conversions
			operator VectorA<T, 2>()
			{
				return XY;
			}

			operator VectorA<T, 3>()
			{
				return XYZ;
			}

			// methods
			Dimension<4> Dimensions() const
			{
				return Dimension<4>();
			}

			// operators
			VectorA<T, 4>& operator-=(VectorA<T, 4> const& v)
			{
				X -= v.X;
				Y -= v.Y;
				Z -= v.Z;
				W -= v.W;

				return (*this);
			}

			VectorA<T, 4>& operator+=(VectorA<T, 4> const& v)
			{
				X += v.X;
				Y += v.Y;
				Z += v.Z;
				W += v.w;

				return (*this);
			}

			VectorA<T, 4>& operator*=(T d)
			{
				X *= d;
				Y *= d;
				Z *= d;
				W *= d;

				return (*this);
			}

			VectorA<T, 4>& operator*=(VectorA<T, 4> const& v)
			{
				X *= v.X;
				Y *= v.Y;
				Z *= v.Z;
				W *= v.W;

				return (*this);
			}

			VectorA<T, 4>& operator/=(T d)
			{
				X /= d;
				Y /= d;
				Z /= d;
				W /= d;

				return (*this);
			}

			VectorA<T, 4>& operator/=(VectorA<T, 4> const& v)
			{
				X /= v.X;
				Y /= v.Y;
				Z /= v.Z;
				W /= v.W;

				return (*this);
			}

			VectorA<T, 4>& operator=(T d)
			{
				X = d;
				Y = d;
				Z = d;
				W = d;

				return (*this);
			}

			// do not need other = operators, since each vector type has the conversion operators
			VectorA<T, 4>& operator=(VectorA<T, 4> const& v)
			{
				if (this != &v)
				{
					X = v.X;
					Y = v.Y;
					Z = v.Z;
					W = v.W;
				}

				return (*this);
			}

			friend VectorA<T, 4> operator-(VectorA<T, 4> v, T d)
			{
				v -= d;
				return v;
			}

			friend VectorA<T, 4> operator-(VectorA<T, 4> v, VectorA<T, 4> const& oV)
			{
				v -= oV;
				return v;
			}

			friend VectorA<T, 4> operator+(VectorA<T, 4> v, T d)
			{
				v += d;
				return v;
			}

			friend VectorA<T, 4> operator+(VectorA<T, 4> v, VectorA<T, 4> const& oV)
			{
				v += oV;
				return v;
			}

			friend VectorA<T, 4> operator*(VectorA<T, 4> v, T d)
			{
				v *= d;
				return v;
			}

			friend VectorA<T, 4> operator*(VectorA<T, 4> v, VectorA<T, 4> const& oV)
			{
				v *= oV;
				return v;
			}

			friend VectorA<T, 4> operator/(VectorA<T, 4> v, T d)
			{
				v /= d;
				return v;
			}

			friend VectorA<T, 4> operator/(VectorA<T, 4> v, VectorA<T, 4> const& oV)
			{
				v /= oV;
				return v;
			}

			bool operator==(VectorA<T, 4> const& v)
			{
				return (X == v.X && Y == v.Y && Z == v.Z && W == v.W);
			}

			bool operator!=(VectorA<T, 4> const& v)
			{
				return (X != v.X || Y != v.Y || Z != v.Z || W != v.W);
			}

			// add in other comparison operators

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
		using Vector4 = VectorA<T, 4>;

		using Float4 = Vector4<float>;
		using Int4 = Vector4<int>;
		using Uint4 = Vector4<uint>;
	}
}
