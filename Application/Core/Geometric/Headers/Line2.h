#pragma once

#include "Line.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct LineA<T, 2>
		{
			VectorA<T, 2> V;
			VectorA<T, 2> P;

			LineA()
				: V(T(1), T(0)), P(T(0))
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 2> v, VectorA<T, 2> p = VectorA<T, 2>(T(0)))
				: V(v), P(p)
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 2> p1, VectorA<T, 2> p2)
				: V(p2 - p1), P(p1)
			{}

			LineA(LineA<T, 2> const& l)
				: V(l.V), P(l.P)
			{}

			// methods
			Dimension<2> Dimensions()
			{
				return Dimension<2>;
			}

			// operators
			LineA<T, 2>& operator-=(VectorA<T, 2> const& v)
			{
				P -= v;

				return (*this);
			}

			LineA<T, 2>& operator+=(VectorA<T, 2> const& v)
			{
				P += v;

				return (*this);
			}

			LineA<T, 2>& operator=(LineA<T, 2> const& l)
			{
				if (this != &p)
				{
					V = l.V;
					P = l.P;
				}

				return (*this);
			}

			friend LineA<T, 2> operator-(LineA<T, 2> l, VectorA<T, 2> const& v)
			{
				l -= v;
				return l;
			}

			friend LineA<T, 2> operator+(LineA<T, 2> l, VectorA<T, 2> const& v)
			{
				l += v;
				return l;
			}

			bool operator==(LineA<T, 2> const& l)
			{
				auto pointDirection = Direction(P, l.P);
				auto vNormalize = Normalize(V);
				auto lVNormalize = Normalize(l.V);

				bool vectorsEqual = (vNormalize == lVNormalize || -vNormalize == lVNormalize);
				bool pointsOnSameLine = (pointDirection == vNormalize || -pointDirection == vNormalize);

				return (vectorsEqual && pointsOnSameLine);
			}

			// other comparison operators have no meaning

			LineA<T, 2>& Rotate(Quaternion<T> r)
			{
				V = RotateVectorBy(V, r);

				return (*this);
			}

			VectorA<T, A> SubstituteInCoefficient(T coefficient)
			{
				return (P + (coefficient * V));
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Line2 = LineA<T, 2>;

		using Line2F = Line2<float>;
		using Line2I = Line2<int>;
		using Line2UI = Line2<uint>;
	}
}