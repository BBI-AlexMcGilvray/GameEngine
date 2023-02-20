#include "Pipeline/Rendering/Headers/CameraManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Pipeline/Rendering/Headers/RenderManager.h"

using namespace Core;

namespace Application {
namespace Rendering {
    void CameraManager::ResetActive()
    {
      VERIFY(_renderCameras.size() == _active.size());
      for (auto& active : _active)
      {
        active = false;
      }
    }

    void CameraManager::UpdateCamera(const Camera& camera, const Core::Math::Int2& renderDimensions, const Core::Math::Float4x4& cameraMatrix)
    {
      SCOPED_MEMORY_CATEGORY("Rendering");

      size_t index = 0;
      for (auto& renderCamera : _renderCameras)
      {
        if (renderCamera.cameraId == camera.GetCameraId())
        {
          renderCamera.renderDimensions = renderDimensions; // needs to be a Resize call for the camera dimensions? (if they do not match)
          renderCamera.renderMatrix = cameraMatrix;
          _active[index] = true;
          return;
        }
        ++index;
      }

      auto& newCamera = _renderCameras.emplace_back(RenderCamera(camera, renderDimensions, cameraMatrix));
      newCamera.InitializeCamera();
      
      _active.emplace_back(true);
    }

    void CameraManager::RemoveInactive()
    {
      for (size_t index = _active.size(); index > 0; --index)
      {
        size_t actualIndex = index - 1;
        if (!_active[actualIndex])
        {
          // this would be the other place we clean up the camera (if not in the destructor)
          (_renderCameras.begin() + actualIndex)->CleanUpCamera();
          _renderCameras.erase(_renderCameras.begin() + actualIndex);
        }
      }

      _active.resize(_renderCameras.size());
    }

    const std::vector<RenderCamera>& CameraManager::GetCameras() const
    {
      return _renderCameras;
    }

    const RenderCamera& CameraManager::GetCamera(const Core::instanceId<Camera>& cameraId)
    {
      for (const auto& camera : _renderCameras)
      {
        if (camera.cameraId == cameraId)
        {
          return camera;
        }
      }

      CORE_THROW("CameraManager", "Requested camera does not exist!");
    }
}// namespace Rendering
}// namespace Application