#pragma once

#include "Vector.h"

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

		VectorA(VectorA<T, 4>& v)
			: X(v.X), Y(v.Y), Z(v.Z), W(v.W)
		{}

		T Dot(VectorA<T, 4> const& v)
		{
			auto temp = v;
			temp * (*this);

			return (temp.X + temp.Y + temp.Z + temp.W);
		}

		template <typename T>
		VectorA<T, 4> Min(VectorA<T, 4> const& v, T d)
		{
			VectorA<T, 4> minV(Min(v.X, d), Min(v.Y, d), Min(v.Z, d), Min(v.W, d));

			return minV;
		}

		template <typename T>
		VectorA<T, 4> Min(VectorA<T, 4> const& v1, VectorA<T, 4> const& v2)
		{
			VectorA<T, 4> minV(Min(v1.X, v2.X), Min(v1.Y, v2.Y), Min(v1.Z, v2.Z), Min(v1.W, v2.W));

			return minV;
		}

		template <typename T>
		VectorA<T, 4> Max(VectorA<T, 4> const& v, T d)
		{
			VectorA<T, 4> maxV(Max(v.X, d), Max(v.Y, d), Max(v.Z, d), Max(v.W, d));

			return maxV;
		}

		template <typename T>
		VectorA<T, 4> Max(VectorA<T, 4> const& v1, VectorA<T, 4> const& v2)
		{
			VectorA<T, 4> maxV(Max(v1.X, v2.X), Max(v1.Y, v2.Y), Max(v1.Z, v2.Z), Max(v1.W, v2.W));

			return maxV;
		}


		template <typename T>
		VectorA<T, 4> Clamp(VectorA<T, 4> const& v, T d1, T d2)
		{
			VectorA<T, 4> clampV(Clamp(v1.X, d1, d2), Clamp(v1.Y, d1, d2), Clamp(v1.Z, d1, d2), Clamp(v1.W, d1, d2));

			return clampV;
		}

		template <typename T>
		VectorA<T, 4> Clamp(VectorA<T, 4> const& v1, VectorA<T, 4> const& v2, VectorA<T, 4> const& v3)
		{
			VectorA<T, 4> clampV(Clamp(v1.X, v2.X, v3.X), Clamp(v1.Y, v2.Y, v3.Y), Clamp(v1.Z, v2.Z, v3.Z), Clamp(v1.W, v2.W, v3.W));

			return clampV;
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
};
