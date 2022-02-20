#include "Core/Geometric/Functions.h"

#include "Core/Debugging/Profiling/Utils.h"

namespace Core {
namespace Geometric {
namespace INTERNAL_HELPER {
    // given two variants, will call the appropriate DistanceSqr(...) method for the two types held by them respectively
    struct ShapeVisitor_DistanceSqr
    {
        ShapeVisitor_DistanceSqr(const Transform& transform1, const Transform& transform2)
        : transform1(transform1)
        , transform2(transform2)
        {}

        template <typename SHAPE1, typename SHAPE2>
        float operator()(const SHAPE1& shape1, const SHAPE2& shape2) const
        {
            return DistanceSqr(ShapeOrientation<SHAPE1>(transform1, shape1), ShapeOrientation<SHAPE2>(transform2, shape2));
        }

    private:
        const Transform& transform1;
        const Transform& transform2;
    };

    // given two variants, will call the appropriate Engulfs(...) method for the two types held by them respectively
    struct ShapeVisitor_Engulfs
    {
        ShapeVisitor_Engulfs(const Transform& transform1, const Transform& transform2)
        : transform1(transform1)
        , transform2(transform2)
        {}

        template <typename SHAPE1, typename SHAPE2>
        bool operator()(const SHAPE1& shape1, const SHAPE2& shape2) const
        {
            return Engulfs(ShapeOrientation<SHAPE1>(transform1, shape1), ShapeOrientation<SHAPE2>(transform2, shape2));
        }

    private:
        const Transform& transform1;
        const Transform& transform2;
    };

    // given two variants, will call the appropriate Intersect(...) method for the two types held by them respectively
    struct ShapeVisitor_Intersect
    {
        ShapeVisitor_Intersect(const Transform& transform1, const Transform& transform2, const float& precision)
        : transform1(transform1)
        , transform2(transform2)
        , _precision(precision)
        {}

        template <typename SHAPE1, typename SHAPE2>
        bool operator()(const SHAPE1& shape1, const SHAPE2& shape2) const
        {
            return Intersect(ShapeOrientation<SHAPE1>(transform1, shape1), ShapeOrientation<SHAPE2>(transform2, shape2), _precision);
        }

    private:
        const Transform& transform1;
        const Transform& transform2;
        const float _precision;
    };
} // namespace INTERNAL_HELPER

/*
// NOTE: We may want a
Math::Float2 IntersectionPoint(...)
method, but that can wait - likely much more complex

// NOTE: How are we handling 2D<->3D collision? We should make a plane from the 2D (representing the default 2D plane) and do it that way
    - yes
*/

float DistanceSqr(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d)
{
    return DistanceSqr(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}

float DistanceSqr(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d)
{
    return DistanceSqr(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}

float DistanceSqr(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2)
{
    DEBUG_PROFILE_SCOPE("DistanceSqr(Shape3D, Shape3D)");

    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_DistanceSqr(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

float DistanceSqr(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2)
{
    DEBUG_PROFILE_SCOPE("DistanceSqr(Shape2D, Shape2D)");

    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_DistanceSqr(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

bool Engulfs(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d)
{
    return Engulfs(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)));
}

bool Engulfs(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d)
{
    // 2d can't contain 3d
    return false;
}

bool Engulfs(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2)
{
    DEBUG_PROFILE_SCOPE("Engulfs(Shape3D, Shape3D)");

    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Engulfs(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

bool Engulfs(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2)
{
    DEBUG_PROFILE_SCOPE("Engulfs(Shape2D, Shape2D)");

    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Engulfs(shape1.orientation, shape2.orientation), shape1.shape, shape2.shape);
}

bool Intersect(const ShapeOrientation3D& shape_3d, const ShapeOrientation2D& shape_2d, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    return Intersect(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)), precision);
}

bool Intersect(const ShapeOrientation2D& shape_2d, const ShapeOrientation3D& shape_3d, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    return Intersect(shape_3d, ShapeOrientation3D(shape_2d.orientation, Shape2DAsPlane(shape_2d.shape)), precision);
}

bool Intersect(const ShapeOrientation3D& shape1, const ShapeOrientation3D& shape2, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    DEBUG_PROFILE_SCOPE("Intersect(Shape3D, Shape3D)");

    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Intersect(shape1.orientation, shape2.orientation, precision), shape1.shape, shape2.shape);
}

bool Intersect(const ShapeOrientation2D& shape1, const ShapeOrientation2D& shape2, const float& precision/* = Math::DEFAULT_PRECISION()*/)
{
    DEBUG_PROFILE_SCOPE("Intersect(Shape2D, Shape2D)");

    // since the '.shape' is the variant, we need to pass the transforms along in the visitor
    // this should have the benefit of maintaining them as references as well, so we have less copies
    return std::visit(INTERNAL_HELPER::ShapeVisitor_Intersect(shape1.orientation, shape2.orientation, precision), shape1.shape, shape2.shape);
}
} // namespace Geometric
} // namespace Core