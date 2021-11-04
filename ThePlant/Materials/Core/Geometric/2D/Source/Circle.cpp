#include "Core/Geometric/2D/Headers/Circle.h"

namespace Core {
namespace Geometric {
  Circle2D::Circle2D()
    : Circle2D(Transform(), 1.0f)
  {}

  Circle2D::Circle2D(const Transform &origin)
    : Circle2D(origin, 1.0f)
  {}

  Circle2D::Circle2D(const Transform &origin, const float &radius)
    : _origin(origin), _radius(radius)
  {}

  void Circle2D::SetRadius(const float& radius)
  {
    _radius = radius;
  }

  float Circle2D::GetRadius() const
  {
    return _radius * GetScale(); // it is a circle, so x/y scales should be the same anyway
  }

  void Circle2D::SetPosition(const Math::Float2 &origin)
  {
    _origin.SetPosition(Math::Float3(origin));
  }

  void Circle2D::AdjustPosition(const Math::Float2 &adjustment)
  {
    _origin.AdjustPosition(Math::Float3(adjustment));
  }

  Math::Float2 Circle2D::GetPosition() const
  {
    return _origin.GetPosition();
  }

  void Circle2D::SetScale(const float &scale)
  {
    _origin.SetScale(scale);
  }

  void Circle2D::AdjustScale(const float &adjustment)
  {
    _origin.AdjustScale(adjustment);
  }

  float Circle2D::GetScale() const
  {
    // Scale is always set to the same value, doesn't matter which i get
    return _origin.GetScale().X;
  }

  float Circle2D::_GetEffectiveRadius() const
  {
    return GetScale() * _radius;
  }
}// namespace Geometric
}// namespace Core