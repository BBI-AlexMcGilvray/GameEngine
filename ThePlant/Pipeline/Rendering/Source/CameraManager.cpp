#include "Pipeline/Rendering/Headers/CameraManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Pipeline/Rendering/Headers/RenderManager.h"
#include "Pipeline/Rendering/Headers/RenderDataCreator.h"

using namespace Core;

namespace Application {
namespace Rendering {
    CameraManager::CameraManager(MeshManager& meshManager)
    : _meshManager(meshManager)
    {}

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
          // renderCamera.renderDimensions = renderDimensions; // if render dimensions don't match, we'd need to resize the render texture, not the camera
          renderCamera.renderMatrix = cameraMatrix;
          _active[index] = true;
          return;
        }
        ++index;
      }

      auto& newRenderTarget = _renderCameraTargets.emplace_back(RenderTarget(renderDimensions));
      auto& newCamera = _renderCameras.emplace_back(RenderCamera(camera.GetCameraId(), cameraMatrix, newRenderTarget.GetHandle()));
      
      _active.emplace_back(true);
    }

    void CameraManager::RemoveInactive()
    {
      for (size_t index = _active.size(); index > 0; --index)
      {
        size_t actualIndex = index - 1;
        if (!_active[actualIndex])
        {
          _renderCameras.erase(_renderCameras.begin() + actualIndex);
        }
      }

      // this and the above should be split into private functions
      for (size_t index = _renderCameraTargets.size(); index > 0; --index)
      {
        size_t actualIndex = index - 1;
        if (!_renderCameraTargets[actualIndex].IsReferenced())
        {
          RenderDataCreator::DestroyRenderData(_renderCameraTargets[actualIndex], &DeleteRenderTarget);
          _renderCameraTargets.erase(_renderCameraTargets.begin() + actualIndex);
        }
      }

      _active.resize(_renderCameras.size());
    }

    std::vector<RenderCamera> CameraManager::GetCameraCopies()
    {
      std::vector<RenderCamera> copies;
      copies.reserve(_renderCameras.size());

      for (const auto& camera : _renderCameras)
      {
        copies.emplace_back(std::move(_GetCameraCopy(camera)));
      }

      return copies;
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

    const RenderTarget& CameraManager::GetValidRenderTarget(const RenderDataHandle& handle)
    {
      for (auto& target : _renderCameraTargets)
      {
        if (target.IsHeldBy(handle))
        {
          if (!target.IsValid())
          {
            RenderDataCreator::InitializeRenderData(target, &InitializeRenderTarget, _meshManager);
          }
          return target;
        }
      }

      CORE_THROW("CameraManager", "Requested render target does not exist!");
    }

    RenderCamera CameraManager::_GetCameraCopy(const RenderCamera& camera)
    {
      RenderTarget& cameraTarget = _GetRenderTarget(camera.renderTargetHandle);
      return RenderCamera(camera.cameraId, camera.renderMatrix, cameraTarget.GetHandle());
    }

    RenderTarget& CameraManager::_GetRenderTarget(const RenderDataHandle& handle)
    {
      for (auto& target : _renderCameraTargets)
      {
        if (target.IsHeldBy(handle))
        {
          return target;
        }
      }

      CORE_THROW("CameraManager", "Requested render target does not exist!");
    }
}// namespace Rendering
}// namespace Application