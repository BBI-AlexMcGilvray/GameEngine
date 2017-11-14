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
								VectorA<T, 2> XY[2];
							};
							T Z;
						};
						VectorA<T, 3> XYZ[3];
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

			VectorA(VectorA<T, 4> const& v)
				: X(v.X), Y(v.Y), Z(v.Z), W(v.W)
			{}

			// methods
			Dimension<4> Dimensions()
			{
				return Dimension<4>;
			}

			T MagnitudeSqr()
			{
				return Dot(*this);
			}

			T Magnitude()
			{
				return sqrt(MagnitudeSqr);
			}

			VectorA<T, 4>& Normalize()
			{
				return ((*this) /= (Magnitude()));
			}

			T Dot(VectorA<T, 4> const& v)
			{
				auto temp = v;
				temp * (*this);

				return (temp.X + temp.Y + temp.Z + temp.W);
			}

			template <typename T>
			VectorA<T, 4>& Min(T d)
			{
				X = Min(X, d);
				Y = Min(Y, d);
				Z = Min(Z, d);
				W = Min(W, d);

				return (*this);
			}

			template <typename T>
			VectorA<T, 4>& Min(VectorA<T, 4> const& v1)
			{
				X = Min(X, v1.X);
				Y = Min(Y, v1.Y);
				Z = Min(Z, v1.Z);
				W = Min(W, v1.W);

				return (*this);
			}

			template <typename T>
			VectorA<T, 4>& Max(T d)
			{
				X = Max(X, d);
				Y = Max(Y, d);
				Z = Max(Z, d);
				W = Max(W, d);

				return (*this);
			}

			template <typename T>
			VectorA<T, 4>& Max(VectorA<T, 4> const& v1)
			{
				X = Max(X, v1.X);
				Y = Max(Y, v1.Y);
				Z = Max(Z, v1.Z);
				W = Max(W, v1.W);

				return (*this);
			}


			template <typename T>
			VectorA<T, 4>& Clamp(T d1, T d2)
			{
				X = Clamp(X, d1, d2);
				Y = Clamp(Y, d1, d2);
				Z = Clamp(Z, d1, d2);
				W = Clamp(W, d1, d2);

				return (*this);
			}

			template <typename T>
			VectorA<T, 4>& Clamp(VectorA<T, 4> const& v1, VectorA<T, 4> const& v2)
			{
				VectorA<T, 4> clampV(Clamp(X, v1.X, v2.X), Clamp(Y, v1.Y, v2.Y), Clamp(Z, v1.Z, v2.Z), Clamp(W, v1.W, v2.W));

				return clampV;
			}

			// operators
			VectorA<T, 4>& operator-=(T d)
			{
				return (this = this - d);
			}

			VectorA<T, 4>& operator-=(VectorA<T, 4> const& v)
			{
				return (this = this - v);
			}

			VectorA<T, 4>& operator+=(T d)
			{
				return (this = this + d);
			}

			VectorA<T, 4>& operator+=(VectorA<T, 4> const& v)
			{
				return (this = this + v);
			}

			VectorA<T, 4>& operator*=(T d)
			{
				return (this = this * d);
			}

			VectorA<T, 4>& operator*=(VectorA<T, 4> const& v)
			{
				return (this = this * v);
			}

			VectorA<T, 4>& operator/=(T d)
			{
				return (this = this / d);
			}

			VectorA<T, 4>& operator/=(VectorA<T, 4> const& v)
			{
				return (this = this / v);
			}

			VectorA<T, 4>& operator-(VectorA<T, 4> const& v)
			{
				X -= v.X;
				Y -= v.Y;
				Z -= v.Z;
				W -= v.W;

				return *this;
			}

			VectorA<T, 4>& operator+(VectorA<T, 4> const& v)
			{
				X += v.X;
				Y += v.Y;
				Z += v.Z;
				W += v.W;

				return *this;
			}

			VectorA<T, 4>& operator*(T d)
			{
				X *= d;
				Y *= d;
				Z *= d;
				W *= d;

				return *this;
			}

			VectorA<T, 4>& operator*(VectorA<T, 4> const& v)
			{
				X *= v.X;
				Y *= v.Y;
				Z *= v.Z;
				W *= v.W;

				return *this;
			}

			VectorA<T, 4>& operator/(T d)
			{
				X /= d;
				Y /= d;
				Z /= d;
				W /= d;

				return *this;
			}

			VectorA<T, 4>& operator/(VectorA<T, 4> const& v)
			{
				X /= v.X;
				Y /= v.Y;
				Z /= v.Z;
				W /= v.W;

				return *this;
			}

			VectorA<T, 4>& operator=(T d)
			{
				X = d;
				Y = d;
				Z = d;
				W = d;

				return *this;
			}

			VectorA<T, 4>& operator=(VectorA<T, 4> const& v)
			{
				X = v.X;
				Y = v.Y;
				Z = v.Z;
				W = v.W;

				return *this;
			}

			bool operator==(VectorA<T, 4> const& v)
			{
				return (X == v.X && Y == v.Y && Z == v.Z && W == v.W);
			}

			T& operator[](int axis)
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
