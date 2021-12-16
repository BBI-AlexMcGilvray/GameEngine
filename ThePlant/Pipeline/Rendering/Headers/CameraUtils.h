#pragma once

#include "Core/Math/Headers/Matrix4x4.h"
#include "Core/Geometric/Headers/Transform.h"

using namespace Core::Math;

namespace Application {
namespace Rendering {
  struct Camera;

  Float4x4 CalculatePerspectiveMatrix(const FRad& fovy, const float& aspectRatio, const float& nearPlane, const float& farPlane);
  Float4x4 CalculateTransformationMatrix(Camera& camera, Core::Geometric::Transform& transform);

  // viewRect is the size of the screen in pixels
  Float3 ScreenToWorld(const Camera &camera, Core::Geometric::Transform& cameraTransform, const Float2 &screenPosition, const Float2 &viewRect);
  Float2 WorldToScreen(const Camera &camera, Core::Geometric::Transform& cameraTransform, const Float2 &worldPosition, const Float2 &viewRect);

  void LookAt(Core::Geometric::Transform& cameraTransform, const Float3& position);
  void LookInDirection(Core::Geometric::Transform& cameraTransform, const Float3& direction);
}// namespace Rendering
}// namespace Application