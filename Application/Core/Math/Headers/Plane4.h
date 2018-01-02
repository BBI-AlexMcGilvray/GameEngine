#pragma once

#include "Plane.h"

#include "Vector4.h"

#include "Quaternion.h"
#include "QuaternionFunctions.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct PlaneA<T, 4>
		{
			VectorA<T, 4> E1;
			VectorA<T, 4> E2;

			PlaneA()
				: E1(T(1), T(0), T(0), T(0)), E2(T(0), T(1), T(0), T(0))
			{}

			// plane represented by 2 vectors
			PlaneA(VectorA<T, 4> v1, VectorA<T, 4> v2)
				: E1(v1), E2(v2)
			{}

			// plane represented by 3 points
			PlaneA(VectorA<T, 4> v1, VectorA<T, 4> v2, VectorA<T, 4> v3)
				: E1(v3 - v1), E2(v3 - v2)
			{}

			PlaneA(PlaneA<T, 4> const& p)
				: E1(p.E1), E2(p.E2)
			{}

			// methods
			Dimension<4> Dimensions()
			{
				return Dimension<4>;
			}

			// operators
			PlaneA<T, 4>& operator-=(VectorA<T, 4> const& v)
			{
				E1 -= v;
				E2 -= v;

				return (*this);
			}

			PlaneA<T, 4>& operator+=(VectorA<T, 4> const& v)
			{
				E1 += v;
				E2 += v;

				return (*this);
			}

			PlaneA<T, 4>& operator=(PlaneA<T, 4> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
				}

				return (*this);
			}

			friend PlaneA<T, 4> operator-(PlaneA<T, 4> p, PlaneA<T, 4> const& oP)
			{
				p -= oP;
				return p;
			}

			friend PlaneA<T, 4> operator+(PlaneA<T, 4> p, PlaneA<T, 4> const& oP)
			{
				p += oP;
				return p;
			}

			bool operator==(PlaneA<T, 4> const& p)
			{
				return (E1 == p.E1 && E2 == p.E2);
			}

			PlaneA<T, 4>& Rotate(Quaternion<T> r)
			{
				// not implemented yet
				/*
				E1 = RotateVectorBy(E1, r);
				E2 = RotateVectorBy(E2, r);
				*/

				return (*this);
			}

			VectorA<T, 4> GetNormal()
			{
				// does not exist for 2 dimensions
				return VectorA<T, 4>(0);
			}
		};

		/*	TYPE DEFS	*/
		template <typename T>
		using Plane4 = PlaneA<T, 4>;

		using Plane4F = Plane4<float>;
		using Plane4I = Plane4<int>;
		using Plant4UI = Plane4<uint>;
	}
}