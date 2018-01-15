#pragma once

#include "Plane.h"
#include "Line4.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T>
		struct PlaneA<T, 4>
		{
			union
			{
				struct
				{
					VectorA<T, 4> E1;
					VectorA<T, 4> E2;
				};
				VectorA<T, 4> Vectors[2];
			};
			VectorA<T, 4> O;

			PlaneA()
				: E1(T(1), T(0), T(0), T(0)), E2(T(0), T(1), T(0), T(0)), O(T(0))
			{}

			// plane represented by 2 vectors and origin
			PlaneA(VectorA<T, 4> const& v1, VectorA<T, 4> const& v2, VectorA<T, 4> const& o = VectorA<T, 4>(T(0)))
				: E1(v1), E2(v2), O(o)
			{}

			PlaneA(LineA<T, 4> const& l, VectorA<T, 4> const& v)
				: E1(l.V), E2(v), O(l.P)
			{}

			PlaneA(PlaneA<T, 2> const& p)
				: E1(p.E1), E2(p.E2), O(p.O)
			{}

			PlaneA(PlaneA<T, 3> const& p)
				: E1(p.E1), E2(p.E2), O(p.O)
			{}

			PlaneA(PlaneA<T, 4> const& p)
				: E1(p.E1), E2(p.E2), O(p.O)
			{}

			// conversions
			operator PlaneA<T, 2>()
			{
				return PlaneA<T, 2>(E1, E2, O);
			}

			operator PlaneA<T, 3>()
			{
				return PlaneA<T, 3>(E1, E2, O);
			}

			// methods
			Dimension<4> Dimensions() const
			{
				return Dimension<4>();
			}

			// operators
			PlaneA<T, 4>& operator-=(VectorA<T, 4> const& v)
			{
				O -= v;

				return (*this);
			}

			PlaneA<T, 4>& operator+=(VectorA<T, 4> const& v)
			{
				O += v;

				return (*this);
			}

			PlaneA<T, 4>& operator=(PlaneA<T, 4> const& p)
			{
				if (this != &p)
				{
					E1 = p.E1;
					E2 = p.E2;
					O = p.O;
				}

				return (*this);
			}

			friend PlaneA<T, 4> operator-(PlaneA<T, 4> p, VectorA<T, 4> const& v)
			{
				p -= v;
				return p;
			}

			friend PlaneA<T, 4> operator+(PlaneA<T, 4> p, VectorA<T, 4> const& v)
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

			VectorA<T, 4>& operator[](int index)
			{
				return Vectors[index];
			}

			VectorA<T, 4> operator[](int index) const
			{
				return Vectors[index];
			}

			PlaneA<T, 4>& Rotate(Quaternion<T> r)
			{
				// no implementation for rotating V4 by Quaternion

				return (*this);
			}

			VectorA<T, 4> GetNormal()
			{
				// normlize since magnitude should not matter and due to the crossproduct on arbitrary vectors, no guarantee on size constraints

				// does not exist for 2 dimensions
				return Normalize(VectorA<T, 4>(1, 1, 1, 1));
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