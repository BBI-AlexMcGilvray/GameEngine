#pragma once

#include "Line.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct LineA<T, 3>
		{
			VectorA<T, 3> V;
			VectorA<T, 3> O;

			LineA()
				: V(T(1), T(0), T(0)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 3> v, VectorA<T, 3> o = VectorA<T, 2>(T(0)))
				: V(v), O(o)
			{}

			// plane represented by 2 vectors and origin
			LineA(VectorA<T, 3> p1, VectorA<T, 3> p2)
				: V(p2 - p1), O(p1)
			{}

			LineA(LineA<T, 2> const& l)
				: V(l.V), O(l.O)
			{}

			LineA(LineA<T, 3> const& l)
				: V(l.V), O(l.O)
			{}

			// conversions
			operator LineA<T, 2>()
			{
				return LineA<T, 2>(V, O);
			}

			operator LineA<T, 4>()
			{
				return LineA<T, 4>(V, O);
			}

			// methods
			Dimension<3> Dimensions() const
			{
				return Dimension<3>();
			}

			// operators
			LineA<T, 3>& operator-=(VectorA<T, 3> const& v)
			{
				O -= v;

				return (*this);
			}

			LineA<T, 3>& operator+=(VectorA<T, 3> const& v)
			{
				O += v;

				return (*this);
			}

			LineA<T, 3>& operator=(LineA<T, 3> const& l)
			{
				if (this != &p)
				{
					V = l.V;
					O = l.O;
				}

				return (*this);
			}

			friend LineA<T, 3> operator-(LineA<T, 3> l, VectorA<T, 3> const& v)
			{
				l -= v;
				return l;
			}

			friend LineA<T, 3> operator+(LineA<T, 3> l, VectorA<T, 3> const& v)
			{
				l += v;
				return l;
			}

			bool operator==(LineA<T, 3> const& l)
			{
				auto pointDirection = Direction(O, l.O);
				auto vNormalize = Normalize(V);
				auto lVNormalize = Normalize(l.V);

				bool vectorsEqual = (vNormalize == lVNormalize || -vNormalize == lVNormalize);
				bool pointsOnSameLine = (pointDirection == vNormalize || -pointDirection == vNormalize);

				return (vectorsEqual && pointsOnSameLine);
			}

			// other comparison operators have no meaning

			LineA<T, 3>& Rotate(Quaternion<T> r)
			{
				V = RotateVectorBy(V, r);

				return (*this);
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Line3 = LineA<T, 3>;

		using Line3F = Line3<float>;
		using Line3I = Line3<int>;
		using Line3UI = Line3<uint>;
	}
}