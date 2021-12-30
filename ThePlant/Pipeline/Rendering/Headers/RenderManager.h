#pragma once

#include <map>

#include "Pipeline\Headers\GLContextManager.h"
#include "Pipeline\Headers\WindowManager.h"

#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/MaterialManager.h"
#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Renderer_NEW.h"

#include "Core/Functionality/Headers/Subscription.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"

namespace Application {
struct State;

namespace Rendering {
  struct RenderManager
  {
    // should subscribe to StateManager::StateChanged to change active state automatically
    RenderManager();

    CameraManager& GetCameraManager();

    void Initialize(WindowManager &window, Core::Math::Color clearColor = Core::Math::Color(1.0f, 0.5f, 0.5f, 1.0f));
    void Start();

    void QueueRender(const Context& context);
    void QueueRender(const SkinnedContext& context);

    void Render();

    void End();
    void CleanUp();

    void SetOpenGLAttributes();
#if DEBUG
    void VerifyOpenGLAttributes();
#endif

  private:
    Core::Math::Color _initialColor;

    Core::Math::Color _clearColor;
    Core::Ptr<WindowManager> _window;

    CameraManager _cameraManager;

    void _RenderStart();
    void _RenderMiddle();
    void _RenderEnd();
  
    // testing
    RenderFrame _renderFrame; // in the future, this can be a tripple buffer guarded by a mutex and be what is used for threading purposes
    Renderer_NEW _renderer_NEW;
    // \testing
  };
}// namespace Rendering
}// namespace Application
