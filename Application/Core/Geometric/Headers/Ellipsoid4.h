#pragma once

#include "Ellipsoid.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct EllipsoidA<T, 4>
		{
			VectorA<T, 4> Cs;
			T R;
			VectorA<T, 4> O;

			EllipsoidA()
				: C1(T(1)), C2(T(1)), C3(T(1)), C4(T(1)), R(T(1)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T c1, T c2, T c3, T c4, T r = 1, VectorA<T, 4> o = VectorA<T, 4>(T(0)))
				: Cs(c1, c2, c3, c4), R(r), O(o)
			{}

			EllipsoidA(VectorA<T, 4> cs, T r = 1, VectorA<T, 4> o = VectorA<T, 4>(T(0)))
				: Cs(cs), R(r), O(o)
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T r, VectorA<T, 4> o = VectorA<T, 4>(T(0)))
				: Cs(T(1)), R(r), O(o)
			{}

			EllipsoidA(EllipsoidA<T, 2> const& e)
				: Cs(e.Cs), R(e.R), O(e.O)
			{}

			// conversions
			operator EllipsoidA<T, 2>()
			{
				return EllipsoidA<T, 2>(Cs, R, O);
			}

			operator EllipsoidA<T, 3>()
			{
				return EllipsoidA<T, 3>(Cs, R, O);
			}

			// methods
			Dimension<4> Dimensions() const
			{
				return Dimension<4>();
			}

			// operators
			EllipsoidA<T, 4>& operator-=(VectorA<T, 4> const& v)
			{
				O -= v;

				return (*this);
			}

			EllipsoidA<T, 4>& operator+=(VectorA<T, 4> const& v)
			{
				O += v;

				return (*this);
			}

			EllipsoidA<T, 4>& operator=(EllipsoidA<T, 4> const& e)
			{
				if (this != &e)
				{
					Cs = e.Cs;
					R = e.R;
					O = e.O;
				}

				return (*this);
			}

			friend EllipsoidA<T, 4> operator-(EllipsoidA<T, 4> e, VectorA<T, 4> const& v)
			{
				e -= v;
				return l;
			}

			friend EllipsoidA<T, 3> operator+(EllipsoidA<T, 4> e, VectorA<T, 4> const& v)
			{
				e += v;
				return l;
			}

			bool operator==(EllipsoidA<T, 4> const& e)
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
			EllipsoidA<T, 4>& Rotate(Quaternion<T> r)
			{
				// no implementation for rotating V4 by Quaternion

				return (*this);
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Ellipsoid4 = EllipsoidA<T, 4>;

		using Ellipsoid4F = Ellipsoid4<float>;
		using Ellipsoid4I = Ellipsoid4<int>;
		using Ellipsoid4UI = Ellipsoid4<uint>;
	}
}