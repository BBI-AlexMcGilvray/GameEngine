#pragma once

#include "Plane.h"

#include "Vector2.h"
#include "VectorFunctions.h"

#include "Quaternion.h"
#include "QuaternionFunctions.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct PlaneA<T, 2>
		{
			union
			{
				struct
				{
					VectorA<T, 2> E1;
					VectorA<T, 2> E2;
				};
				T Vectors[2];
			};
			VectorA<T, 2> Origin;

			PlaneA()
				: E1(T(1), T(0)), E2(T(0), T(1)), Origin(T(0))
			{}

			// plane represented by 2 vectors and origin
			PlaneA(VectorA<T, 2> v1, VectorA<T, 2> v2, VectorA<T, 2> origin = VectorA<T, 2>(T(0)))
				: E1(v1), E2(v2), Origin(origin)
			{}

			PlaneA(PlaneA<T, 2> const& p)
				: E1(p.E1), E2(p.E2), Origin(p.Origin)
			{}

			// methods
			Dimension<2> Dimensions()
			{
				return Dimension<2>;
			}

			// operators
			PlaneA<T, 2>& operator-=(VectorA<T, 2> const& v)
			{
				Origin -= v;

				return (*this);
			}

			PlaneA<T, 2>& operator+=(VectorA<T, 2> const& v)
			{
				Origin += v;

				return (*this);
			}

			PlaneA<T, 2>& operator=(PlaneA<T, 2> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
					Origin = p.Origin;
				}

				return (*this);
			}

			friend PlaneA<T, 2> operator-(PlaneA<T, 2> p, VectorA<T, 2> const& v)
			{
				p -= v;
				return p;
			}

			friend PlaneA<T, 2> operator+(PlaneA<T, 2> p, VectorA<T, 2> const& v)
			{
				p += v;
				return p;
			}

			bool operator==(PlaneA<T, 2> const& p)
			{
				return (GetNormal() == p.GetNormal() && Origin == p.Origin);
			}

			// other comparison operators have no meaning

			T& operator[](int index)
			{
				return Vectors[index];
			}

			T operator[](int index) const
			{
				return Vectors[index];
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
				// normlize since magnitude should not matter and due to the crossproduct on arbitrary vectors, no guarantee on size constraints

				// does not exist for 2 dimensions
				return Normalize(VectorA<T, 2>(1, 1));
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