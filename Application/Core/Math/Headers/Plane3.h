#pragma once

#include "Plane.h"

#include "Vector3.h"

#include "Quaternion.h"
#include "QuaternionFunctions.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct PlaneA<T, 3>
		{
			VectorA<T, 3> E1;
			VectorA<T, 3> E2;

			PlaneA()
				: E1(T(1), T(0), T(0)), E2(T(0), T(1), T(0))
			{}

			// plane represented by 2 vectors
			PlaneA(VectorA<T, 3> v1, VectorA<T, 3> v2)
				: E1(v1), E2(v2)
			{}

			// plane represented by 3 points
			PlaneA(VectorA<T, 3> v1, VectorA<T, 3> v2, VectorA<T, 3> v3)
				: E1(v3 - v1), E2(v3 - v2)
			{}

			PlaneA(PlaneA<T, 3> const& p)
				: E1(p.E1), E2(p.E2)
			{}

			// methods
			Dimension<3> Dimensions()
			{
				return Dimension<3>;
			}

			// operators
			PlaneA<T, 3>& operator-=(VectorA<T, 3> const& v)
			{
				E1 -= v;
				E2 -= v;

				return (*this);
			}

			PlaneA<T, 3>& operator+=(VectorA<T, 3> const& v)
			{
				E1 += v;
				E2 += v;

				return (*this);
			}

			PlaneA<T, 3>& operator=(PlaneA<T, 3> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
				}

				return (*this);
			}

			friend PlaneA<T, 3> operator-(PlaneA<T, 3> p, PlaneA<T, 3> const& oP)
			{
				p -= oP;
				return p;
			}

			friend PlaneA<T, 3> operator+(PlaneA<T, 3> p, PlaneA<T, 3> const& oP)
			{
				p += oP;
				return p;
			}

			bool operator==(PlaneA<T, 3> const& p)
			{
				return (E1 == p.E1 && E2 == p.E2);
			}

			PlaneA<T, 3>& Rotate(Quaternion<T> r)
			{
				E1 = RotateVectorBy(E1, r);
				E2 = RotateVectorBy(E2, r);

				return (*this);
			}

			VectorA<T, 3> GetNormal()
			{
				// does not exist for 2 dimensions
				return CrossProduct(E1, E2);
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Plane3 = PlaneA<T, 3>;

		using Plane3F = Plane3<float>;
		using Plane3I = Plane3<int>;
		using Plant3UI = Plane3<uint>;
	}
}