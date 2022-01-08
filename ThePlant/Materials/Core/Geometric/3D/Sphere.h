#pragma once

#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Geometric {
  struct Line3D;
  struct Plane;

  struct Sphere
  {
    Sphere(const Math::Float3& origin);
    Sphere(const Math::Float3& origin, const float& radius);

    Sphere(const Sphere&) = default;
    Sphere(Sphere&&) = default;
    Sphere& operator=(const Sphere&) = default;
    Sphere& operator=(Sphere&&) = default;

    bool operator==(const Sphere& other) const;
    bool operator!=(const Sphere& other) const;

    void SetRadius(const float& radius);
    void AdjustRadius(const float& adjustment);
    float GetRadius() const;

    void SetOrigin(const Math::Float3 &origin);
    void AdjustOrigin(const Math::Float3 &adjustment);
    Math::Float3 GetOrigin() const;

  private:
    Math::Float3 _origin;
    float _radius;
  };
}// namespace Geometric
}// namespace Core