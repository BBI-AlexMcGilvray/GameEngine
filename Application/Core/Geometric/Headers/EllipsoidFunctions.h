#pragma once

// should be able to return a point when an axis value subbed into ellipsoid2, an ellipsoid2 of possible values when an axis value is subbed into ellipsoid3,
// an ellipsoid3 of possible values when an axis value is subbed into an ellipsoid4, and so on for if 2 (or 3 or 4) axis values are subbed in
// NOTE: may want to have a way to nicely pass an axis/value pair. (Should be added to math defs - possible all axis' can just have values as well?
#pragma once

#include "Ellipsoid.h"
#include "Ellipsoid2.h"
#include "Ellipsoid3.h"
#include "Ellipsoid4.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/VectorFunctions.h"

#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/CoreDefs.h"

namespace Core
{
	namespace Geometric
	{
		template <typename T, typename int A>
		bool PointInEllipsoid(VectorA<T, A> const& p, EllipsoidA<T, A> const& e)
		{
			T distanceSqr = DistanceSqr(p, e.O);

			return (distanceSqr < Sqr(e.R));
		}

		template <typename T, typename int A, typename P = Thousandth>
		bool PointOnEllipsoid(VectorA<T, A> const& p, EllipsoidA<T, A> const& e)
		{
			T distanceSqr = DistanceSqr(p, e.O);

			return Within(distanceSqr, sqr(e.R), P);
		}

		template <typename T, typename int A>
		bool LineIntersectsEllipsoid(LineA<T, A> const& l, EllipsoidA<T, A> const& e)
		{
			auto closestPointToEllipse = ShortestDirectionFromPointToLine(e.O, l);

			return (PointInEllipsoid(closestPointToEllipse, e) || PointOnEllipsoid(closestPointToEllipse, e));
		}

		/*
			To get the closestpoint on a line to an ellipsoid, calculate the line from ellipsoid origin to the line,
			and find the closest points between the two lines
		*/
		template <typename T, typename int A>
		VectorA<T, A> ClosestPointOnEllipsoidToPoint(VectorA<T, A> const& p, EllipsoidA<T, A> const& e)
		{
			auto directionToPoint = Direction(e.O, p);

			auto lineToPoint = LineA<T, A>(directionToPoint, e.O);

			// because we are going to the ellipsoid origin, we know there will be intersection points
			Pair<VectorA<T, A>> intersectionPoints = LineEllipsoidIntersection(lineToPoint, e).Value;

			auto d1 = DistanceSqr(intersectionPoints.first, p);
			auto d2 = DistanceSqr(intersectionPoints.second, p);

			return (d1 < d2 ? intersectionPoints.first : intersectionPoints.second);
		}

		template <typename T, typename int A>
		Truth<Pair<VectorA<T, A>>> LineEllipsoidIntersection(LineA<T, A> const& l, EllipsoidA<T, A> const& e)
		{
			if (!LineIntersectsEllipsoid(l, e))
			{
				return Truth(false);
			}

			/*
				L: O + sV = W
				E: Sum(Ci * ((Oi + Vi)^2)) = R^2

				Solve: Sum(Ci * ((Oi + L::Oi + (s * L::Vi))^2)) = R^2
				=> expand and solve for s
				=> s = -b
			*/

			T a = T(0);
			T b = T(0);
			T c = -Sqr(R);

			for (int i = 0; i < A; i++)
			{
				a += e.Coefficients[i] * Sqr(l.V[i]);
				b += 2 * (e.Coefficients[i] * (e.O[i] + l.O[i]) * l.V[i]);
				c += e.Coefficients[i] * (e.O[i] + l.O[i]);
			}

			Pair<T> sValues = QuadraticFormula(a, b, c);

			Pair<VectorA<T, A>> intersectionPoints = Pair<VectorA<T, A>>(SubstituteInValue(l, sValues.first), SubstituteInValue(l, sValues.second));

			return Truth(true, intersectionPoints);
		}

		template <typename T, typename int A>
		T SubInAxisValue(Ellipsoid2<T> const& e, AxisValue<A, T> const& a)
		{
			if (!MESSAGE(a == ZAxis || a == WAxis, "Axis is not on the ellipsoid"))
			{
				return T(0);
			}

			T numerator = Sqr(e.R) - (e[a] * Sqr(e.O[a] + a.V));
			T denominator = (a == XAxis) ? e[YAxis] : e[XAxis];
			T offset = (a == XAxis) ? e.O[YAxis] : e.O[XAxis];

			return (Sqrt(numerator / denominator) - offset);
		}

		template <typename T, typename int A1, typename int A2, EnableIf<IsSame<false, IsSame<A1, A2>>>>
		T SubInAxisValue(Ellipsoid3<T> const& e, AxisValue<A1, T> const& a1, AxisValue<A2, T> const& a2)
		{
			Ellipsoid2<T> possibleOptions = SubInAxisValue(e, a1);

			if (IsAxisLower(a1, a2))
			{
				return SubInAxisValue(possibleOptions, DownshiftAxis(a2));
			}

			return SubInAxisValue(possibleOptions, a2);
		}

