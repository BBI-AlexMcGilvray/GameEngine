#pragma once

#include "Plane.h"

#include "Vector2.h"

#include "Quaternion.h"
#include "QuaternionFunctions.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct PlaneA<T, 2>
		{
			VectorA<T, 2> E1;
			VectorA<T, 2> E2;

			PlaneA()
				: E1(T(1), T(0)), E2(T(0), T(1))
			{}

			// plane represented by 2 vectors
			PlaneA(VectorA<T, 2> v1, VectorA<T, 2> v2)
				: E1(v1), E2(v2)
			{}

			// plane represented by 3 points
			PlaneA(VectorA<T, 2> v1, VectorA<T, 2> v2, VectorA<T, 2> v3)
				: E1(v3 - v1), E2(v3 - v2)
			{}

			PlaneA(PlaneA<T, 2> const& p)
				: E1(p.E1), E2(p.E2)
			{}

			// methods
			Dimension<2> Dimensions()
			{
				return Dimension<2>;
			}

			// operators
			PlaneA<T, 2>& operator-=(VectorA<T, 2> const& v)
			{
				E1 -= v;
				E2 -= v;

				return (*this);
			}

			PlaneA<T, 2>& operator+=(VectorA<T, 2> const& v)
			{
				E1 += v;
				E2 += v;

				return (*this);
			}

			PlaneA<T, 2>& operator=(PlaneA<T, 2> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
				}

				return (*this);
			}

			friend PlaneA<T, 2> operator-(PlaneA<T, 2> p, PlaneA<T, 2> const& oP)
			{
				p -= oP;
				return p;
			}

			friend PlaneA<T, 2> operator+(PlaneA<T, 2> p, PlaneA<T, 2> const& oP)
			{
				p += oP;
				return p;
			}

			bool operator==(PlaneA<T, 2> const& p)
			{
				return (E1 == p.E1 && E2 == p.E2);
			}

			PlaneA<T, 2>& Rotate(Quaternion<T> r)
			{
				// not implemented yet
				/*
				E1 = RotateVectorBy(E1, r);
				E2 = RotateVectorBy(E2, r);
				*/

				return (*this);
			}

			VectorA<T, 2> GetNormal()
			{
				// does not exist for 2 dimensions
				return VectorA<T, 2>(0);
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Plane2 = PlaneA<T, 2>;

		using Plane2F = Plane2<float>;
		using Plane2I = Plane2<int>;
		using Plant2UI = Plane2<uint>;
	}
}