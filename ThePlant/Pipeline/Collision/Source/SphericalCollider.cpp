#include "Pipeline/Collision/Headers/SphericalCollider.h"

namespace Application {
namespace GameSystem {
  namespace Collision {
    SphericalCollider::SphericalCollider(SharedPtr<const Transform> collisionTransform, float radius, Core::Math::Float3 coefficients)
      : ColliderBase(collisionTransform), Radius(radius), Coefficients(coefficients)
    {}

    float SphericalCollider::GetBoundingRadius() const
    {
      return Radius;
    }

    void SphericalCollider::SetCoefficients(Core::Math::Float3 coefficients)
    {
      Coefficients = coefficients;
    }
  }// namespace Collision
}// namespace GameSystem
}// namespace Application