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
			union
			{
				struct
				{
					T C1;
					T C2;
					T C3;
				};
				T Coefficients[3];
			};
			T R;
			VectorA<T, 3> O;

			EllipsoidA()
				: C1(T(1)), C2(T(1)), C3(T(1)), R(T(1)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T c1, T c2, T c3, T r = 1, VectorA<T, 3> o = VectorA<T, 3>(T(0)))
				: C1(c1), C2(c2), C3(c3), R(r), O(o)
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T r, VectorA<T, 3> o = VectorA<T, 3>(T(0)))
				: C1(T(1)), C2(T(1)),C3(T(1)), R(r), O(o)
			{}

			EllipsoidA(EllipsoidA<T, 2> const& e)
				: C1(e.C1), C2(e.C2), C3(e.C3), R(e.R), O(e.O)
			{}

			// conversions
			operator EllipsoidA<T, 2>()
			{
				return EllipsoidA<T, 2>(C1, C2, R, O);
			}

			operator EllipsoidA<T, 4>()
			{
				return EllipsoidA<T, 4>(C1, C2, C3, T(1), R, O);
			}

			// methods
			Dimension<3> Dimensions()
			{
				return Dimension<3>;
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
					C1 = e.C1;
					C2 = e.C2;
					C3 = e.C3;
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
				return (C1 == e.C1 && C2 == e.C2 && C3 == e.C3 && R == e.R && O == e.O);
			}

			// other comparison operators have no meaning

			T& operator[](int axis)
			{
				return Coefficients[axis];
			}

			T operator[](int axis) const
			{
				return Coefficients[axis];
			}

			EllipsoidA<T, 3>& Rotate(Quaternion<T> r)
			{
				VectorA<T, 3> rotatedCoefficients = RotateVectorBy(VectorA<T, 3>(C1, C2, C3), r);

				C1 = rotatedCoefficients.X;
				C2 = rotatedCoefficients.Y;
				C3 = rotatedCoefficients.Z;

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