#pragma once

#include "Line.h"
#include "Line2.h"
#include "Line3.h"
#include "Line4.h"

#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/CoreDefs.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T, typename int A>
		VectorA<T, A> SubstituteInValue(LineA<T, A> const& l, T s)
		{
			return VectorA<T, A>(l.O + (s * l.V));
		}

		template <typename T, typename int A>
		LineA<T, A> LineFromPoints(VectorA<T, A> const& p1, VectorA<T, A> const& p2)
		{
			return LineA<T, A>(p2 - p1, p1);
		}

		template <typename T, typename int A>
		bool LinesParrallel(LineA<T, A> const& l1, LineA<T, A> const& l2)
		{
			auto l1Normal = Normalize(l1.V);
			auto l2Normal = Normalize(l2.V);

			return (l1Normal == l2Normal || -l1Normal == l2Normal);
		}

		template <typename T, typename int A>
		bool LinesOrthogonal(LineA<T, A> const& l1, LineA<T, A> const& l2)
		{
			return (Dot(l1.V, l2.V) == 0);
		}

		template <typename T, typename int A>
		bool PointOnLine(VectorA<T, A> const& p, LineA<T, A> const& l)
		{
			auto newLine = LineFromPoints<T, A>(p, l.O);

			return LinesParrallel(newLine, l);
		}

		template <typename T, typename int A>
		Truth<T> ValueToGetPointFromLine(VectorA<T, A> const& p, LineA<T, A> const& l)
		{
			if (!PointOnLine(p, l))
			{
				returh Truth(false, T(0));
			}

			T value = (p[0] - l.O[0]) / l.V[0];

			return Truth(true, value);
		}

		template <typename T, typename int A>
		VectorA<T, A> ShortestDirectionFromPointToLine(VectorA<T, A> const& p, LineA<T, A> const& l)
		{
			/*
				NOTE: Not normalized
			*/

			auto pTolPoint = (l.O - p);

			auto shortestDirection = Perp(pTolPoint, l.V);

			return shortestDirection;
		}

		// custom struct to hold results of ClosestPointOnL1ToL2
		template <typename T, typename int A>
		struct ClosestPointsBetweenLines
		{
			enum class ProximityType
			{
				Closest,
				Intersection,
				Parrallel,
				Unknown
			};
			ProximityType Type;

			VectorA<T, A> Point1;
			VectorA<T, A> Point2;

			ClosestPoint(ProximityType type, VectorA<T, A> point1, VectorA<T, A> point2)
				: Type(type), Point1(point1), Point2(point2)
			{}

			bool Closest()
			{
				return (ProximityType::Closest == Type);
			}

			bool Intersect()
			{
				return (ProximityType::Intersection == Type);
			}

			bool Parrallel()
			{
				return (ProximityType::Parrallel == Type);
			}

			bool Unknown()
			{
				return (ProximityType::Unknown == Type);
			}

			T DistanceBetweenPoints()
			{
				return Distance(Point1, Point2);
			}

			VectorA<T, A> Direction()
			{
				return Direction(Point1, Point2);
			}
		};

		template <typename T, typename int A, typename P = Thousandth>
		ClosestPointsBetweenLines<T, A> ClosestPointOnL1ToL2(LineA<T, A> const& l1, LineA<T, A> const& l2)
		{
			/*
				Solve the equation: L1 = l1.P + (s * l1.V), L2 = l2.P + (t * l2.V)

				To solve, calculate the magnitude square of the difference between the two lines (parametric equations)
				and then take the derivatives of the resulting equation with respect to s and t, set the result to 0,
				equate the two, and solve for s and t

				f(s, t) = |L1 - L2|^2 = (l1.P - l2.P + (s * l1.V) - (t * l2.V))^2

				d/ds(f(s, t)) = 2 * l1.V * [l1.P - l2.P + (s * l1.V) - (t * l2.V)] = 0 = (l1.P - l2.P) + [(s * l1.V) - (t * l2.V)]
				d/dt(f(s, t)) = -2 * l2.V * [l1.P - l2.P + (s * l1.V) - (t * l2.V)] = 0 = (l1.P - l2.P) + [(s * l1.V) - (t * l2.V)]

				So we need to solve 0 = (l1.P[i] - l2.P[i]) + [(s * l1.V[i]) - (t * l2.V[i])] for all ie[0, A - 1]

				// initial information
				=> s = [(l2.P[i] - l1.P[i]) + (t * l2.V[i])] / l1.V[i], => l1.V[i] != 0
				=> t = [(l1.P[j] - l2.P[j]) + (s * l1.V[j])] / l2.V[j], => l2.V[j] != 0

				// secondary information
				NOTE: i != j
				=> t = [(l1.V[i] * (l1.P[j] - l2.P[j])) + (l1.V[j] * (l2.P[i] - l1.P[i]))] / [(l1.V[i] * l2.V[j]) - (l1.V[j] * l2.V[i])], => (l1.V[i] * l2.V[j]) - (l1.V[j] * l2.V[i]) != 0
				=> s = [(l2.V[j] * (l2.P[i] - l1.P[i])) + (l2.V[i] * (l1.P[j] - l2.P[j]))] / [(l2.V[j] * l1.V[i]) - (l2.V[i] * l1.V[j])], => (l2.V[j] * l1.V[i]) - (l2.V[i] * l1.V[j]) != 0
			*/

			if (LinesParrallel(l1, l2))
			{
				// do not intersect, any point on l1 is the closest to l2 (parrallel)
				return ClosestPointsBetweenLines(ClosestPointsBetweenLines::ProximityType::Parrallel, l1.O, l1.O + ShortestDistanceFromPointToLine(l1.O, l2));
			}

			bool iIsInitial = true;
			int i = 0;
			int j = 0;

			bool findIndex = [&](bool lookingForI)
			{
				int& index = lookingForI ? i : j;

				bool isInitial = iIsInitial == lookingForI;

				for (; index < A; index++)
				{
					// initial restrictions
					bool indexEqualsZero = lookingForI ? l1.V[i] == T(0) : l2.V[j] == T(0);

					// secondary restrictions
					bool denominatorEqualsZero = lookingForI ? ((l1.V[i] * l2.V[j]) - (l1.V[j] * l2.V[i]) == 0) : ((l2.V[j] * l1.V[i]) - (l2.V[i] * l1.V[j]) == 0);

					// relevant result
					bool indexRestricted = isInitial ? indexEqualsZero : (i == j && denominatorEqualsZero);

					if (!indexRestricted)
					{
						return true;
					}
				}

				return false;
			}

			bool correctIndexFound = false;
			if (findIndex(true))
			{
				correctIndexFound = findIndex(false);
			}

			if (!correctIndexFound)
			{
				iIsInitial = false;
				if (findIndex(false))
				{
					correctIndexFound = findIndex(true);
				}
			}

			if (!correctIndexFound)
			{
				// no value could be found
				return ClosestPointsBetweenLines(ClosestPointsBetweenLines::ProximityType::Unknown, l1.O, l2.O);
			}
			
			T s;
			T t;

			if (iIsInitial)
			{
				t = [(l1.V[i] * (l1.O[j] - l2.O[j])) + (l1.V[j] * (l2.O[i] - l1.O[i]))] / [(l1.V[i] * l2.V[j]) - (l1.V[j] * l2.V[i])];
				s = [(l2.O[i] - l1.O[i]) + (t * l2.V[i])] / l1.V[i];
			}
			else
			{
				s = [(l2.V[j] * (l2.O[i] - l1.O[i])) + (l2.V[i] * (l1.O[j] - l2.O[j]))] / [(l2.V[j] * l1.V[i]) - (l2.V[i] * l1.V[j])];
				t = [(l1.O[j] - l2.O[j]) + (s * l1.V[j])] / l2.V[j];
			}

			auto l1Closest = l1.SubstituteInCoefficient(s);
			auto l2Closest = l2.SubstituteInCoefficient(t);
			auto intersect = Within(l1Closest, l2Closest, P);

			auto proximityType = intersect ? ClosestPointsBetweenLines::ProximityType::Intersect : ClosestPointsBetweenLines::ProximityType::Closest;
			return ClosestPointsBetweenLines(proximityType, l1Closest, l2Closest);
		}
#if DEBUG

		// reminder: macro statements should be formatted such that whitespace is correct were they to be removed
		template <typename T, typename int A>
		String LineString(LineA<T, A> const& p)
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