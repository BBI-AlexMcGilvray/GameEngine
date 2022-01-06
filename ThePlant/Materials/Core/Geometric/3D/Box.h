#pragma once

#include "Core/Math/Headers/Vector3.h"

namespace Core {
namespace Geometric {
  struct Line3D;
  struct Plane;
  struct Sphere;

  // CAN'T be rotated - at least not yet. keep it simple for now
  struct Box
  {
    Box(const Math::Float3& origin);
    Box(const Math::Float3& min, const Math::Float3& max);

    Box(const Box&) = default;
    Box(Box&&) = default;
    Box& operator=(const Box&) = default;
    Box& operator=(Box&&) = default;

    bool operator==(const Box& other) const;
    bool operator!=(const Box& other) const;

    void SetMin(const Math::Float3& min);
    void AdjustMin(const Math::Float3& adjustment);
    Math::Float3 GetMin() const;

    void SetMax(const Math::Float3& max);
    void AdjustMax(const Math::Float3& adjustment);
    Math::Float3 GetMax() const;

    Math::Float3 GetDimensions() const;
    Math::Float3 GetOrigin() const;

  private:
    Math::Float3 _min;
    Math::Float3 _max;
  };

  Box FromDimensions(const Math::Float3& origin, const Math::Float3& dimensions);

  float Distance(const Box& box, const Math::Float3& point);
  float Distance(const Box& box, const Line3D& line);
  float Distance(const Box& box, const Plane& plane);
  float Distance(const Box& box, const Sphere& sphere);
  float Distance(const Box& box1, const Box& box2);

  bool Intersect(const Box& box, const Math::Float3& point);
  bool Intersect(const Box& box, const Line3D& line);
  bool Intersect(const Box& box, const Plane& plane);
  bool Intersect(const Box& box, const Sphere& sphere);
  bool Intersect(const Box& box1, const Box& box2);
}// namespace Geometric
}// namespace Core