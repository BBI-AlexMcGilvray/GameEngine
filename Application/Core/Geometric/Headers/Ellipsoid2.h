#pragma once

#include "Ellipsoid.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct EllipsoidA<T, 2>
		{
			VectorA<T, 2> Cs;
			T R;
			VectorA<T, 2> O;

			EllipsoidA()
				: Cs(T(1)), R(T(1)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T c1, T c2, T r = 1, VectorA<T, 2> o = VectorA<T, 2>(T(0)))
				: Cs(c1, c2), R(r), O(o)
			{}

			EllipsoidA(VectorA<T, 2> cs, T r = 1, VectorA<T, 2> o = VectorA<T, 2>(T(0)))
				: Cs(cs), R(r), O(o)
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T r, VectorA<T, 2> o = VectorA<T, 2>(T(0)))
				: Cs(T(1)), R(r), O(o)
			{}

			EllipsoidA(EllipsoidA<T, 2> const& e)
				: Cs(e.Cs), R(e.R), O(e.O)
			{}

			// conversions
			operator EllipsoidA<T, 3>()
			{
				return EllipsoidA<T, 3>(Cs, R, O);
			}

			operator EllipsoidA<T, 4>()
			{
				return EllipsoidA<T, 4>(Cs, R, O);
			}

			// methods
			Dimension<2> Dimensions() const
			{
				return Dimension<2>();
			}

			// operators
			EllipsoidA<T, 2>& operator-=(VectorA<T, 2> const& v)
			{
				O -= v;

				return (*this);
			}

			EllipsoidA<T, 2>& operator+=(VectorA<T, 2> const& v)
			{
				O += v;

				return (*this);
			}

			EllipsoidA<T, 2>& operator=(EllipsoidA<T, 2> const& e)
			{
				if (this != &e)
				{
					Cs = e.Cs;
					R = e.R;
					O = e.O;
				}

				return (*this);
			}

			friend EllipsoidA<T, 2> operator-(EllipsoidA<T, 2> e, VectorA<T, 2> const& v)
			{
				e -= v;
				return l;
			}

			friend EllipsoidA<T, 2> operator+(EllipsoidA<T, 2> e, VectorA<T, 2> const& v)
			{
				e += v;
				return l;
			}

			bool operator==(EllipsoidA<T, 2> const& e)
			{
				return (Cs == e.Cs && R == e.R && O == e.O);
			}

			// other comparison operators have no meaning

			T& operator[](int axis)
			{
				return Cs[axis];
			}

			T operator[](int axis) const
			{
				return Cs[axis];
			}

			// This rotation function just alters the SHAPE of the ellipsoid, NOT the actual orientation
			EllipsoidA<T, 2>& Rotate(Quaternion<T> r)
			{
				VectorA<T, 3> rotatedCoefficients = RotateVectorBy(Cs, r);

				Cs = rotatedCoefficients;

				return (*this);
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Ellipsoid2 = EllipsoidA<T, 2>;

		using Ellipsoid2F = Ellipsoid2<float>;
		using Ellipsoid2I = Ellipsoid2<int>;
		using Ellipsoid2UI = Ellipsoid2<uint>;
	}
}