		template <typename T, typename int A1, typename int A2, typename int A3, EnableIf<IsSame<IsSame<false, IsSame<A1, A2>>, IsSame<IsSame<A1, A3>, IsSame<A2, A3>>>>>
		T SubInAxisValue(Ellipsoid4<T> const& e, AxisValue<A1, T> const& a1, AxisValue<A2, T> const& a2, AxisValue<A3, T> const& a3)
		{
			Ellipsoid3<T> possibleOptions = SubInAxisValue(e, a1);

			if (IsAxisLower(a1, a2))
			{
				if (IsAxisLower(a1, a3))
				{
					return SubInAxisValue(possibleOptions, DownshiftAxis(a2), DownshiftAxis(a3));
				}

				return SubInAxisValue(possibleOptions, DownshiftAxis(a2), a3);
			}

			if (IsAxisLower(a1, a3))
			{
				return SubInAxisValue(possibleOptions, a2, DownshiftAxis(a3));
			}

			return SubInAxisValue(possibleOptions, a2, a3);
		}

		// when shifting down a dimension, the 'missing' axis - and all those of a higher axis value - get shifted down a slot
		template <typename T, typename int A>
		Ellipsoid2<T> SubInAxisValue(Ellipsoid3<T> const& e, AxisValue<A, T> const& a)
		{
			if (!MESSAGE(a == WAxis, "Axis is not on the ellipsoid"))
			{
				return Ellipsoid2<T>();
			}

			T newC1 = (a == XAxis) ? e[YAxis] : e[XAxis];
			T newC2 = (a == XAxis || a == YAxis) ? e[ZAxis] : e[YAxis];

			T newR = Sqr(R) - (e[a] * Sqr(e.O[a] + a.V));

			T newOX = (a == XAxis) ? e.O[YAxis] : e.O[XAxis];
			T newOY = (a == XAxis || a == YAxis) ? e.O[ZAxis] : e.O[YAxis];
			Vector2<T> newO = Vector2<T>(newOX, newOY);

			return Ellipsoid2<T>(newC1, newC2, newR, newO);
		}

		template <typename T, typename int A1, typename int A2, EnableIf<IsSame<fale, IsSame<A1, A2>>>>
		Ellipsoid2<T> SubInAxisValue(Ellipsoid4<T> const& e, AxisValue<A1, T> const& a1, AxisValue<A2, T> const& a2)
		{
			Ellipsoid3<T> possibleOptions = SubInAxisValue(e, a1);

			if (IsAxisLower(a1, a2))
			{
				return SubInAxisValue(possibleOptions, DownshiftAxis(a2));
			}

			return SubInAxisValue(possibleOptions, a2);
		}

		template <typename T, typename int A>
		Ellipsoid3<T> SubInAxisValue(Ellipsoid4<T> const& e, AxisValue<A, T> const& a)
		{
			T newC1 = (a == XAxis) ? e[YAxis] : e[XAxis];
			T newC2 = (a == XAxis || a == YAxis) ? e[ZAxis] : e[YAxis];
			T newC3 = (a == XAxis || a == YAxis || a == ZAxis) ? e[WAxis] : e[ZAxis];

			T newR = Sqr(R) - (e[a] * Sqr(e.O[a] + a.V));

			T newOX = (a == XAxis) ? e.O[YAxis] : e.O[XAxis];
			T newOY = (a == XAxis || a == YAxis) ? e.O[ZAxis] : e.O[YAxis];
			T newOZ = (a == XAxis || a == YAxis || a == ZAxis) ? e.O[WAxis] : e.O[ZAxis];
			Vector3<T> newO = Vector3<T>(newOX, newOY);

			return Ellipsoid3<T>(newC1, newC2, newR, newO);
		}
#if DEBUG

		// reminder: macro statements should be formatted such that whitespace is correct were they to be removed
		template <typename T, typename int A>
		String EllipsoidString(EllipsoidA<T, A> const& e)
		{
			String ellipsoidInfo;

			ellipsoidInfo += "[";
			for (auto i = 0; i < e.Dimensions(); i++)
			{
				ellipsoidInfo += e[i];

				ellipsoidInfo += "(";
				
				ellipsoidInfo += e.O[i];

				ellipsoidInfo += " + ";

				switch (i)
				{
					case XAxis:
					{
						ellipsoidInfo += "x";
						break;
					}
					case YAxis:
					{
						ellipsoidInfo += "y";
						break;
					}
					case ZAxis:
					{
						ellipsoidInfo += "z";
						break;
					}
					case WAxis:
					{
						ellipsoidInfo += "w";
						break;
					}
				}

				ellipsoidInfo += ")";
			}

			ellipsoidInfo += " = ";
			ellipsoidInfo += e.R;

			ellipsoidInfo += "]";

			return ellipsoidInfo;
		}
#endif
	}
}