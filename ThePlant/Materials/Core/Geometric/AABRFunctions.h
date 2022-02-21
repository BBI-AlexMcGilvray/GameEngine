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

    AABR AABRFor(const Spot2D& point);
    ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Spot2D>& point);
    AABR AABRFor(const Line2D& line);
    ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Line2D>& line);
    AABR AABRFor(const Circle& circle);
    ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Circle>& circle);
    AABR AABRFor(const Rectangle& rectangle);
    ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Rectangle>& rectangle);
    AABR AABRFor(const Shape2D& shape);
    ShapeOrientation<AABR> AABRFor(const ShapeOrientation2D& shape);
} // namespace Geometric
} // namespace Core