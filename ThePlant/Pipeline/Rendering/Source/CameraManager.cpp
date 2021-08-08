#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

using namespace Core;

namespace Application {
namespace Rendering {
  CameraManager::CameraManager(Core::Ptr<RenderManager> manager)
    : _manager(manager)
  {}
}// namespace Rendering
}// namespace Application