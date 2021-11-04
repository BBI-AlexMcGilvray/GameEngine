#pragma once

#include "Core/Geometric/Headers/Transform.h"

namespace Core {
namespace Geometric {
  struct Circle2D
  {
    Circle2D();
    Circle2D(const Transform &origin);
    Circle2D(const Transform &origin, const float &radius);

    void SetRadius(const float& radius);
    float GetRadius() const;

    void SetPosition(const Math::Float2 &position);
    void AdjustPosition(const Math::Float2 &adjustment);
    Math::Float2 GetPosition() const;

    // circles can't be rotated

    // scale must be equivalent between X and Y so handling Float2s do not make sense
    void SetScale(const float &scale);
    void AdjustScale(const float &adjustment);
    float GetScale() const;

  private:
    Transform _origin;
    float _radius;

    float _GetEffectiveRadius() const;
  };
}// namespace Geometric
}// namespace Core