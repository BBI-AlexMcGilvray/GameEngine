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
			VectorA<T, 4> O;

			LineA()
				: V(T(1), T(0), T(0), T(0)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 4> v, VectorA<T, 4> o = VectorA<T, 2>(T(0)))
				: V(v), O(o)
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 4> p1, VectorA<T, 4> p2)
				: V(p2 - p1), O(p1)
			{}

			LineA(LineA<T, 2> const& l)
				: V(l.V), O(l.O)
			{}

			LineA(LineA<T, 3> const& l)
				: V(l.V), O(l.O)
			{}

			LineA(LineA<T, 4> const& l)
				: V(l.V), O(l.O)
			{}

			// conversions
			operator LineA<T, 2>()
			{
				return LineA<T, 2>(V, O);
			}

			operator LineA<T, 3>()
			{
				return LineA<T, 3>(V, O);
			}

			// methods
			Dimension<4> Dimensions() const
			{
				return Dimension<4>();
			}

			// operators
			LineA<T, 4>& operator-=(VectorA<T, 4> const& v)
			{
				O -= v;

				return (*this);
			}

			LineA<T, 4>& operator+=(VectorA<T, 4> const& v)
			{
				O += v;

				return (*this);
			}

			LineA<T, 4>& operator=(LineA<T, 4> const& l)
			{
				if (this != &p)
				{
					V = l.V;
					O = l.O;
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
				auto pointDirection = Direction(O, l.O);
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
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Line4 = LineA<T, 3>;

		using Line4F = Line4<float>;
		using Line4I = Line4<int>;
		using Line4UI = Line4<uint>;
	}
}