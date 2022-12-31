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

    void CameraManager::UpdateCamera(const Camera& camera, const Core::Math::Float4x4& cameraMatrix)
    {
      SCOPED_MEMORY_CATEGORY("Rendering");
      
      size_t index = 0;
      for (auto& renderCamera : _renderCameras)
      {
        if (renderCamera.cameraId == camera.GetCameraId())
        {
          renderCamera.renderMatrix = cameraMatrix;
          _active[index] = true;
          return;
        }
        ++index;
      }

      _renderCameras.emplace_back(RenderCamera(camera, cameraMatrix));
      _active.emplace_back(true);
    }

    void CameraManager::RemoveInactive()
    {
      for (size_t index = 0; index < _active.size(); ++index)
      {
        if (!_active[index])
        {
          _renderCameras.erase(_renderCameras.begin() + index);
        }
      }

      _active.resize(_renderCameras.size());
    }

    const std::vector<RenderCamera>& CameraManager::GetCameras() const
    {
      return _renderCameras;
    }
}// namespace Rendering
}// namespace Application