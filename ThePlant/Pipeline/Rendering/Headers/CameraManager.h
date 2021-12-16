#pragma once

#include <vector>

#include "Pipeline/Rendering/Headers/Camera.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  // this is how we should manage having different camera behavious (ex: simple camera manager that just maintains a single camera, or more complex behaviour like cinemachine)
  struct CameraManager
  {
    CameraManager() = default;

    void AddCamera(const Core::Math::Float4x4& camera);

    const std::vector<Core::Math::Float4x4>& GetCameras() const;

    void ClearCameras();

  protected:
    std::vector<Core::Math::Float4x4> _cameras; // the camera matrices
  };
}// namespace Rendering
}// namespace Application
