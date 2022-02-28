#pragma once

#include <atomic>
#include <map>

#include "Core/Functionality/Headers/Subscription.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Threading/SafeTypes/TripleBuffer.h"
#include "Core/Threading/Thread.h"

#include "Pipeline\Headers\GLContextManager.h"
#include "Pipeline/Headers/SDL2Manager.h"
#include "Pipeline\Headers\WindowManager.h"

#include "Pipeline/UI/IMGUI/Manager.h"

#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/MaterialManager.h"
#include "Pipeline/Rendering/Headers/Camera.h"
#include "Pipeline/Rendering/RenderContext.h"
#include "Pipeline/Rendering/Renderer.h"

namespace Application {
namespace Rendering {
  struct RenderManager
  {
    RenderManager();

    CameraManager& GetCameraManager();

    void Initialize(SDL2Manager& sdlManager, Core::Threading::Thread&& renderThread, Core::Math::Color clearColor = Core::Math::Color(1.0f, 0.5f, 0.5f, 1.0f));
    void Start();

    void QueueCamera(const Core::Math::Float4x4& camera);
    void QueueRender(const Context& context);
    void QueueRender(const SkinnedContext& context);

    void Render();

    void End(Core::Threading::ThreadManager& threadManager);
    void CleanUp();

    void SetOpenGLAttributes();
#if DEBUG
    void VerifyOpenGLAttributes();
#endif

  private:
    Core::Math::Color _initialColor;

    Core::Math::Color _clearColor;
    Core::Ptr<SDL2Manager> _sdlManager;

    CameraManager _cameraManager;
    std::unique_ptr<UI::IMGUI::Manager> _ui;

    void _RenderStart();
    void _RenderMiddle();
    void _RenderEnd();
  
    RenderFrame _mainThreadRenderFrame; // in the future, this can be a tripple buffer guarded by a mutex and be what is used for threading purposes

    Core::Threading::TripleBuffer<RenderFrame> _renderFrames;
    std::atomic<bool> _rendering;
    Core::Threading::Thread _renderThread;

    Renderer _Renderer;
  };
}// namespace Rendering
}// namespace Application
