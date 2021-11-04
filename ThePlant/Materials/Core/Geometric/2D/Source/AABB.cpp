#include "Core/Geometric/2D/Headers/AABB.h"

namespace Core {
namespace Geometric {
  AABB2D::AABB2D()
    : AABB2D(Transform())
  {}

  AABB2D::AABB2D(const Transform &origin)
    : AABB2D(origin, 1.0f, 1.0f)
  {}

  AABB2D::AABB2D(const float &width, const float &height)
    : AABB2D(Transform(), width, height)
  {}

  AABB2D::AABB2D(const Transform& origin, const float &width, const float &height)
    : _origin(origin)
    , _halfSize(width * 0.5f, height * 0.5f)
  {}

  void AABB2D::SetWidth(const float& width)
  {
    _halfSize.X = width * 0.5f;
  }

  float AABB2D::GetWidth() const
  {
    return _halfSize.X * 2.0f;
  }

  void AABB2D::SetHeight(const float& height)
  {
    _halfSize.Y = height * 0.5f;
  }

  float AABB2D::GetHeight() const
  {
    return _halfSize.Y * 2.0f;
  }

  void AABB2D::SetPosition(const Math::Float2 &origin)
  {
    _origin.SetPosition(Math::Float3(origin));
  }

  void AABB2D::AdjustPosition(const Math::Float2 &adjustment)
  {
    _origin.AdjustPosition(Math::Float3(adjustment));
  }

  Math::Float2 AABB2D::GetPosition() const
  {
    return _origin.GetPosition();
  }

  void AABB2D::SetScale(const float &scale)
  {
    _origin.SetScale(scale);
  }

  void AABB2D::SetScale(const Math::Float2 &scale)
  {
    _origin.SetScale(Math::Float3(scale));
  }

  void AABB2D::AdjustScale(const float &adjustment)
  {
    _origin.AdjustScale(adjustment);
  }

  void AABB2D::AdjustScale(const Math::Float2 &adjustment)
  {
    _origin.AdjustScale(Math::Float3(adjustment));
  }

  Math::Float2 AABB2D::GetScale() const
  {
    return _origin.GetScale();
  }

  std::array<Math::Float2, 4> AABB2D::GetAllCorners() const
  {
    std::array<Math::Float2, 4> allCorners = 
    {
      GetBottomLeftCorner(),
      GetTopLeftCorner(),
      GetTopRightCorner(),
      GetBottomRightCorner()
    };

    return allCorners;
  }

  Math::Float2 AABB2D::GetTopLeftCorner() const
  {
    Math::Float3 center = _origin.GetPosition();
    Math::Float2 halfSize = _GetEffectiveHalfSize();
    Math::Float2 topLeft = Math::Float2(center.X - halfSize.X, center.Y + halfSize.Y);
    return topLeft;
  }

  Math::Float2 AABB2D::GetTopRightCorner() const
  {
    Math::Float3 center = _origin.GetPosition();
    Math::Float2 halfSize = _GetEffectiveHalfSize();
    Math::Float2 topRight = Math::Float2(center.X + halfSize.X, center.Y + halfSize.Y);
    return topRight;
  }

  Math::Float2 AABB2D::GetBottomLeftCorner() const
  {
    Math::Float3 center = _origin.GetPosition();
    Math::Float2 halfSize = _GetEffectiveHalfSize();
    Math::Float2 bottomLeft = Math::Float2(center.X - halfSize.X, center.Y - halfSize.Y);
    return bottomLeft;
  }

  Math::Float2 AABB2D::GetBottomRightCorner() const
  {
    Math::Float3 center = _origin.GetPosition();
    Math::Float2 halfSize = _GetEffectiveHalfSize();
    Math::Float2 bottomRight = Math::Float2(center.X + halfSize.X, center.Y - halfSize.Y);
    return bottomRight;
  }

  Math::Float2 AABB2D::_GetEffectiveHalfSize() const
  {
    return _halfSize * GetScale();
  }
}// namespace Geometric
}// namespace Core