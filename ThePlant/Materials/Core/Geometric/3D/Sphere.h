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

  float Distance(const Sphere& sphere, const Math::Float3& point);
  float Distance(const Math::Float3& point, const Sphere& sphere)
  {
    return Distance(sphere, point);
  }
  float Distance(const Sphere& sphere, const Line3D& line);
  float Distance(const Line3D& line, const Sphere& sphere)
  {
    return Distance(sphere, line);
  }
  float Distance(const Sphere& sphere, const Plane& plane);
  float Distance(const Plane& plane, const Sphere& sphere)
  {
    return Distance(sphere, plane);
  }
  float Distance(const Sphere& sphere1, const Sphere& sphere2);

  bool Intersect(const Sphere& sphere, const Math::Float3& point, const float& variance = 0.01f);
  bool Intersect(const Math::Float3& point, const Sphere& sphere, const float& variance = 0.01f)
  {
    return Intersect(sphere, point, variance);
  }
  bool Intersect(const Sphere& sphere, const Line3D& line, const float& variance = 0.01f);
  bool Intersect(const Line3D& line, const Sphere& sphere, const float& variance = 0.01f)
  {
    return Intersect(sphere, line, variance);
  }
  bool Intersect(const Sphere& sphere, const Plane& plane, const float& variance = 0.01f);
  bool Intersect(const Plane& plane, const Sphere& sphere, const float& variance = 0.01f)
  {
    return Intersect(sphere, plane, variance);
  }
  bool Intersect(const Sphere& sphere1, const Sphere& sphere2, const float& variance = 0.01f);
}// namespace Geometric
}// namespace Core