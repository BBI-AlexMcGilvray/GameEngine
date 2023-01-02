#pragma once

#include "Core/IdTypes/InstanceId.h"

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

    Camera(const Camera&) = default; // delete? or we need to set a new cameraId
    Camera(Camera&&) = default;

    Camera& operator=(const Camera&) = default; // delete? or we need to set a new cameraId
    Camera& operator=(Camera&&) = default;

    Core::instanceId<Camera> GetCameraId() const;

    Float4x4 GetProjectionMatrix();

    FRad& GetFOVY();
    FRad GetFOVY() const;
    void SetFOVY(const FRad& fovy);

    float& GetAspectRatio();
    float GetAspectRatio() const;
    void SetAspectRatio(const float& width, const float& height);
    void SetAspectRatio(const Float2& viewRect);
    void SetAspectRatio(const float& aspectRatio);

    float& GetNearPlane();
    float GetNearPlane() const;
    void SetNearPlane(const float &nearPlane);
    float& GetFarPlane();
    float GetFarPlane() const;
    void SetFarPlane(const float &farPlane);
    // near = x, far = y
    Float2 GetPlanes() const;
    void SetPlanes(const float &nearPlane, const float &farPlane);
    void SetPlanes(const Float2 &planes);

    void SetProjectionVariables(const FRad &fovy, const float &AspectRatio, const float &nearPlane, const float &farPlane);

    bool operator==(const Camera& other) const;
    bool operator!=(const Camera& other) const { return !(*this == other); }

  protected:
    Core::instanceId<Camera> _cameraId;
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