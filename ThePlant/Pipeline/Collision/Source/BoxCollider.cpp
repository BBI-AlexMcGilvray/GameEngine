#include "Pipeline/Collision/Headers/BoxCollider.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    BoxCollider::BoxCollider(SharedPtr<const Transform> collisionTransform, Core::Math::Float3 dimensions)
      : BoxCollider(collisionTransform, dimensions * -0.5f, dimensions * 0.5f)
    {}

    BoxCollider::BoxCollider(SharedPtr<const Transform> collisionTransform, Core::Math::Float3 minimum, Core::Math::Float3 maximum)
      : ColliderBase(collisionTransform), Minimum(minimum), Maximum(maximum)
    {}

    float BoxCollider::GetBoundingRadius() const
    {
      return Distance(Minimum, Maximum);
    }

    Core::Math::Float3 BoxCollider::GetDimensions()
    {
      return (Maximum - Minimum);
    }

    void BoxCollider::SetDimensions(Core::Math::Float3 dimensions)
    {
      Minimum = (dimensions * -0.5f);
      Maximum = (dimensions * 0.5f);
    }
  }// namespace Collision
}// namespace GameSystem
}// namespace Application