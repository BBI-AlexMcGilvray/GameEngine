#pragma once

#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core::Math;

namespace Application {
namespace Rendering {
  struct Camera;

  Float4x4 CalculatePerspectiveMatrix(FRad fov, float aspectRatio, float nearPlane, float farPlane);

  Float3 ScreenToWorld(const Camera &camera, const Float2 &screenPosition, const Float2 &viewRect);
  Float2 WorldToScreen(const Camera &camera, const Float2 &worldPosition, const Float2 &viewRect);
}// namespace Rendering
}// namespace Application