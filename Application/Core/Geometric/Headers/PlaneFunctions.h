#pragma once

#include "Plane.h"
#include "Plane2.h"
#include "Plane3.h"
#include "Plane4.h"

#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/CoreDefs.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T, typename int A>
		PlaneA<T, A> PlaneFromNormal(VectorA<T, A> const& n, VectorA<T, A> const& origin)
		{
			if (!MESSAGE(n == VectorA<T, A>(T(0)) && n.Dimensions <= 4, "Normal is the 0 vector, or is an unsupported dimension"))
			{
				return PlaneA<T, A>(T(0));
			}

			VectorA<T, A> differentVector;
			if (n[0] != 0 && n[1] != 0)
			{ // vector in any direction
				differentVector = n + VectorA<T, A>(T(1), T(0));
			}
			else if (n[1] != 0)
			{ // vector in 0 direction
				differentVector = n + VectorA<T, A>(T(1), T(0));
			}
			else if (n[0] != 0)
			{ // vector in 0 direction
				differentVector = n + VectorA<T, A>(T(0), T(1));
			}
			else if (n.Dimensions() > 2 && n[2] != 0)
			{ // vector in 0 direction
				differentVector = n + VectorA<T, A>(T(1), T(0));
			}
			else if (n.Dimensions() > 3 && n[3] != 0)
			{ // vector in 0 direction
				differentVector = n + VectorA<T, A>(T(1), T(0));
			}

			auto firstPerpendicular = Perp(n, differentVector);
			auto secondPerpendiculat = Perp(n, firstPerpendicular);

			return PlaneA<T, A>(firstPerpendicular, secondPerpendicular, origin);
		}

		template <typename T, typename int A>
		PlaneA<T, A> PlaneFromPoints(VectorA<T, A> const& p1, VectorA<T, A> const& p2, VectorA<T, A> const& p3)
		{
			return PlaneA<T, A>(p3 - p1, p2 - p1, p1);
		}

		template <typename T, typename int A, typename P = Thousandth>
		bool PointIsOnPlane(VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			/*
				(p.O - v) will give us a vector, if the vector is parrallel to the plane, the point is on the plane (since the origin is on the plane)
			*/

			auto pointToOrigin = (p.O - v);

			return VectorParrallelToPlane<T, A, P>(pointToOrigin, p, P);
		}

		template <typename T, typename int A, typename P = Thousandth>
		bool VectorParrallelToPlane(VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			/*
				Any vector parrallel to the plane will have a result of 0 when dotten with the normal
			*/

			if (!MESSAGE(n == VectorA<T, A>(T(0)), "Vector is the 0 vector"))
			{
				return false;
			}

			auto normalDotVector = Dot(p.GetNormal, v);

			return (Within(normalDotVector, T(0), P));
		}

		template <typename T, typename int A, typename P = Thousandth>
		bool VectorIntersectsPlane(VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			return !VectorParrallelToPlane<T, A, P>(v, p);
		}

		template <typename T, typename int A>
		Truth<VectorA<T, A>> VectorPlanePointOfIntersection(VectorA<T, A> const& vOrigin, VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			if (VectorParrallelToPlane(v, p))
			{
				return Truth(false, VectorA<T, A>(T(0)));
			}

			/*
				Using the equation of a plane, gotten by Dot(N, (origin - pointOnPlane)) = 0 (=> Dot(N, vOrigin + (v * t)) = Dot(N, origin))
				we get that t = ((origin_x,y,z - vOrigin_x,y,z) / v_x,y,z), after ensuring that v_x,y,z != 0
			*/

			T t;
			if (v[0] != 0)
			{
				t = (p.O[0] - vOrigin[0]) / v[0];
			}
			else if (v[1] != 0)
			{
				t = (p.O[1] - v.Origin[1]) / v[1];
			}
			else if (v.Dimensions() > 2 && v[2] != 0)
			{
				t = (p.O[2] - v.Origin[2]) / v[2];
			}
			else if (v.Dimensions() > 3 && v[3] != 0)
			{
				t = (p.O[3] - v.Origin[3]) / v[3];
			}
			else
			{
				return Truth(MESSAGE(false, "Dimension of vector not supported"), VectorA<T, A>(T(0)));
			}

			VectorA<T, A> pointOfIntersection = vOrigin + (v * t);

			return Truth(true, pointOfIntersection);
		}
#if DEBUG

		// reminder: macro statements should be formatted such that whitespace is correct were they to be removed
		template <typename T, typename int A>
		String PlaneString(PlaneA<T, A> const& p)
		{
			String planeInfo;

			planeInfo += "[";
			for (auto i = 0; i < p.Dimensions(); i++)
			{
				planeInfo += VectorString(p[i]);

				if (i != p.Dimensions() - 1)
				{
					planeInfo += ", ";
				}
			}
			planeInfo += "]";

			return planeInfo;
		}
#endif
	}
}