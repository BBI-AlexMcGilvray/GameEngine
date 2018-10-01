#include "Core/Geometric/2D/Headers/GeometryFunctions.h"

#include "Core/Geometric/2D/Headers/Point.h"
#include "Core/Geometric/2D/Headers/Line.h"
#include "Core/Geometric/2D/Headers/Box.h"
#include "Core/Geometric/2D/Headers/Circle.h"
#include "Core/Geometric/2D/Headers/Polygon.h"

#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core
{
	namespace Geometric
	{
		namespace GeometryFunctions2D
		{
			bool Intersect(Ptr<const Geometry2D> geometry1, Ptr<const Geometry2D> geometry2)
			{
				return geometry1->Intersect(geometry2);
			}

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Point2D> point)
			{
				return geometry->Intersect(point);
			}
			bool Intersect(Ptr<const Point2D> point, Ptr<const Geometry2D> geometry)
			{
				return geometry->Intersect(point);
			}

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Line2D> line)
			{
				return geometry->Intersect(line);
			}
			bool Intersect(Ptr<const Line2D> line, Ptr<const Geometry2D> geometry)
			{
				return geometry->Intersect(line);
			}

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Box2D> box)
			{
				return geometry->Intersect(box);
			}
			bool Intersect(Ptr<const Box2D> box, Ptr<const Geometry2D> geometry)
			{
				return geometry->Intersect(box);
			}

			bool Intersect(Ptr<const Geometry2D> geometry, Ptr<const Circle2D> circle)
			{
				return geometry->Intersect(circle);
			}
			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Geometry2D> geometry)
			{
				return geometry->Intersect(circle);
			}

			bool Intersect(Ptr<const Point2D> point1, Ptr<const Point2D> point2)
			{
				return (point1->Axes == point2->Axes);
			}

			bool Intersect(Ptr<const Point2D> point, Ptr<const Line2D> line)
			{
				return line->PointOnLine(*point);
			}

			bool Intersect(Ptr<const Point2D> point, Ptr<const Box2D> box)
			{
				Float2 boxAxis1 = box->GetRelativeHeightAxis();
				Float2 boxAxis2 = box->GetRelativeWidthAxis();

				auto axisCollision = [point, box](Float2 axis)
				{
					List<Float2> boxProjections = List<Float2>(4);
					Push(boxProjections, Project(box->GetTopLeftCorner(), axis));
					Push(boxProjections, Project(box->GetTopRightCorner(), axis));
					Push(boxProjections, Project(box->GetBottomLeftCorner(), axis));
					Push(boxProjections, Project(box->GetBottomRightCorner(), axis));

					Float2 pointProjection = Project(*point, axis);

					float boxMaxScalar = Dot(boxProjections[0], axis);
					float boxMinScalar = Dot(boxProjections[0], axis);
					for (int i = 1; i < 4; i++)
					{
						float dot = Dot(boxProjections[i], axis);
						if (dot > boxMaxScalar)
						{
							boxMaxScalar = dot;
						}

						if (dot < boxMinScalar)
						{
							boxMinScalar = dot;
						}
					}

					float pointScalar = Dot(pointProjection, axis);

					return (pointScalar >= boxMinScalar && pointScalar <= boxMaxScalar);
				};

				return (axisCollision(boxAxis1) && axisCollision(boxAxis2));
			}

			bool Intersect(Ptr<const Point2D> point, Ptr<const Circle2D> circle)
			{
				return circle->PointInCircle(*point);
			}

			// bool Intersect(Ptr<const Point2D> point, Ptr<const Polygon2D> polygon)
			// {
			// 
			// }

			bool Intersect(Ptr<const Line2D> line, Ptr<const Point2D> point)
			{
				return Intersect(point, line);
			}

			// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/amp/
			bool Intersect(Ptr<const Line2D> line1, Ptr<const Line2D> line2)
			{
				enum class Orientation
				{
					Colinear,
					Clockwise,
					CounterClockwise
				};

				Point2D line1Origin = Point2D(line1->GetPosition());
				Point2D line1End = line1Origin + Point2D(line1->GetScale());

				Point2D line2Origin = Point2D(line2->GetPosition());
				Point2D line2End = line2Origin + Point2D(line2->GetScale());

				auto orientation = [](Point2D p1, Point2D p2, Point2D p3)
				{
					float val = ((p2.Y - p1.Y) * (p3.X - p2.X)) - ((p2.X - p1.X) * (p3.Y - p2.Y));

					if (val == 0.0f)
					{
						return Orientation::Colinear;
					}
					else if (val > 0.0f)
					{
						return Orientation::Clockwise;
					}
					return Orientation::CounterClockwise;
				};

				Orientation o1 = orientation(line1Origin, line1End, line2Origin);
				Orientation o2 = orientation(line1Origin, line1End, line2End);
				Orientation o3 = orientation(line2Origin, line2End, line1Origin);
				Orientation o4 = orientation(line2Origin, line2End, line1End);

				if (o1 != o2 && o3 != o4)
				{
					return true;
				}

				if (o1 == Orientation::Colinear && line1->PointOnLine(line2Origin))
				{
					return true;
				}

				if (o2 == Orientation::Colinear && line1->PointOnLine(line2End))
				{
					return true;
				}

				if (o3 == Orientation::Colinear && line2->PointOnLine(line1Origin))
				{
					return true;
				}

				if (o4 == Orientation::Colinear && line2->PointOnLine(line1End))
				{
					return true;
				}

				return false;
			}

			bool Intersect(Ptr<const Line2D> line, Ptr<const Box2D> box)
			{
				auto axisCollision = [line, box](Float2 axis)
				{
					List<Float2> boxProjections = List<Float2>(4);
					Push(boxProjections, Project(box->GetTopLeftCorner(), axis));
					Push(boxProjections, Project(box->GetTopRightCorner(), axis));
					Push(boxProjections, Project(box->GetBottomLeftCorner(), axis));
					Push(boxProjections, Project(box->GetBottomRightCorner(), axis));

					Float2 lineOriginProjection = Project(line->GetPosition(), axis);
					Float2 lineEndProjection = Project(Float2(line->PointAtScale(1.0f)), axis);

					float boxMaxScalar = Dot(boxProjections[0], axis);
					float boxMinScalar = Dot(boxProjections[0], axis);
					for (int i = 1; i < 4; i++)
					{
						float dot = Dot(boxProjections[i], axis);
						if (dot > boxMaxScalar)
						{
							boxMaxScalar = dot;
						}

						if (dot < boxMinScalar)
						{
							boxMinScalar = dot;
						}
					}

					float minLineScalar = Dot(lineOriginProjection, axis);
					float maxLineScalar = minLineScalar;

					float lineEndScalar = Dot(lineEndProjection, axis);
					if (lineEndScalar >= minLineScalar)
					{
						maxLineScalar = lineEndScalar;
					}
					else
					{
						minLineScalar = lineEndScalar;
					}

					return (maxLineScalar >= boxMinScalar && minLineScalar <= boxMaxScalar);
				};

				Float2 boxAxis1 = box->GetRelativeHeightAxis();
				Float2 boxAxis2 = box->GetRelativeWidthAxis();

				return (axisCollision(boxAxis1) && axisCollision(boxAxis2));
			}

			bool Intersect(Ptr<const Line2D> line, Ptr<const Circle2D> circle)
			{
				float distanceToCircleSqr = line->DistanceToPointSqr(circle->GetPosition());
				float radiusSqr = circle->GetScale().X;
				return (distanceToCircleSqr <= radiusSqr);
			}

			// bool Intersect(Ptr<const Line2D> line, Ptr<const Polygon2D> polygon)
			// {
			// 
			// }

			bool Intersect(Ptr<const Box2D> box, Ptr<const Point2D> point)
			{
				return Intersect(point, box);
			}

			bool Intersect(Ptr<const Box2D> box, Ptr<const Line2D> line)
			{
				return Intersect(line, box);
			}

			// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/2d-rotated-rectangle-collision-r2604/
			// the above is also being applies to box/line and box/point collision
			bool Intersect(Ptr<const Box2D> box1, Ptr<const Box2D> box2)
			{
				Float2 box1Axis1 = box1->GetTopRightCorner() - box1->GetTopLeftCorner();
				Float2 box1Axis2 = box1->GetTopRightCorner() - box1->GetBottomRightCorner();

				Float2 box2Axis1 = box2->GetTopRightCorner() - box2->GetBottomRightCorner();
				Float2 box2Axis2 = box2->GetTopLeftCorner() - box2->GetTopRightCorner();

				auto axisCollision = [box1, box2](Float2 axis)
				{
					List<Float2> box1Projections = List<Float2>(4);
					Push(box1Projections, Project(box1->GetTopLeftCorner(), axis));
					Push(box1Projections, Project(box1->GetTopRightCorner(), axis));
					Push(box1Projections, Project(box1->GetBottomLeftCorner(), axis));
					Push(box1Projections, Project(box1->GetBottomRightCorner(), axis));

					List<Float2> box2Projections = List<Float2>(4);
					Push(box2Projections, Project(box2->GetTopLeftCorner(), axis));
					Push(box2Projections, Project(box2->GetTopRightCorner(), axis));
					Push(box2Projections, Project(box2->GetBottomLeftCorner(), axis));
					Push(box2Projections, Project(box2->GetBottomRightCorner(), axis));

					float box1MaxScalar = Dot(box1Projections[0], axis);
					float box1MinScalar = Dot(box1Projections[0], axis);
					for (int i = 1; i < 4; i++)
					{
						float dot = Dot(box1Projections[i], axis);
						if (dot > box1MaxScalar)
						{
							box1MaxScalar = dot;
						}

						if (dot < box1MinScalar)
						{
							box1MinScalar = dot;
						}
					}

					float box2MaxScalar = Dot(box2Projections[0], axis);
					float box2MinScalar = Dot(box2Projections[0], axis);
					for (int i = 1; i < 4; i++)
					{
						float dot = Dot(box2Projections[i], axis);
						if (dot > box2MaxScalar)
						{
							box2MaxScalar = dot;
						}

						if (dot < box2MinScalar)
						{
							box2MinScalar = dot;
						}
					}

					return (box1MinScalar <= box2MaxScalar && box1MaxScalar >= box2MinScalar);
				};

				return (axisCollision(box1Axis1) && axisCollision(box1Axis2) && axisCollision(box2Axis1) && axisCollision(box2Axis2));
			}

			// https://www.gamedev.net/articles/programming/general-and-gameplay-programming/2d-rotated-rectangle-collision-r2604/
			bool Intersect(Ptr<const Box2D> box, Ptr<const Circle2D> circle)
			{
				Point2D rotatedCircleOrigin = RotateVectorBy(circle->GetPosition(), box->GetRotation());

				Float2 boxPosition = box->GetPosition();
				Float2 boxHalfScale = box->GetScale() * 0.5f;

				float nearestX = Clamp(rotatedCircleOrigin.X, boxPosition.X - boxHalfScale.X, boxPosition.X + boxHalfScale.X);
				float nearestY = Clamp(rotatedCircleOrigin.Y, boxPosition.Y - boxHalfScale.Y, boxPosition.Y + boxHalfScale.Y);

				Float2 closestPosition = Float2(nearestX, nearestY);

				return (MagnitudeSqr(circle->GetScale()) >= DistanceSqr(closestPosition, rotatedCircleOrigin));
			}

			// bool Intersect(Ptr<const Box2D> box, Ptr<const Polygon2D> polygon)
			// {
			// 
			// }

			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Point2D> point)
			{
				return Intersect(point, circle);
			}

			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Line2D> line)
			{
				return Intersect(line, circle);
			}

			bool Intersect(Ptr<const Circle2D> circle, Ptr<const Box2D> box)
			{
				return Intersect(box, circle);
			}

			bool Intersect(Ptr<const Circle2D> circle1, Ptr<const Circle2D> circle2)
			{
				Float2 connectingLine = circle1->GetPosition() - circle2->GetPosition();
				float maxReach = circle1->GetScale().X * circle2->GetScale().X;
				return (MagnitudeSqr(connectingLine) <= maxReach);
			}

			// bool Intersect(Ptr<const Circle2D> circle, Ptr<const Polygon2D> polygon)
			// {
			// 
			// }

			// bool Intersect(Ptr<const Polygon2D> polygon1, Ptr<const Polygon2D> polygon2)
			// {
			// 
			// }
		}
	}
}