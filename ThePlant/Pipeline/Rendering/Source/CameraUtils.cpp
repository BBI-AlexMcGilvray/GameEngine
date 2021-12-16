#include "Pipeline/Rendering/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "Pipeline/Rendering/Headers/Camera.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;

namespace Application {
namespace Rendering {
  // this is wrong
  Float4x4 CalculatePerspectiveMatrix(const FRad& fovy, const float& aspectRatio, const float& nearPlane, const float& farPlane)
  {
    Float4x4 perspectiveMatrix;

    if (fovy <= 0 || aspectRatio == 0) {
      return perspectiveMatrix;
    }

    // Note: tan(FOV_H/2) / screen_width = tan(FOV_V/2) / screen_height

    float fovYRatio = 1.0f / tan(0.5f * fovy);
    float fovXRatio = fovYRatio / aspectRatio;
    float frustrumDepth = farPlane - nearPlane;

    perspectiveMatrix[0][0] = fovXRatio;
    perspectiveMatrix[1][1] = fovYRatio;
    perspectiveMatrix[2][2] = -1.0f * (farPlane + nearPlane) / frustrumDepth;
    perspectiveMatrix[2][3] = -1.0f;
    perspectiveMatrix[3][2] = -2.0f * (farPlane * nearPlane) / frustrumDepth;
    perspectiveMatrix[3][3] = 0.0f;

    return perspectiveMatrix;
  }

  Float4x4 CalculateTransformationMatrix(Camera& camera, Core::Geometric::Transform& transform)
  {
    return camera.GetProjectionMatrix() * transform.GetInverseTransformationMatrix();
  }

  Float3 ScreenToWorld(const Camera &camera, Core::Geometric::Transform& cameraTransform, const Float2 &screenPosition, const Float2 &viewRect)
  {
    float worldX = screenPosition.X / viewRect.X * 2.0f - 1.0f;
    float worldY = 1.0f - screenPosition.Y / viewRect.Y * 2.0f;

    Float4x4 inverseMVP = cameraTransform.GetTransformationMatrix();

    Float4 worldPosition = inverseMVP * Float4(worldX, worldY, 0.0f, 1.0f);

    return Float3(worldPosition.X, worldPosition.Y, worldPosition.Z) / worldPosition.W;

    // This gives the world coordinate of clicked area. Using the vector of camera->this (given by: this - camera) you
    // can calculate the coordinates that would be found at y = 0.

    // Note: Create a ray class that has a direction and origin and can test for intersection & find the values when an axis (typically y) is 0
  }

  Float2 WorldToScreen(const Camera &camera, Core::Geometric::Transform& cameraTransform, const Float2 &worldPosition, const Float2 &viewRect)
  {
    Float4x4 MVP = cameraTransform.GetTransformationMatrix();
    Float4 transformedPosition = MVP * Float4(worldPosition, 1.0f);

    float screenX = transformedPosition.X / transformedPosition.Z;// scaled down based on distance from 0 x
    float screenY = transformedPosition.Y / transformedPosition.Z;// scaled down based on distance from 0 y

    screenX = (screenX + 1.f) * 0.5f * viewRect.X;
    screenY = (1.0f - screenY) * 0.5f * viewRect.Y;// y goes from top to bottom in screen space

    return Float2(screenX, screenY);
  }

  void LookAt(Core::Geometric::Transform& cameraTransform, const Float3& position)
  {
    auto newDirection = Normalize(position - cameraTransform.GetPosition());

    LookInDirection(cameraTransform, newDirection);
  }

  void LookInDirection(Core::Geometric::Transform& cameraTransform, const Float3& direction)
  {
    cameraTransform.SetRotation(RotationBetweenVectors(Camera::defaultDirection, direction));
  }
}// namespace Rendering
}// namespace Application