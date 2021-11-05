#pragma once

#include "Pipeline\Collision\Headers\ColliderBase.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    struct BoxCollider : ColliderBase
    {
      ColliderType GetColliderType() const override
      {
        return ColliderType::Box;
      }

      Core::Math::Float3 Minimum;
      Core::Math::Float3 Maximum;

      BoxCollider(SharedPtr<const Transform> collisionTransform, Core::Math::Float3 dimensions = 1.0f);
      BoxCollider(SharedPtr<const Transform> collisionTransform, Core::Math::Float3 minimum = -0.5f, Core::Math::Float3 maximum = 0.5f);

      float GetBoundingRadius() const override;
      Core::Math::Float3 GetDimensions();

      void SetDimensions(Core::Math::Float3 dimensions);
    };
  }// namespace Collision
}// namespace GameSystem
}// namespace Application