#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/Math/Headers/MathDefs.h"
#include "Core/Math/Headers/Vector3.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Core
{
	namespace Math
	{
		/*
		NOTES: (https://en.wikipedia.org/wiki/Quaternions_and_spatial_rotation)
			Quaternions, represented by (w, x, y, z), w + xi + yj + zk, or (w, u) - where u is a vector = (x, y, z),
			represent the ROTATION of ANGLE w AROUND THE AXIS (x, y, z) CLOCKWISE (assuming we are looking in the direction (x, y, z)

			Thus, when you multiply them by a vector (v), which is equivalent to a quaternion (0, v) (or: a rotation of NO ANGLE AROUND THE AXIS v,
			you are calculating the final result, which is a COMBINATION (initial state (0, v) being modified by state (w, u)) of rotations which
			results in a final state of (r, n) where n represents the axis v after it has been mapped through the transformation of (w, u).

			In other words, combining quaternion states gives us the final state, the vector part of which is the final axis - which represents the
			transformed vector part of the initial state. Which, in the case of direction, gives us our final direction after the initial direction
			was rotated by the quaternion

			Rotating a vector, v, by quaternion, q, gives us the equation v' = qvq' because one transformation (qv - first v then q) is equivalent
			to another transformation (v'q - first q then inverse of v), so we have v'q = qv which is equivalent to v' = qvq'
		*/

		template <typename T>
		struct Quaternion
		{
			union
			{
				struct
				{
					T W;
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
								T XY[2];
							};
							T Z;
						};
						T XYZ[3];
					};
				};
				T quat[4];
			};

			Quaternion()
				: Quaternion(II())
			{}

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

			// operators
			Quaternion<T>& operator-=(Quaternion<T> const& q)
			{
				MESSAGE(false, "Don't use this - why are you using this?");

				return (*this);
			}

			Quaternion<T>& operator+=(Quaternion<T> const& q)
			{
				MESSAGE(false, "Don't use this - why are you using this?");

				return (*this);
			}

			Quaternion<T>& operator*=(Quaternion<T> const& q)
			{
				W *= q.W;
				X *= q.X;
				Y *= q.Y;
				Z *= q.Z;

				return (*this);
			}

			Quaternion<T>& operator/=(T d)
			{
				W /= d;
				X /= d;
				Y /= d;
				Z /= d;
				return (*this);
			}

			Quaternion<T>& operator/=(Quaternion<T> const& q)
			{
				T qMagnitude = Sqrt((q.W * q.W) + (q.X * q.X) + (q.Y * q.Y) + (q.Z * q.Z));

				Quaternion<T> qInverse;
				qInverse.W = q.W / qMagnitude;
				qInverse.X = q.X / qMagnitude;
				qInverse.Y = q.Y / qMagnitude;
				qInverse.Z = q.Z / qMagnitude;

				return ((*this) * qInverse);
			}

			Quaternion<T>& operator=(Quaternion<T> const& q)
			{
				W = q.W;
				X = q.X;
				Y = q.Y;
				Z = q.Z;

				return *this;
			}

			friend Quaternion<T> operator-(Quaternion<T> q, Quaternion<T> const& oQ)
			{
				MESSAGE(false, "Don't use this - why are you using this?");

				return q;
			}

			friend Quaternion<T> operator+(Quaternion<T> q, Quaternion<T> const& oQ)
			{
				MESSAGE(false, "Don't use this - why are you using this?");

				return q;
			}

			friend Quaternion<T> operator*(Quaternion<T> q, VectorA<T, 4> const& v)
			{
				auto qW = (-q.X * v.X) + (-q.Y * v.Y) + (-q.Z * v.Z);
				auto qX = (q.W * v.X) + (q.Y * v.Z) + (-q.Z * v.Y);
				auto qY = (q.W * v.Y) + (-q.X * v.Z) + (q.Z * v.X);
				auto qZ = (q.W * v.Z) + (q.X * v.Y) + (-q.Y * v.X);

				Quaternion<T> result(qW, qX, qY, qZ);

				return result;
			}

			friend Quaternion<T> operator*(Quaternion<T> q, Quaternion<T> const& oQ)
			{
				auto newW = (q.W * oQ.W) - (q.X * oQX) - (q.Y * oQ.Y) - (q.Z * oQ.Z);
				auto newX = (q.W * oQ.X) + (q.X * oQ.W) + (q.Y * oQ.Z) - (q.Z * oQ.Y);
				auto newY = (q.W * oQ.Y) - (q.X * oQ.Z) + (q.Y * oQ.X) + (q.Z * oQ.Y);
				auto newZ = (q.W * oQ.Z) + (q.X * oQ.Y) - (q.Y * qoQX) + (q.Z * oQ.X);

				W = newW;
				X = newX;
				Y = newY;
				Z = newZ;

				return *this;
			}

			friend Quaternion<T> operator/(Quaternion<T> q, T d)
			{
				q /= d;
				return q;
			}

			friend Quaternion<T> operator/(Quaternion<T> q, Quaternion<T> const& oQ)
			{
				q /= oQ;
				return q;
			}

			bool operator==(Quaternion<T> const& q)
			{
				return (W == q.W && == q.X && Y == q.Y && Z == q.Z);
			}

			T operator[](int axis)
			{
				auto modifiedAxis = (axis + 1) % 4;

				return quat[modifiedAxis];
			}
		};
		
		/*	TYPE DEFS	*/
		using FQuaternion = Quaternion<float>;
	}
}