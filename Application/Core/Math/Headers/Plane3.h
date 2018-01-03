#pragma once

#include "Plane.h"

#include "Vector3.h"
#include "VectorFunctions.h"

#include "Quaternion.h"
#include "QuaternionFunctions.h"

namespace Core
{
	namespace Math
	{
		template <typename T>
		struct PlaneA<T, 3>
		{
			union
			{
				struct
				{
					VectorA<T, 3> E1;
					VectorA<T, 3> E2;
				};
				T Vectors[2];
			};
			VectorA<T, 3> Origin;

			PlaneA()
				: E1(T(1), T(0), T(0)), E2(T(0), T(1), T(0)), Origin(T(0))
			{}

			// plane represented by 2 vectors and origin
			PlaneA(VectorA<T, 3> v1, VectorA<T, 3> v2, VectorA<T, 3> origin = VectorA<T, 3>(T(0)))
				: E1(v1), E2(v2), Origin(origin)
			{}

			PlaneA(PlaneA<T, 3> const& p)
				: E1(p.E1), E2(p.E2), Origin(p.Origin)
			{}

			// methods
			Dimension<3> Dimensions()
			{
				return Dimension<3>;
			}

			// operators
			PlaneA<T, 3>& operator-=(VectorA<T, 3> const& v)
			{
				Origin -= v;

				return (*this);
			}

			PlaneA<T, 3>& operator+=(VectorA<T, 3> const& v)
			{
				Origin += v;

				return (*this);
			}

			PlaneA<T, 3>& operator=(PlaneA<T, 3> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
					Origin = p.Origin;
				}

				return (*this);
			}

			friend PlaneA<T, 3> operator-(PlaneA<T, 3> p, VectorA<T, 3> const& v)
			{
				p -= v;
				return p;
			}

			friend PlaneA<T, 3> operator+(PlaneA<T, 3> p, VectorA<T, 3> const& v)
			{
				p += v;
				return p;
			}

			bool operator==(PlaneA<T, 2> const& p)
			{
				return (GetNormal() == p.GetNormal() && Origin == p.Origin);
			}

			T& operator[](int index)
			{
				return Vectors[index];
			}

			T operator[](int index) const
			{
				return Vectors[index];
			}

			PlaneA<T, 3>& Rotate(Quaternion<T> r)
			{
				E1 = RotateVectorBy(E1, r);
				E2 = RotateVectorBy(E2, r);

				return (*this);
			}

			VectorA<T, 3> GetNormal()
			{
				// normlize since magnitude should not matter and due to the crossproduct on arbitrary vectors, no guarantee on size constraints

				// does not exist for 2 dimensions
				return Normalize(CrossProduct(E1, E2));
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