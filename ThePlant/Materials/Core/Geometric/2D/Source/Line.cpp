#include "Core/Geometric/2D/Headers/Line.h"

#include "Core/Math/Headers/QuaternionFunctions.h"

namespace Core {
namespace Geometric {
    Line2D::Line2D()
    : Line2D(Math::Float2(0.0f, 0.0f), Math::Float2(1.0f, 1.0f))
    {}

    Line2D::Line2D(const Math::Float2 &origin, const Math::Float2 &endPoint, const bool& infinite/* = false*/)
    : _origin(origin)
    , _endPoint(endPoint)
    , _infinite(infinite)
    {}

    Line2D::Line2D(const Math::Float2 &origin, const Math::Float2 &direction, const float& length)
    : _origin(origin)
    , _endPoint(origin + (Math::Normalize(direction) * length))
    , _infinite(false)
    {}

    void Line2D::SetOrigin(const Math::Float2 &origin)
    {
      _origin = origin;
    }

    void Line2D::AdjustOrigin(const Math::Float2 &adjustment)
    {
      _origin += adjustment;
    }

    Math::Float2 Line2D::GetOrigin() const
    {
      return _origin;
    }

    void Line2D::SetEndpoint(const Math::Float2& endPoint)
    {
      _endPoint = endPoint;
    }

    void Line2D::AdjustEndpoint(const Math::Float2& adjustment)
    {
      _endPoint += adjustment;
    }

    Math::Float2 Line2D::GetEndpoint() const
    {
      return _endPoint;
    }

    void Line2D::SetInfinite(const bool& infinite)
    {
      _infinite = infinite;
    }

    bool Line2D::IsInfinite() const
    {
      return _infinite;
    }

    void Line2D::RotateLine(const Math::FQuaternion &rotation)
    {
      Math::Float2 direction = _endPoint - _origin;
      Math::Float2 rotatedDirection = Math::RotateVectorBy(direction, rotation);

      _endPoint = _origin + rotatedDirection;
    }

    Math::Float2 Line2D::GetDirection() const
    {
      return _endPoint - _origin;
    }

    Math::Float2 Line2D::GetNormal() const
    {
      Math::Float2 direction = GetDirection();
      return Math::Float2(direction.X, -direction.Y);
    }
}// namespace Geometric
}// namespace Core