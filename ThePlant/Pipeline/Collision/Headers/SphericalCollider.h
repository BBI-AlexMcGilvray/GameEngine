#pragma once

#include "Pipeline\Collision\Headers\ColliderBase.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    struct SphericalCollider : ColliderBase
    {
      ColliderType GetColliderType() const override
      {
        return ColliderType::Sphere;
      }

      float Radius;
      Float3 Coefficients;

      SphericalCollider(SharedPtr<const Transform> collisionTransform, float radius = 1.0f, Float3 coefficients = 1.0f);

      float GetBoundingRadius() const override;

      void SetCoefficients(Float3 coefficients);
    };
  }// namespace Collision
}// namespace GameSystem
}// namespace Application