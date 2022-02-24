#pragma once

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"

#include "Core/Math/Headers/Quaternion.h"

#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core;
using namespace Core::Math;

namespace Application {
namespace Rendering {
  // anything needed for camera. should create specifications for perspective and orthographic
  struct Camera
  {
    inline static const Float3 defaultDirection = Float3(0.0f, 0.0f, -1.0f);

    Camera(const float &aspectRatio = 0.5f);

    Camera(const Camera&) = default;
    Camera(Camera&&) = default;

    Camera& operator=(const Camera&) = default;
    Camera& operator=(Camera&&) = default;

    Float4x4 GetProjectionMatrix();

    void SetFOVY(const FRad& fovy);

    void SetAspectRatio(const float& width, const float& height);
    void SetAspectRatio(const Float2& viewRect);
    void SetAspectRatio(const float& aspectRatio);

    void SetNearPlane(const float &nearPlane);
    void SetFarPlane(const float &farPlane);
    void SetPlanes(const float &nearPlane, const float &farPlane);
    void SetPlanes(const Float2 &planes);

    void SetProjectionVariables(const FRad &fovy, const float &AspectRatio, const float &nearPlane, const float &farPlane);

    bool operator==(const Camera& other) const;
    bool operator!=(const Camera& other) const { return !(*this == other); }

  protected:
    bool _dirty = true;

    Float4x4 _projectionMatrix;

    float _aspectRatio;
    FRad _fovy = 1.57079f;// radian representation of 90

    float _nearPlane = 0.1f;
    float _farPlane = 1000.0f;

    bool _IsDirty() const;
    void _Dirty();
    void _Clean();

    void _RecalculateProjectionMatrix();
  };
}// namespace Rendering
}// namespace Application