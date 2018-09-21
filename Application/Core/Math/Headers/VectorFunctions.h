#pragma once

#include "Vector.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "MathUtils.h"

#include "Core/Debugging/Headers/Declarations.h"

namespace Core
{
	namespace Math
	{
		template <typename T, int D>
		bool Perpendicular(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			return (Dot(v1, v2) == T(0));
		}

		template <typename T, int D>
		bool Parallel(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			bool multipleSet = false;
			float multiple = 0.0f;

			if (Perpendicular(v1, v2))
			{
				return false;
			}

			for (int i = 0; i < D; i++)
			{
				if (v2[i] == T(0))
				{
					if (v1[i] == T(0))
					{
						continue;
					}

					return false;
				}

				if (v1[i] == T(0))
				{
					return false;
				}

				float newMultiple = float(v1[i]) / float(v2[i]);
				if (!multipleSet)
				{
					multiple = newMultiple;
					multipleSet = true;
				}
				else
				{
					if (multiple != newMultiple)
					{
						return false;
					}
				}
			}

			return true;
		}

		template <typename T, int D>
		bool SameDirection(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			if (Parallel(v1, v2))
			{
				return (Dot(v1, v2) >= T(0));
			}

			return false;
		}

		template <typename T, int D>
		T MagnitudeSqr(VectorA<T, D> const& v)
		{
			return Dot(v, v);
		}

		template <typename T, int D>
		T Magnitude(VectorA<T, D> const& v)
		{
			return Sqrt(MagnitudeSqr(v));
		}

		template <typename T, int D>
		VectorA<T, D> Normalize(VectorA<T, D> const& v)
		{
			return (v / Magnitude(v));
		}

		template <typename T, int D>
		VectorA<T, D> Min(VectorA<T, D> const& v, T d)
		{
			VectorA<T, D> minV;

			for (int i = 0; i < D; i++)
			{
				minV[i] = Min(v[i], d);
			}

			return minV;
		}

		template <typename T, int D>
		VectorA<T, D> Min(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			VectorA<T, D> minV;

			for (int i = 0; i < D; i++)
			{
				minV[i] = Min(v1[i], v2[i]);
			}

			return minV;
		}

		template <typename T, int D>
		VectorA<T, D> Shortest(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			auto v1MagSqr = MagnitudeSqr(v1);
			auto v2MagSqr = MagnitudeSqr(v2);

			if (v1MagSqr < v2MagSqr)
			{
				return v1;
			}
			return v2;
		}

		template <typename T, int D>
		VectorA<T, D> Max(VectorA<T, D> const& v, T d)
		{
			VectorA<T, D> maxV;

			for (int i = 0; i < D; i++)
			{
				maxV[i] = Max(v[i], d);
			}

			return maxV;
		}

		template <typename T, int D>
		VectorA<T, D> Max(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			VectorA<T, D> maxV;

			for (int i = 0; i < D; i++)
			{
				maxV[i] = Max(v1[i], v2[i]);
			}

			return maxV;
		}

		template <typename T, int D>
		VectorA<T, D> Longest(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			auto v1MagSqr = MagnitudeSqr(v1);
			auto v2MagSqr = MagnitudeSqr(v2);

			if (v1MagSqr > v2MagSqr)
			{
				return v1;
			}
			return v2;
		}

		template <typename T, int D>
		VectorA<T, D>& Clamp(VectorA<T, D> const& v, T d1, T d2)
		{
			VectorA<T, D> clampV;

			for (int i = 0; i < D; i++)
			{
				clampV[i] = Clamp(v[i], d);
			}

			return clampV;
		}

		template <typename T, int D>
		VectorA<T, D> Clamp(VectorA<T, D> const& v, VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			VectorA<T, D> clampV;

			for (int i = 0; i < D; i++)
			{
				clampV[i] = Clamp(v[i], v1[i], v2[i]);
			}

			return clampV;
		}

		template <typename T, int D>
		T Dot(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			T dot = 0;

			for (int i = 0; i < D; i++)
			{
				dot += (v1[i] * v2[i]);
			}

			return dot;
		}

		template <typename T, int D>
		Rad AngleBetweenVectors(VectorA<T, D> const& v1, VectorA<T, D> const& v2)
		{
			T dot = Dot(Normalize(v1), Normalize(v2));

			return Acos(dot);
		}

		template <typename T>
		Vector3<T> CrossProduct(Vector3<T> const& v1, Vector3<T> const& v2)
		{
			T crossX = (v1.Y * v2.Z) - (v1.Z * v2.Y);
			T crossY = (v1.Z * v2.X) - (v1.X * v2.Z);
			T crossZ = (v1.X * v2.Y) - (v1.Y * v2.X);

			return Vector3<T>(crossX, crossY, crossZ);
		}

		template <typename T, int A>
		VectorA<T, A> Project(VectorA<T, A> const& v1, VectorA<T, A> const& v2)
		{
			auto projection = v2;
			projection *= Dot(v1, v2);
			projection /= MagnitudeSqr(v2);

			return projection;
		}

		template <typename T, typename int A>
		VectorA<T, A> Perp(VectorA<T, A> const& v1, VectorA<T, A> const& v2)
		{
			return (v1 - Project(v1, v2));
		}

		template <typename T, typename int A>
		VectorA<T, A> Reject(VectorA<T, A> const& v1, VectorA<T, A> const& v2)
		{
			return Perp(v1, v2);
		}

		template <typename T, typename int A>
		T DistanceSqr(VectorA<T, A> const& v1, VectorA<T, A> const& v2)
		{
			return MagnitudeSqr(v2 - v1);
		}

		template <typename T, typename int A>
		T Distance(VectorA<T, A> const& v1, VectorA<T, A> const& v2)
		{
			return Sqrt(DistanceSqr(v1, v2));
		}

		template <typename T, typename int A>
		VectorA<T, A> Direction(VectorA<T, A> const& v1, VectorA<T, A> const& v2)
		{
			return Normalize(v2 - v1);
		}

#if DEBUG
		template <typename T, typename int A>
		String VectorString(VectorA<T, A> const& v)
		{
			String vectorInfo;

			vectorInfo += "(";
			for (auto i = 0; i < v.Dimensions(); i++)
			{
				vectorInfo += std::to_string(v[i]);

				if (i != v.Dimensions() - 1)
				{
					vectorInfo += ", ";
				}
			}
			vectorInfo += ")";

			return vectorInfo;
		}
#endif
	}
}