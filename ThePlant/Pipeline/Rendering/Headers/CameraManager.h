#pragma once

#include <vector>

#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/Headers/RenderCamera.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  // this is how we should manage having different camera behavious (ex: simple camera manager that just maintains a single camera, or more complex behaviour like cinemachine)
  struct CameraManager
  {
    CameraManager() = default;

    void ResetActive();
    void UpdateCamera(const Camera& camera, const Core::Math::Float4x4& cameraMatrix);
    void RemoveInactive();

    const std::vector<RenderCamera>& GetCameras() const;

  protected:
    std::vector<bool> _active; // index-matched with the below, false -> camera not updated this frame, remove it
    std::vector<RenderCamera> _renderCameras;
  };
}// namespace Rendering
}// namespace Application
