#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

using namespace Core;

namespace Application {
namespace Rendering {
    void CameraManager::AddCamera(const Core::Math::Float4x4& camera)
    {
      _cameras.emplace_back(camera);
    }

    const std::vector<Core::Math::Float4x4>& CameraManager::GetCameras() const
    {
      return _cameras;
    }

    void CameraManager::ClearCameras()
    {
      _cameras.clear();
    }
}// namespace Rendering
}// namespace Application