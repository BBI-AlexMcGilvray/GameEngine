#pragma once

#include <array>

#include "Core/Geometric/Headers/Transform.h"

namespace Core {
namespace Geometric {
  // should this be split out to be made up of a 'box (width and height)' and a transform?
  // maybe only if that ends up being actually useful 
  struct AABB2D
  {
    AABB2D();
    AABB2D(const Transform &origin);
    AABB2D(const float &width, const float &height);
    AABB2D(const Transform &origin, const float &width, const float &height);

    void SetWidth(const float& width);
    float GetWidth() const;

    void SetHeight(const float& height);
    float GetHeight() const;

    void SetPosition(const Math::Float2 &position);
    void AdjustPosition(const Math::Float2 &adjustment);
    Math::Float2 GetPosition() const;

    // AABBs do not rotate

    void SetScale(const float &scale);
    void SetScale(const Math::Float2 &scale);
    void AdjustScale(const float &adjustment);
    void AdjustScale(const Math::Float2 &adjustment);
    Math::Float2 GetScale() const;

    std::array<Math::Float2, 4> GetAllCorners() const;

    Math::Float2 GetTopLeftCorner() const;
    Math::Float2 GetTopRightCorner() const;
    Math::Float2 GetBottomLeftCorner() const;
    Math::Float2 GetBottomRightCorner() const;

  private:
    Transform _origin;

    Math::Float2 _halfSize;

    Math::Float2 _GetEffectiveHalfSize() const;
  };
}// namespace Geometric
}// namespace Core