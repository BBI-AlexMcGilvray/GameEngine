#pragma once

#include "Line.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct LineA<T, 4>
		{
			VectorA<T, 4> V;
			VectorA<T, 4> P;

			LineA()
				: V(T(1), T(0), T(0), T(0)), P(T(0))
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 4> v, VectorA<T, 4> p = VectorA<T, 2>(T(0)))
				: V(v), P(p)
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 4> p1, VectorA<T, 4> p2)
				: V(p2 - p1), P(p1)
			{}

			LineA(LineA<T, 2> const& l)
				: V(l.V), P(l.P)
			{}

			LineA(LineA<T, 3> const& l)
				: V(l.V), P(l.P)
			{}

			LineA(LineA<T, 4> const& l)
				: V(l.V), P(l.P)
			{}

			// methods
			Dimension<4> Dimensions()
			{
				return Dimension<4>;
			}

			// operators
			LineA<T, 4>& operator-=(VectorA<T, 4> const& v)
			{
				P -= v;

				return (*this);
			}

			LineA<T, 4>& operator+=(VectorA<T, 4> const& v)
			{
				P += v;

				return (*this);
			}

			LineA<T, 4>& operator=(LineA<T, 4> const& l)
			{
				if (this != &p)
				{
					V = l.V;
					P = l.P;
				}

				return (*this);
			}

			friend LineA<T, 4> operator-(LineA<T, 4> l, VectorA<T, 4> const& v)
			{
				l -= v;
				return l;
			}

			friend LineA<T, 4> operator+(LineA<T, 4> l, VectorA<T, 4> const& v)
			{
				l += v;
				return l;
			}

			bool operator==(LineA<T, 4> const& l)
			{
				auto pointDirection = Direction(P, l.P);
				auto vNormalize = Normalize(V);
				auto lVNormalize = Normalize(l.V);

				bool vectorsEqual = (vNormalize == lVNormalize || -vNormalize == lVNormalize);
				bool pointsOnSameLine = (pointDirection == vNormalize || -pointDirection == vNormalize);

				return (vectorsEqual && pointsOnSameLine);
			}

			// other comparison operators have no meaning

			LineA<T, 4>& Rotate(Quaternion<T> r)
			{
				// no implementation for rotating V4 by Quaternion

				return (*this);
			}

			VectorA<T, A> SubstituteInCoefficient(T coefficient)
			{
				return (P + (coefficient * V));
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Line4 = LineA<T, 3>;

		using Line4F = Line4<float>;
		using Line4I = Line4<int>;
		using Line4UI = Line4<uint>;
	}
}