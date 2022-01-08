#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

namespace Core {
namespace Geometric {
  struct Plane;

  struct Line3D
  {
    Line3D();
    Line3D(const Math::Float3 &origin, const Math::Float3 &direction); // infinite
    Line3D(const Math::Float3 &origin, const Math::Float3 &direction, const float& length); // gives an set-length line in the given direction

    Line3D(const Line3D&) = default;
    Line3D(Line3D&&) = default;
    Line3D& operator=(const Line3D&) = default;
    Line3D& operator=(Line3D&&) = default;

    bool operator==(const Line3D& other) const;
    bool operator!=(const Line3D& other) const;

    void SetOrigin(const Math::Float3 &origin);
    void AdjustOrigin(const Math::Float3 &adjustment);
    Math::Float3 GetOrigin() const;

    void SetDirection(const Math::Float3& direction);
    void AdjustDirection(const Math::Float3& adjustment);
    Math::Float3 GetDirection() const;

    void SetLength(const float& length);
    void AdjustLength(const float& adjustment);
    float GetLength() const;

    void SetInfinite();
    bool IsInfinite() const;

    Plane GetNormal(const Math::Float3& atPoint) const;

  private:
    Math::Float3 _origin;
    Math::Float3 _direction;
    float _length;
    bool _infinite;
  };

  Line3D Rotate(const Line3D& line, const Math::FQuaternion& rotation);
}// namespace Geometric
}// namespace Core