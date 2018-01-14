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
		template <typename T, typename int A, typename int B = 2>
		LineA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B> const& b) = delete;

		template <typename T, typename int A, typename int B = 3>
		LineA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B> const& b) = delete;

		template <typename T, typename int A, typename int B>
		LineA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B> const& b)
		{
			VectorA<T, A> newOrigin = (b.V * p[b]) + p.O;
			VectorA<T, A> remainingVector = (b == Basis0) ? p[Basis1()] : p[Basis0()];

			return LineA<T, A>(remainingVector, newOrigin);
		}

		template <typename T, typename int A, typename int B1, typename int B2 = 2>
		VectorA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B1> const& b1, BasisValue<T, B2> const& b2) = delete;

		template <typename T, typename int A, typename int B1, typename int B2 = 3>
		VectorA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B1> const& b1, BasisValue<T, B2> const& b2) = delete;

		template <typename T, typename int A, typename int B1 = 2, typename int B2>
		VectorA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B1> const& b1, BasisValue<T, B2> const& b2) = delete;

		template <typename T, typename int A, typename int B1 = 3, typename int B2>
		VectorA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B1> const& b1, BasisValue<T, B2> const& b2) = delete;

		template <typename T, typename int A, typename int B1, typename int B2>
		VectorA<T, A> SubstituteInValue(PlaneA<T, A> const& p, BasisValue<T, B1> const& b1, BasisValue<T, B2> const& b2)
		{
			LineA<T, A> remainingLine = SubstituteInValue(p, b1);
			return SubstituteInValue(remainingLine, b2.V);
		}

		// function to get coefficients of vector on plane?

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

		template <typename T, typename int A>
		bool PlanesIntersect(PlaneA<T, A> const& p1, PlaneA<T, A> const& p1)
		{
			return (Dot(p1.GetNormal(), p2.GetNormal()) != 0);
		}

		template <typename T, typename int A, typename P = Thousandth>
		bool VectorIntersectsPlane(VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			return !VectorParrallelToPlane<T, A, P>(v, p);
		}

		template <typename T, typename int A>
		T DistanceSqr(VectorA<T, A> const& p, PlaneA<T, A> const& pl)
		{
			auto closestPointOnPlane = ClosestPointOnPlaneToPoint(p, pl);

			return DistanceSqr(closestPointOnPlane, p);
		}

		template <typename T, typename int A>
		T Distance(VectorA<T, A> const& p, PlaneA<T, A> const& pl)
		{
			return Sqrt(DistanceSqr(p, pl));
		}

		template <typename T, typename int A>
		VectorA<T, A> Project(VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			return Perp(v, p.GetNormal());
		}

		template <typename T, typename int A>
		VectorA<T, A> Project(PlaneA<T, A> const& p, VectorA<T, A> const& v)
		{
			return Project(v, p);
		}

		template <typename T, typename int A>
		VectorA<T, A> Perp(VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			return Project(v, p.GetNormal());
		}

		template <typename T, typename int A>
		VectorA<T, A> Perp(PlaneA<T, A> const& p, VectorA<T, A> const& v)
		{
			return Perp(v, p);
		}

		template <typename T, typename int A>
		VectorA<T, A> ClosestPointOnPlaneToPoint(VectorA<T, A> const& p, PlaneA<T, A> const& pl)
		{
			return VectorPlanePointOfIntersection(p, pl.N, pl);
		}

		template <typename T, typename int A>
		Truth<LineA<T, A>> PlanePlaneLineOfIntersection(PlaneA<T, A> const& p1, PlaneA<T, A> const& p2)
		{
			if (!PlanesIntersect(p1, p2))
			{
				return Truth(false, LineA<T, A>(T(0)));
			}

			// direction the intersection will move in
			VectorA<T, A> intersectionDirection = CrossProduct(p1, p2);

			// normal of p2, projected onto p1 gives the direction to p2
			auto directionToPlane = Project(p2.GetNormal(), p1);
			VectorA<T, A> aPointOfIntersection = VectorPlanePointOfIntersection(p1.O, directionToPlane, p2);

			return Truth(true, LineA<T, A>(intersectionDirection, aPointOfIntersection));
		}

		template <typename T, typename int A>
		Truth<VectorA<T, A>> LinePlanePointOfIntersection(LineA<T, A> const& l, PlaneA<T, A> const& p)
		{
			return VectorPlanePointOfIntersection(l.P, l.V, p);
		}

		template <typename T, typename int A>
		Truth<VectorA<T, A>> VectorPlanePointOfIntersection(VectorA<T, A> const& vO, VectorA<T, A> const& v, PlaneA<T, A> const& p)
		{
			if (VectorParrallelToPlane(v, p))
			{
				return Truth(false, VectorA<T, A>(T(0)));
			}

			/*
				Using the equation of a plane, gotten by Dot(N, (origin - pointOnPlane)) = 0 (=> Dot(N, vO + (v * t)) = Dot(N, O) - we want to find t such that vO + (v * t) is on the plane)
				we get that t = ((O,y,z - vO,y,z) / v_x,y,z), after ensuring that v_x,y,z != 0
			*/

			T t;

			if (v[0] != 0)
			{
				t = (p.O[0] - vO[0]) / v[0];
			}
			else if (v[1] != 0)
			{
				t = (p.O[1] - v.vO[1]) / v[1];
			}
			else if (v.Dimensions() > 2 && v[2] != 0)
			{
				t = (p.O[2] - v.vO[2]) / v[2];
			}
			else if (v.Dimensions() > 3 && v[3] != 0)
			{
				t = (p.O[3] - v.vO[3]) / v[3];
			}
			else
			{
				return Truth(MESSAGE(false, "Dimension of vector not supported"), VectorA<T, A>(T(0)));
			}

			VectorA<T, A> pointOfIntersection = vO + (v * t);

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