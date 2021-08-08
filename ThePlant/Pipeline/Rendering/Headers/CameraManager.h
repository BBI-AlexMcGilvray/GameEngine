#pragma once

#include "Pipeline/Rendering/Headers/Camera.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Headers/MapDefs.h"

namespace Application {
namespace Rendering {
  struct RenderManager;

  // this is how we should manage having different camera behavious (ex: simple camera manager that just maintains a single camera, or more complex behaviour like cinemachine)
  struct CameraManager
  {
    CameraManager(Core::Ptr<RenderManager> manager);

    virtual void Initialize() = 0;
    virtual void Start() = 0;

    virtual void Update(Core::Second dt) = 0;
    virtual Core::Ptr<Camera> GetCamera() const = 0;

    virtual void End() = 0;
    virtual void CleanUp() = 0;

    // This should return a RanderObjectPtr that holds a unique ptr to the render object and will remove the object from
    // the manager once deleted
    template<typename T, typename... Ts>
    Core::Ptr<T> AddCamera(Ts &&...args)
    {
      Core::UniquePtr<Camera> newCamera = Core::MakeUnique<T>(Forward<Ts>(args)...);

      return static_cast<Ptr<T>>(AddCamera(move(newCamera)));
    }

    virtual Core::Ptr<Camera> AddCamera(Core::UniquePtr<Camera> camera) = 0;
    virtual void RemoveCamera(Core::Ptr<Camera> camera) = 0;

  protected:
    // ideally we find a way to make this not a raw pointer, but it should be fine for now since this object
    // will only exist within a render manager, so lifetime is not a concern
    // ~ Could just be an element of this class and not a pointer at all?
    Core::Ptr<RenderManager> _manager;
  };
}// namespace Rendering
}// namespace Application
