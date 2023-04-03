#pragma once

#include <vector>

#include "Pipeline/Rendering/MeshManager.h"
#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/Headers/RenderCamera.h"
#include "Pipeline/Rendering/Headers/RenderTarget.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/IdTypes/InstanceId.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  // this is how we should manage having different camera behavious (ex: simple camera manager that just maintains a single camera, or more complex behaviour like cinemachine)
  struct CameraManager
  {
    CameraManager(MeshManager& meshManager);

    void ResetActive();
    void UpdateCamera(const Camera& camera, const Core::Math::Int2& renderDimensions, const Core::Math::Float4x4& cameraMatrix);
    void RemoveInactive();

    std::vector<RenderCamera> GetCameraCopies();
    const RenderCamera& GetCamera(const Core::instanceId<Camera>& cameraId);

    const RenderTarget& GetValidRenderTarget(const RenderDataHandle& handle);

  protected:
    MeshManager& _meshManager;

    std::vector<bool> _active; // index-matched with the below, false -> camera not updated this frame, remove it
    std::vector<RenderCamera> _renderCameras;
    std::vector<RenderTarget> _renderCameraTargets;

    RenderCamera _GetCameraCopy(const RenderCamera& camera);
    RenderTarget& _GetRenderTarget(const RenderDataHandle& handle);
  };
}// namespace Rendering
}// namespace Application
