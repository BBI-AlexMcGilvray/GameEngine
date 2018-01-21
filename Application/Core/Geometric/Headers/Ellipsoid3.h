#pragma once

#include "Ellipsoid.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct EllipsoidA<T, 3>
		{
			VectorA<T, 3> Cs;
			T R;
			VectorA<T, 3> O;

			EllipsoidA()
				: Cs(T(1)), R(T(1)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T c1, T c2, T c3, T r = 1, VectorA<T, 3> o = VectorA<T, 3>(T(0)))
				: Cs(c1, c2, c3), R(r), O(o)
			{}

			EllipsoidA(VectorA<T, 3> cs, T r = 1, VectorA<T, 3> o = VectorA<T, 3>(T(0)))
				: Cs(cs), R(r), O(o)
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T r, VectorA<T, 3> o = VectorA<T, 3>(T(0)))
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

			operator EllipsoidA<T, 4>()
			{
				return EllipsoidA<T, 4>(Cs, R, O);
			}

			// methods
			Dimension<3> Dimensions() const
			{
				return Dimension<3>();
			}

			// operators
			EllipsoidA<T, 3>& operator-=(VectorA<T, 3> const& v)
			{
				O -= v;

				return (*this);
			}

			EllipsoidA<T, 3>& operator+=(VectorA<T, 3> const& v)
			{
				O += v;

				return (*this);
			}

			EllipsoidA<T, 3>& operator=(EllipsoidA<T, 3> const& e)
			{
				if (this != &e)
				{
					Cs = e.Cs;
					R = e.R;
					O = e.O;
				}

				return (*this);
			}

			friend EllipsoidA<T, 3> operator-(EllipsoidA<T, 3> e, VectorA<T, 3> const& v)
			{
				e -= v;
				return l;
			}

			friend EllipsoidA<T, 3> operator+(EllipsoidA<T, 3> e, VectorA<T, 3> const& v)
			{
				e += v;
				return l;
			}

			bool operator==(EllipsoidA<T, 3> const& e)
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
			EllipsoidA<T, 3>& Rotate(Quaternion<T> r)
			{
				VectorA<T, 3> rotatedCoefficients = RotateVectorBy(Cs, r);

				Cs = rotatedCoefficients;

				return (*this);
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Ellipsoid3 = EllipsoidA<T, 3>;

		using Ellipsoid3F = Ellipsoid3<float>;
		using Ellipsoid3I = Ellipsoid3<int>;
		using Ellipsoid3UI = Ellipsoid3<uint>;
	}
}