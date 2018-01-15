#pragma once

#include "Plane.h"
#include "Line2.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		// a 2D plane is just the whole 2D space
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
				VectorA<T, 2> Vectors[2];
			};
			VectorA<T, 2> O;

			PlaneA()
				: E1(T(1), T(0)), E2(T(0), T(1)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			PlaneA(VectorA<T, 2> const& v1, VectorA<T, 2> const& v2, VectorA<T, 2> const& o = VectorA<T, 2>(T(0)))
				: E1(v1), E2(v2), O(o)
			{}

			PlaneA(LineA<T, 2> const& l, VectorA<T, 2> const& v)
				: E1(l.V), E2(v), O(l.P)
			{}

			PlaneA(PlaneA<T, 2> const& p)
				: E1(p.E1), E2(p.E2), O(p.O)
			{}

			// methods
			Dimension<2> Dimensions() const
			{
				return Dimension<2>();
			}

			// conversions
			operator PlaneA<T, 3>()
			{
				return PlaneA<T, 3>(E1, E2, O);
			}

			operator PlaneA<T, 4>()
			{
				return PlaneA<T, 4>(E1, E2, O);
			}

			// operators
			PlaneA<T, 2>& operator-=(VectorA<T, 2> const& v)
			{
				O -= v;

				return (*this);
			}

			PlaneA<T, 2>& operator+=(VectorA<T, 2> const& v)
			{
				O += v;

				return (*this);
			}

			PlaneA<T, 2>& operator=(PlaneA<T, 2> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
					O = p.O;
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
				auto normal = GetNormal();
				auto otherNormal = p.GetNormal();
				bool normalsEqual = (normal == otherNormal || -normal == otherNormal);

				// not true, Origins can be different and still have the same plane
				bool originsEqual = (O == p.O);

				return (normalsEqual && originsEqual);
			}

			// other comparison operators have no meaning

			VectorA<T, 2>& operator[](int index)
			{
				return Vectors[index];
			}

			VectorA<T, 2> operator[](int index) const
			{
				return Vectors[index];
			}

			PlaneA<T, 2>& Rotate(Quaternion<T> r)
			{
				E1 = RotateVectorBy(E1, r);
				E2 = RotateVectorBy(E2, r);

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
		*/
	}
}