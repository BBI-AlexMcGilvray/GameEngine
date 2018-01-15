#pragma once

#include "Plane.h"
#include "Line3.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
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
				VectorA<T, 3> Vectors[2];
			};
			VectorA<T, 3> O;

			PlaneA()
				: E1(T(1), T(0), T(0)), E2(T(0), T(1), T(0)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			PlaneA(VectorA<T, 3> const& v1, VectorA<T, 3> const& v2, VectorA<T, 3> const& o = VectorA<T, 3>(T(0)))
				: E1(v1), E2(v2), O(o)
			{}

			PlaneA(LineA<T, 3> const& l, VectorA<T, 3> const& v)
				: E1(l.V), E2(v), O(l.P)
			{}

			PlaneA(PlaneA<T, 2> const& p)
				: E1(p.E1), E2(p.E2), O(p.O)
			{}

			PlaneA(PlaneA<T, 3> const& p)
				: E1(p.E1), E2(p.E2), O(p.O)
			{}

			// conversions
			operator PlaneA<T, 2>()
			{
				return PlaneA<T, 2>(E1, E2, O);
			}

			operator PlaneA<T, 4>()
			{
				return PlaneA<T, 4>(E1, E2, O);
			}

			// methods
			Dimension<3> Dimensions() const
			{
				return Dimension<3>();
			}

			// operators
			PlaneA<T, 3>& operator-=(VectorA<T, 3> const& v)
			{
				O -= v;

				return (*this);
			}

			PlaneA<T, 3>& operator+=(VectorA<T, 3> const& v)
			{
				O += v;

				return (*this);
			}

			PlaneA<T, 3>& operator=(PlaneA<T, 3> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
					O = p.O;
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
				auto normal = GetNormal();
				auto otherNormal = p.GetNormal();
				bool normalsEqual = (normal == otherNormal || -normal == otherNormal);

				// not true, Origins can be different and still have the same plane
				bool originsEqual = (O == p.O);

				return (normalsEqual && originsEqual);
			}

			// other comparison operators have no meaning

			VectorA<T, 3>& operator[](int index)
			{
				return Vectors[index];
			}

			VectorA<T, 3> operator[](int index) const
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