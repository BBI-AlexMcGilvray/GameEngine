#pragma once

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Quaternion.h"

namespace Core {
namespace Geometric {
  struct Line2D
  {
    Line2D();
    Line2D(const Math::Float2 &origin, const Math::Float2 &endPoint, const bool& infinite = false); // a line using endpoint as either direction or enpoint depending on if it is infinite
    Line2D(const Math::Float2 &origin, const Math::Float2 &direction, const float& length); // gives an set-length line in the given direction

    void SetOrigin(const Math::Float2 &origin);
    void AdjustOrigin(const Math::Float2 &adjustment);
    Math::Float2 GetOrigin() const;

    void SetEndpoint(const Math::Float2& endPoint);
    void AdjustEndpoint(const Math::Float2& adjustment);
    Math::Float2 GetEndpoint() const;

    void SetInfinite(const bool& infinite);
    bool IsInfinite() const;

    void RotateLine(const Math::FQuaternion &rotation);

    Math::Float2 GetDirection() const;
    Math::Float2 GetNormal() const;

  private:
    Math::Float2 _origin;
    Math::Float2 _endPoint;
    bool _infinite;
  };
}// namespace Geometric
}// namespace Core