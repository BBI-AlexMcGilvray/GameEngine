#include "Pipeline/Rendering/Headers/Camera.h"

#include "Pipeline/Rendering/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application {
namespace Rendering {
  Camera::Camera(const float &aspectRatio /* = 0.5f */)
  {
    _cameraId = Core::GetInstanceId<Camera>();
    SetProjectionVariables(_fovy, aspectRatio, _nearPlane, _farPlane);
  }

  Core::instanceId<Camera> Camera::GetCameraId() const
  {
    return _cameraId;
  }

  Float4x4 Camera::GetProjectionMatrix()
  {
    if (_IsDirty())
    {
      _RecalculateProjectionMatrix();
    }

    return _projectionMatrix;
  }

  FRad& Camera::GetFOVY()
  {
    return _fovy;
  }

  FRad Camera::GetFOVY() const
  {
    return _fovy;
  }

  void Camera::SetFOVY(const FRad& fovy)
  {
    _fovy = fovy;

    _Dirty();
  }

  float& Camera::GetAspectRatio()
  {
    return _aspectRatio;
  }
  
  float Camera::GetAspectRatio() const
  {
    return _aspectRatio;
  }

  void Camera::SetAspectRatio(const float& width, const float& height)
  {
    SetAspectRatio(Float2(width, height));
  }

  void Camera::SetAspectRatio(const Float2& viewRect)
  {
    SetAspectRatio(viewRect.X / viewRect.Y);
  }

  void Camera::SetAspectRatio(const float& aspectRatio)
  {
    _aspectRatio = aspectRatio;

    _Dirty();
  }

  float& Camera::GetNearPlane()
  {
    return _nearPlane;
  }

  float Camera::GetNearPlane() const
  {
    return _nearPlane;
  }

  void Camera::SetNearPlane(const float &nearPlane)
  {
    SetPlanes(nearPlane, _farPlane);
  }

  float& Camera::GetFarPlane()
  {
    return _farPlane;
  }

  float Camera::GetFarPlane() const
  {
    return _farPlane;
  }

  void Camera::SetFarPlane(const float &farPlane)
  {
    SetPlanes(_nearPlane, farPlane);
  }

  Float2 Camera::GetPlanes() const
  {
    return { _nearPlane, _farPlane };
  }

  void Camera::SetPlanes(const float &nearPlane, const float &farPlane)
  {
    SetPlanes(Float2(nearPlane, farPlane));
  }

  void Camera::SetPlanes(const Float2 &planes)
  {
    _nearPlane = planes.X;
    _farPlane = planes.Y;

    _Dirty();
  }

  void Camera::SetProjectionVariables(const FRad &fovy, const float &aspectRatio, const float &nearPlane, const float &farPlane)
  {
    _fovy = fovy;

    _aspectRatio = aspectRatio;

    _nearPlane = nearPlane;
    _farPlane = farPlane;

    _Dirty();
  }

  bool Camera::operator==(const Camera& other) const
  {
    return (_fovy == other._fovy
          && _aspectRatio == other._aspectRatio
          && _nearPlane == other._nearPlane
          && _farPlane == other._farPlane);
  }

  bool Camera::_IsDirty() const { return _dirty; }
  void Camera::_Dirty() { _dirty = true; }
  void Camera::_Clean() { _dirty = false; }
  
  void Camera::_RecalculateProjectionMatrix()
  {
    _projectionMatrix = CalculatePerspectiveMatrix(_fovy, _aspectRatio, _nearPlane, _farPlane);
    _Clean();
  }
}// namespace Rendering
}// namespace Application