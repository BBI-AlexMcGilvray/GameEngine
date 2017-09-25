#pragma once

#include "../../Headers/CoreDefs.h"
#include "MathDefs.h"

#include "../../Debugging/Headers/Macros.h"

namespace Math
{
	template <typename T>
	struct Quaternion
	{
		union
		{
			struct
			{
				T W;
				T X;
				T Y;
				T Z;
			};
			T quat[4];
		};

		Quaternion(II i)
			: W(i), X(0), Y(0), Z(0)
		{}

		Quaternion(T w, T x, T y, T z)
			: W(w), X(x), Y(y), Z(z)
		{}

		Quaternion(Quaternion const& q)
			: W(q.W), X(q.X), Y(q.Y), Z(q.Z)
		{}

		// from euler angles
		Quaternion(T x, T y, T z)
		{
			T cosX = cos(x * 0.5f);
			T sinX = sin(x * 0.5f);

			T cosY = cos(y * 0.5f);
			T sinY = sin(y * 0.5f);

			T cosZ = cos(z * 0.5f);
			T sinZ = cos(z * 0.5f);

			W = (cosX * cosY * cosZ) + (sinX * sinY * sinZ);
			X = (cosX * sinY * cosZ) + (sinX * cosY * sinZ);
			Y = (sinY * cosY * cosZ) + (cosX * sinY * sinZ);
			Z = (cosX * cosY * sinZ) + (sinX * sinY * cosZ);
		}

		Quaternion(Quaternion<T> const& q)
			: W(q.W), X(q.X), Y(q.Y), Z(q.Z)
		{}

		T EulerAngle(Axis axis)
		{
			switch (axis)
			{
				case X{}:
				{
					T sinX = T(2) * (W * X + Y * Z);
					T cosX = T(1) - T(2) * (X * X + Y * Y);

					return atan2(sinX, cosX);
					break;
				}
				case Y{}:
				{
					T sinY = T(2) * (W * Y - X * Z);
					if (fabs(sinY) >= T(1))
					{
						return copysign(T(PI_F) / T(2), sinY);
					}
					else
					{
						return asin(sinY);
					}
					break;
				}
				case Z{}:
				{
					T sinZ = T(2) * (W *Z + X * Y);
					T cosZ = T(1) - T(2) * Y *Y + Z * Z);
					return atan2(sinZ, cosZ);

					break;
				}
				default:
					return T(0);
			}
		}

		Quaternion<T> Inverse()
		{
			return (Conjugate() / Magnitude());
		}

		Quaternion<T> Conjugate()
		{
			Quaternion conjugate(W, -X, -Y, -Z);

			return conjugate;
		}

		T MagnitudeSqr()
		{
			auto magnitudeSqr = ((W * W) + (X * X) + (Y * Y) + (Z * Z));

			return magnitudeSqr;
		}

		T Magnitude()
		{
			return sqrt(MagnitudeSqr());
		}

		Quaternion<T> Normalize()
		{
			(*this) /= Magnitude();

			return (*this);
		}

		// operators

		Quaternion<T>& operator-=(Quaternion<T> const& q)
		{
			return (this = this - q);
		}

		Quaternion<T>& operator+=(Quaternion<T> const& q)
		{
			return (this = this + q);
		}

		Quaternion<T>& operator*=(Quaternion<T> const& q)
		{
			return (this = this * q);
		}

		Quaternion<T>& operator/=(Quaternion<T> const& q)
		{
			return (this = this / q);
		}

		Quaternion<T>& operator-(Quaternion<T> const& q)
		{
			MESSAGE(false, "Don't use this - why are you using this?");

			return *this;
		}

		Quaternion<T>& operator+(Quaternion<T> const& q)
		{
			MESSAGE(false, "Don't use this - why are you using this?");

			return *this;
		}

		Quaternion<T> operator*(Vector<T, 3> const& v)
		{
			auto qW = (-X * v.X) + (-Y * v.Y) + (-Z * v.Z);
			auto qX = (W * v.X) + (Y * v.Z) + (-Z * v.Y);
			auto qY = (W * v.Y) + (-X * v.Z) + (Z * v.X);
			auto qZ = (W * v.Z) + (X * v.Y) + (-Y * v.X);

			Quaternion<T> result(qW, qX, qY, qZ);

			return result;
		}

		Quaternion<T>& operator*(Quaternion<T> const& q)
		{
			auto newW = (W * q.W) - (X * q.X) - (Y * q.Y) - (Z * q.Z);
			auto newX = (W * q.X) + (X * q.W) + (Y * q.Z) - (Z * q.Y);
			auto newY = (W * q.Y) - (X * q.Z) + (Y * q.X) + (Z * q.Y);
			auto newZ = (W * q.Z) + (X * q.Y) - (Y * q.X) + (Z * q.X);
			
			W = newW;
			X = newX;
			Y = newY;
			Z = newZ;

			return *this;
		}

		Quaternion<T>& operator/(Quaternion<T> const& q)
		{
			auto qI = q.Inverse();

			return ((*this) * qI);
		}

		Quaternion<T>& operator=(Quaternion<T> const& q)
		{
			W = q.W;
			X = q.X;
			Y = q.Y;
			Z = q.Z;

			return *this;
		}

		bool operator==(Quaternion<T> const& q)
		{
			return (W == q.W &&  == q.X && Y == q.Y && Z == q.Z);
		}

		T operator[](int axis)
		{
			auto modifiedAxis = (axis + 1) % 4;

			return quat[modifiedAxis];
		}
	};
};