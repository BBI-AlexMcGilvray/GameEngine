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
				: C1(T(1)), C2(T(1)), R(T(1)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T c1, T c2, T r = 1, VectorA<T, 2> o = VectorA<T, 2>(T(0)))
				: C1(c1), C2(c2), R(r), O(o)
			{}

			// plane represented by 2 vectors and origin
			EllipsoidA(T r, VectorA<T, 2> o = VectorA<T, 2>(T(0)))
				: C1(T(1)), C2(T(1)), R(r), O(o)
			{}

			EllipsoidA(EllipsoidA<T, 2> const& e)
				: C1(e.C1), C2(e.C2), R(e.R), O(e.O)
			{}

			// methods
			Dimension<2> Dimensions()
			{
				return Dimension<2>;
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
					C1 = e.C1;
					C2 = e.C2;
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
				return (C1 == e.C1 && C2 == e.C2 && R == e.R && O == e.O);
			}

			// other comparison operators have no meaning

			EllipsoidA<T, 2>& Rotate(Quaternion<T> r)
			{
				VectorA<T, 3> rotatedCoefficients = RotateVectorBy(VectorA<T, 3>(C1, C2, T(0)), r);

				C1 = rotatedCoefficients.X;
				C2 = rotatedCoefficients.Y;

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