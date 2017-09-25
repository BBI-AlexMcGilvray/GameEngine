#pragma once

#include "Vector.h"

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

		T Dot(VectorA<T, 3> const& v)
		{
			auto temp = v;
			temp * (*this);

			return (temp.X + temp.Y + temp.X);
		}

		template <typename T>
		VectorA<T, 3> Min(VectorA<T, 3> const& v, T d)
		{
			VectorA<T, 3> minV(Min(v.X, d), Min(v.Y, d), Min(v.Z, d));

			return minV;
		}

		template <typename T>
		VectorA<T, 3> Min(VectorA<T, 3> const& v1, VectorA<T, 3> const& v2)
		{
			VectorA<T, 3> minV(Min(v1.X, v2.X), Min(v1.Y, v2.Y), Min(v1.Z, v2.Z));

			return minV;
		}

		template <typename T>
		VectorA<T, 3> Max(VectorA<T, 3> const& v, T d)
		{
			VectorA<T, 3> maxV(Max(v.X, d), Max(v.Y, d), Max(v.Z, d));

			return maxV;
		}

		template <typename T>
		VectorA<T, 3> Max(VectorA<T, 3> const& v1, VectorA<T, 3> const& v2)
		{
			VectorA<T, 3> maxV(Max(v1.X, v2.X), Max(v1.Y, v2.Y), Max(v1.Z, v2.Z));

			return maxV;
		}


		template <typename T>
		VectorA<T, 3> Clamp(VectorA<T, 3> const& v, T d1, T d2)
		{
			VectorA<T, 3> clampV(Clamp(v1.X, d1, d2), Clamp(v1.Y, d1, d2), Clamp(v1.Z, d1, d2));

			return clampV;
		}

		template <typename T>
		VectorA<T, 3> Clamp(VectorA<T, 3> const& v1, VectorA<T, 3> const& v2, VectorA<T, 3> const& v3)
		{
			VectorA<T, 3> clampV(Clamp(v1.X, v2.X, v3.X), Clamp(v1.Y, v2.Y, v3.Y), Clamp(v1.Z, v2.Z, v3.Z));

			return clampV;
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
};
