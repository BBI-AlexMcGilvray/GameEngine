#pragma once

#include "LineFunctions.h"
#include "PlaneFunctions.h"
#include "EllipsoidFunctions.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T, typename int A>
		bool PlaneIntersectsEllipsoid(PlaneA<T, A> const& p, EllipsoidA<T, A> const& e)
		{
			// distance from e.O to p <= e.R
		}

		template <typename T, typename int A>
		EllipsoidA<T, A - 1> PlaneEllipsoidIntersection(PlaneA<T, A> const& p, EllipsoidA<T, A> const& e)
		{

		}
	}
}