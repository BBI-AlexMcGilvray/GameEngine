#pragma once

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"

#include "Core/Math/Headers/Quaternion.h"

#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Geometric/Headers/HierarchyTransform.h"

using namespace Core;
using namespace Core::Math;

namespace Application {
namespace Rendering {
  // anything needed for camera. should create specifications for perspective and orthographic
  struct Camera
  {
    static const Float3 DefaultDirection;

    Camera(const float &aspectRatio, Geometric::HierarchyTransform &transform, const Float3 &direction = DefaultDirection);

    Geometric::HierarchyTransform &GetCameraTransform();

    Float4x4 GetTransformationMatrix() const;

    void LookAt(Float3 position);

    void SetFOVY(FRad fovy);

    void SetAspectRatio(float width, float height);
    void SetAspectRatio(Float2 viewRect);
    void SetAspectRatio(float aspectRatio);

    void SetNearPlane(const float &nearPlane);
    void SetFarPlane(const float &farPlane);
    void SetPlanes(const float &nearPlane, const float &farPlane);
    void SetPlanes(const Float2 &planes);

    void SetProjectionVariables(const FRad &fovy, const float &AspectRatio, const float &nearPlane, const float &farPlane);

  protected:
    Geometric::HierarchyTransform& CameraTransform;

    Float3 Direction;// direction the camera is looking

    Float4x4 ProjectionMatrix;

    float AspectRatio;
    FRad FOVY = 1.57079f;// radian representation of 90

    float NearPlane = 0.1f;
    float FarPlane = 1000.0f;

    void RecalculateProjectionMatrix();
  };
}// namespace Rendering
}// namespace Application