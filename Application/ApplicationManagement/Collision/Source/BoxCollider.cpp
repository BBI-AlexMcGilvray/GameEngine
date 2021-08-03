#include "ApplicationManagement/Collision/Headers/BoxCollider.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    BoxCollider::BoxCollider(SharedPtr<const Transform> collisionTransform, Float3 dimensions)
      : BoxCollider(collisionTransform, -0.5f * dimensions, 0.5f * dimensions)
    {}

    BoxCollider::BoxCollider(SharedPtr<const Transform> collisionTransform, Float3 minimum, Float3 maximum)
      : ColliderBase(collisionTransform), Minimum(minimum), Maximum(maximum)
    {}

    float BoxCollider::GetBoundingRadius() const
    {
      return Distance(Minimum, Maximum);
    }

    Float3 BoxCollider::GetDimensions()
    {
      return (Maximum - Minimum);
    }

    void BoxCollider::SetDimensions(Float3 dimensions)
    {
      Minimum = (-0.5f * dimensions);
      Maximum = (0.5f * dimensions);
    }
  }// namespace Collision
}// namespace GameSystem
}// namespace Application