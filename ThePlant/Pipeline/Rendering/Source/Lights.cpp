#include "Pipeline/Rendering/Headers/Lights.h"

#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Application {
namespace Rendering {
  BaseLight::BaseLight(SharedPtr<Transform> position, float intensity, Color lightColor)
    : Position(position), LightColor(lightColor), Intensity(intensity)
  {}

  void BaseLight::Update(Second dt)
  {}

  Float3 BaseLight::GetPosition() const
  {
    return Position->GetPosition();
  }

  Color BaseLight::GetColor() const
  {
    return LightColor;
  }

  // Point Light

  float PointLight::GetIntensity(const Float3 &position) const
  {
    if (Intensity == Inf_F) {
      return Inf_F;
    }

    auto distanceSqr = MagnitudeSqr(position - Position->GetPosition());
    return (Intensity / distanceSqr);
  }

  // Directional Light

  DirectionalLight::DirectionalLight(SharedPtr<Transform> position, Float3 direction, Rad coneAngle, Color lightColor, float intensity)
    : BaseLight(position, intensity, lightColor), Direction(direction), ConeAngle(coneAngle)
  {}

  float DirectionalLight::GetIntensity(const Float3 &position) const
  {
    auto toPosition = (position - Position->GetPosition());
    auto facingDirection = RotateVectorBy(Direction, Position->GetRotation());

    auto angle = AngleBetweenVectors(toPosition, facingDirection);

    // the position is in the opposite direction of the light or is outside of the light's angle
    if (angle <= 0.0f || angle > ConeAngle) {
      return 0.0f;
    }

    if (Intensity == Inf_F) {
      return Inf_F;
    }

    auto distanceSqr = MagnitudeSqr(toPosition);
    return (Intensity / distanceSqr);
  }
}// namespace Rendering
}// namespace Application