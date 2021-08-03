#include "ApplicationManagement/Rendering/Headers/SingleCameraManager.h"

using namespace Core;

namespace Application {
namespace Rendering {
  SingleCameraManager::SingleCameraManager(Core::Ptr<RenderManager> manager)
    : CameraManager(manager)
  {}

  void SingleCameraManager::Initialize()
  {
  }

  void SingleCameraManager::Start()
  {
  }

  void SingleCameraManager::Update(Core::Second dt)
  {
  }

  Core::Ptr<Camera> SingleCameraManager::GetCamera() const
  {
    return _camera.get();
  }

  void SingleCameraManager::End()
  {
  }

  void SingleCameraManager::CleanUp()
  {
  }

  Core::Ptr<Camera> SingleCameraManager::AddCamera(Core::UniquePtr<Camera> camera)
  {
#if _DEBUG
    // this assert should be here
    // ASSERT(_camera == nullptr);
#endif
    _camera = move(camera);
    return _camera.get();
  }

  void SingleCameraManager::RemoveCamera(Core::Ptr<Camera> camera)
  {
#if _DEBUG
    ASSERT(_camera.get() == camera);
#endif
    _camera = nullptr;
  }
}// namespace Rendering
}// namespace Application