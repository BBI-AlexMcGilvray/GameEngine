#include "Core/Geometric/AABRFunctions.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Geometric/AABRFunctions.h"
#include "Core/Geometric/RectangleFunctions.h"
#include "Core/Geometric/Line2DFunctions.h"
#include "Core/Geometric/CircleFunctions.h"

namespace Core {
namespace Geometric {
AABR EffectiveAABR(const ShapeOrientation<AABR>& aabr)
{
    VERIFY_2D(aabr);

    return AABR(aabr.shape.dimensions * aabr.orientation.scale.XY);
}

Math::Float3 HalfDimensions(const AABR& aabr)
{
    return aabr.dimensions * 0.5f;
}

Math::Float3 HalfDimensions(const ShapeOrientation<AABR>& aabr)
{
    return HalfDimensions(EffectiveAABR(aabr));
}

Math::Float3 AABRMax(const AABR& aabr)
{
    return HalfDimensions(aabr);   
}

Math::Float3 AABRMax(const ShapeOrientation<AABR>& aabr)
{
    return aabr.orientation.position + HalfDimensions(aabr);
}

Math::Float3 AABRMin(const AABR& aabr)
{
    return HalfDimensions(aabr) * -1.0f;
}

Math::Float3 AABRMin(const ShapeOrientation<AABR>& aabr)
{
    return aabr.orientation.position - HalfDimensions(aabr);
}

std::pair<Math::Float3, Math::Float3> AABRMinMax(const AABR& aabr)
{
    return { AABRMin(aabr), AABRMax(aabr) };
}

std::pair<Math::Float3, Math::Float3> AABRMinMax(const ShapeOrientation<AABR>& aabr)
{
    AABR effectiveAABR = EffectiveAABR(aabr);
    return { aabr.orientation.position + AABRMin(effectiveAABR), aabr.orientation.position + AABRMax(effectiveAABR) };
}

AABR AABRFor(const Spot2D& point)
{
    return AABR(Math::Float2(0.0f));
}

ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Spot2D>& point)
{
    return ShapeOrientation<AABR>(point.orientation, AABRFor(point.shape));
}

AABR AABRFor(const Line2D& line)
{
    if (line.infinite)
    {
        return AABR(line.line, Math::Vector2<bool>(line.line.X != 0.0f, line.line.Y != 0.0f));
    }

    CORE_THROW("AABRFunctions", "Unfinished Implementation");
    // return AABR(LineEndpoint(line)); // line is centered on 0 so this gives the full line dimensions, the line is properly centered by the 0.5 adjustment below
}

ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Line2D>& line)
{
    const auto effectiveLine = EffectiveDirection(line);
    Orientation aabbOrientation = line.orientation;
    aabbOrientation.position -= effectiveLine * 0.5f; // need to center the AABB

    return ShapeOrientation<AABR>(aabbOrientation, AABRFor(Line2D(effectiveLine, line.shape.infinite)));
}

AABR AABRFor(const Circle& circle)
{
    return AABR(Math::Float2(circle.radius * 2.0f));
}

ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Circle>& circle)
{
    CORE_THROW("AABRFunctions", "Unfinished Implementation");
    // return ShapeOrientation<AABR>(circle.orientation, AABRFor(EffectiveRadius(circle)));
}

AABR AABRFor(const Rectangle& rectangle)
{
    return AABR(rectangle.dimensions);
}

ShapeOrientation<AABR> AABRFor(const ShapeOrientation<Rectangle>& rectangle)
{
    CORE_THROW("AABRFunctions", "Unfinished Implementation");
    // const auto rectangleCorners = RectangleCorners(rectangle);
    // Math::Float2 fullMin = rectangleCorners[0];
    // Math::Float2 fullMax = rectangleCorners[0];
    // for (size_t i = 1; i < rectangleCorners.size(); ++i)
    // {
    //     fullMin = Math::Min(fullMin, rectangleCorners[i]);
    //     fullMax = Math::Max(fullMax, rectangleCorners[i]);
    // }
    // Math::Float2 fullDimensions = fullMax - fullMin;

    // return ShapeOrientation<AABB>(rectangle.orientation, AABBFor(Rectangle(fullDimensions)));
}

struct ShapeVisitor2D_AABR
{
    template <typename SHAPE>
    AABR operator()(const SHAPE& shape) const
    {
        return AABRFor(shape);
    }
};

struct ShapeVisitor2D_ShapeOrientationAABR
{
    ShapeVisitor2D_ShapeOrientationAABR(const Orientation& transform)
    : transform(transform)
    {}

    template <typename SHAPE>
    ShapeOrientation<AABR> operator()(const SHAPE& shape) const
    {
        return AABRFor(ShapeOrientation<SHAPE>(transform, shape));
    }

private:
    const Orientation& transform;
};

AABR AABRFor(const Shape2D& shape)
{
    return std::visit(ShapeVisitor2D_AABR(), shape);
}

ShapeOrientation<AABR> AABRFor(const ShapeOrientation2D& shape)
{
    return std::visit(ShapeVisitor2D_ShapeOrientationAABR(shape.orientation), shape.shape);
}
} // namespace Geometric
} // namespace Core