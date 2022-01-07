#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

namespace Core {
namespace Geometric {
  struct Line3D;

  struct Plane
  {
    Plane();
    Plane(const Line3D& line);
    Plane(const Math::Float3& normal, const Math::Float3& origin);
    Plane(const Math::Float3& normal, const Math::Float3& origin, const Math::Float2& dimensions);

    template <int AXIS>
    Plane(const Math::Float3& origin, const Core::Math::Axis<AXIS>& axis)
    {

    }

    template <int AXIS>
    Plane(const Math::Float3& origin, const Math::Float2& dimensions, const Core::Math::Axis<AXIS>& axis)
    {

    }

    Plane(const Plane&) = default;
    Plane(Plane&&) = default;
    Plane& operator=(const Plane&) = default;
    Plane& operator=(Plane&&) = default;

    bool operator==(const Plane& other) const;
    bool operator!=(const Plane& other) const;

    void SetNormal(const Math::Float3 &normal);
    void AdjustNormal(const Math::Float3 &adjustment);
    Math::Float3 GetNormal() const;

    void SetOrigin(const Math::Float3& origin);
    void AdjustOrigin(const Math::Float3& adjustment);
    Math::Float3 GetOrigin() const;

    void SetDimensions(const Math::Float2& dimensions);
    void AdjustDimensions(const Math::Float2& adjustment);
    Math::Float2 GetDimensions() const;

    void SetInfinite();
    bool IsInfinite() const;

  private:
    Math::Float3 _normal;
    Math::Float3 _origin;
    Math::Float2 _dimensions;
    bool _infinite;
  };

  Plane BetweenPoints(const Math::Float3& point1, const Math::Float3& point2, const Math::Float3& point3);
  Plane BetweenPoints(const Math::Float3& point1, const Math::Float3& point2, const Math::Float3& point3, const Math::Float2& dimensions);

  Plane Rotate(const Plane& plane, const Math::FQuaternion& rotation);

  float Distance(const Plane& plane, const Math::Float3& point);
  float Distance(const Math::Float3& point, const Plane& plane)
  {
    return Distance(plane, point);
  }
  float Distance(const Plane& plane, const Line3D& line);
  float Distance(const Line3D& line, const Plane& plane)
  {
    return Distance(plane, line);
  }
  float Distance(const Plane& plane1, const Plane& plane2);

  bool Intersect(const Plane& plane, const Math::Float3& point, const float& variance = 0.01f);
  bool Intersect(const Math::Float3& point, const Plane& plane, const float& variance = 0.01f)
  {
    return Intersect(plane, point, variance);
  }
  bool Intersect(const Plane& plane, const Line3D& line, const float& variance = 0.01f);
  bool Intersect(const Line3D& line, const Plane& plane, const float& variance = 0.01f)
  {
    return Intersect(plane, line, variance);
  }
  bool Intersect(const Plane& plane1, const Plane& plane2, const float& variance = 0.01f);
}// namespace Geometric
}// namespace Core