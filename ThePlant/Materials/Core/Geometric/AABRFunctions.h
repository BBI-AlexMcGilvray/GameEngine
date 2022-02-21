#pragma once

#include <utility>

#include "Core/Geometric/GeometryDefs.h"

namespace Core {
namespace Geometric {
    AABR EffectiveAABR(const ShapeOrientation<AABR>& aabr);

    Math::Float3 HalfDimensions(const AABR& aabr);
    Math::Float3 HalfDimensions(const ShapeOrientation<AABR>& aabr);

    Math::Float3 AABRMax(const AABR& aabr);
    Math::Float3 AABRMax(const ShapeOrientation<AABR>& aabr);
    Math::Float3 AABRMin(const AABR& aabr);
    Math::Float3 AABRMin(const ShapeOrientation<AABR>& aabr);
    std::pair<Math::Float3, Math::Float3> AABRMinMax(const AABR& aabr);
    std::pair<Math::Float3, Math::Float3> AABRMinMax(const ShapeOrientation<AABR>& aabr);

    Rectangle RemoveAA(const AABR& aabr);
    ShapeOrientation<Rectangle> RemoveAA(const ShapeOrientation<AABR>& aabr);

    AABR BoundingFor(const Spot2D& point);
    ShapeOrientation<AABR> BoundingFor(const ShapeOrientation<Spot2D>& point);
    AABR BoundingFor(const Line2D& line);
    ShapeOrientation<AABR> BoundingFor(const ShapeOrientation<Line2D>& line);
    AABR BoundingFor(const Circle& circle);
    ShapeOrientation<AABR> BoundingFor(const ShapeOrientation<Circle>& circle);
    AABR BoundingFor(const Rectangle& rectangle);
    ShapeOrientation<AABR> BoundingFor(const ShapeOrientation<Rectangle>& rectangle);
    AABR BoundingFor(const Shape2D& shape);
    ShapeOrientation<AABR> BoundingFor(const ShapeOrientation2D& shape);
} // namespace Geometric
} // namespace Core