#include "Pipeline/Rendering/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Rendering/Headers/Camera.h"

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

  // This method calculated the position that from the screen that would exist within the frustrum (since it is doing the opposite (inverted) projection as used for rendering)
  // to get the direction, take the result - camera position
  // NEED(?) to take in a CONST camera/transform -> the 'Get' functions should be const with mutable internal variables
  Float3 ScreenToWorld(Camera &camera, Core::Geometric::Transform& cameraTransform, const Float2 &screenPosition, const Float2 &viewRect)
  {
    // converting from screen (top left [0, 0], bottom right [viewRect]) to world (bottom left [-1, -1], top right [1, 1])
    float worldX = ((screenPosition.X / viewRect.X) * 2.0f) - 1.0f;
    float worldY = 1.0f - ((screenPosition.Y / viewRect.Y) * 2.0f);

    Float4x4 inverseMVP = Math::Inverse(CalculateTransformationMatrix(camera, cameraTransform));

    Float4 worldPosition = inverseMVP * Float4(worldX, worldY, 1.0f, 1.0f);

    return Float3(worldPosition.X, worldPosition.Y, worldPosition.Z) / worldPosition.W;
  }

  Float2 WorldToScreen(Camera &camera, Core::Geometric::Transform& cameraTransform, const Float3 &worldPosition, const Float2 &viewRect)
  {
    Float4x4 MVP = CalculateTransformationMatrix(camera, cameraTransform);
    Float4 transformedPosition = MVP * Float4(worldPosition, 1.0f);

    float screenX = (transformedPosition.X + 1.f) * 0.5f * viewRect.X;
    float screenY = (1.0f - transformedPosition.Y) * 0.5f * viewRect.Y;

    return Float2(screenX, screenY);
  }

  void LookAt(Core::Geometric::Transform& cameraTransform, const Float3& position)
  {
    CORE_THROW("CameraUtils", "This function is broken! we need the rotation component (and position component... or just a snapshot?)");
    auto newDirection = Normalize(position - cameraTransform.GetPosition());

    LookInDirection(cameraTransform, newDirection);
  }

  void LookInDirection(Core::Geometric::Transform& cameraTransform, const Float3& direction)
  {
    CORE_THROW("CameraUtils", "This function is broken! we need the rotation component (... or just a snapshot?)");
    cameraTransform.SetRotation(RotationBetweenVectors(Camera::defaultDirection, direction));
  }
}// namespace Rendering
}// namespace Application