#pragma once

#include "LineFunctions.h"
#include "PlaneFunctions.h"
#include "EllipsoidFunctions.h"

namespace Core
{
	namespace Geometric
	{
		/*
			should this be done by having ellipsoids have a Transform (instead of an origin), so that we can always 'revert' the given ellipsoid back to the unit circle,
			and transform the plane to be aligned on the x,y-axis and solve consistently that way?

			Does this mean planes should also have a Transform (instaed of an origin)
		*/
		template <typename T, typename int A>
		bool PlaneIntersectsEllipsoid(PlaneA<T, A> const& p, EllipsoidA<T, A> const& e)
		{
			auto distanceToPlaneSqr = DistanceSqr(e.O, p);

			return (distanceToPlaneSqr <= Sqr(e.R));
		}

		template <typename T, typename int A>
		Truth<EllipsoidA<T, A - 1>> PlaneEllipsoidIntersection(PlaneA<T, A> const& p, EllipsoidA<T, A> const& e)
		{
			if (!PlaneIntersectsEllipsoid(p, e))
			{
				return Truth(false, EllipsoidA<T, A - 1>());
			}

			// need to determine the correct way to solve this

			return Truth(false, EllipsoidA<T, A - 1>());
		}
	}
}