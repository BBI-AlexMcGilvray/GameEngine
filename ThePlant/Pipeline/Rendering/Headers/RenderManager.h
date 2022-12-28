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
#include "Pipeline/Rendering/RenderFrame.h"
#include "Pipeline/Rendering/Renderer.h"

// testing
#include "Pipeline/Rendering/Shaders/Shader.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLFrameBuffer.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLTexture.h"
#include "Pipeline/Rendering/OpenGL/Headers/GLRenderBuffer.h"
// \testing

namespace Application {
namespace Rendering {
  struct RenderManager
  {
    RenderManager();

    CameraManager& GetCameraManager();
    UI::IMGUI::Manager& GetUIManager();

    void Initialize(SDL2Manager& sdlManager, Core::Threading::Thread&& renderThread, Core::Math::Color clearColor = Core::Math::Color(1.0f, 0.5f, 0.5f, 1.0f));
    void Start();

    // for this and the RemoveLayer function, will this support dynamically adding/removing more during runtime? (i.e. not just initialization)
    template <typename LAYER>
    LAYER& AddLayer()
    {
      return _mainThreadRenderFrame.AddLayer<LAYER>();
    }

    template <typename LAYER>
    void RemoveLayer()
    {
      _mainThreadRenderFrame.RemoveLayer<LAYER>();        
    }

    void QueueCamera(const Core::Math::Float4x4& camera);

    template <typename LAYER>
    void QueueRender(const Context& context)
    {
      SCOPED_MEMORY_CATEGORY("Rendering");
      _mainThreadRenderFrame.QueueRender<LAYER>(context);
    }

    template <typename LAYER>
    void QueueRender(const SkinnedContext& context)
    {
      SCOPED_MEMORY_CATEGORY("Rendering");
      _mainThreadRenderFrame.QueueRender<LAYER>(context);
    }

    void Render();

    void End(Core::Threading::ThreadManager& threadManager);
    void CleanUp();

    // must be called BEFORE openGL context is created
    void SetOpenGLAttributes();
#if DEBUG
    void VerifyOpenGLAttributes();
#endif
    // must be called AFTER openGL context is created
    void SetOpenGLState();

  private:
    Core::Math::Color _initialColor;

    Core::Math::Color _clearColor;
    Core::Ptr<SDL2Manager> _sdlManager;

    CameraManager _cameraManager;
    std::unique_ptr<UI::IMGUI::Manager> _ui;

    void _RenderStart();
    void _RenderMiddle();
    void _RenderEnd();
  
    RenderFrame _mainThreadRenderFrame; // this is the frame we update before we pass it in to the triple buffer

    Core::Threading::TripleBuffer<RenderFrame> _renderFrames;
    std::atomic<bool> _rendering;
    Core::Threading::Thread _renderThread;

    Renderer _Renderer;

    // testing
    GLFrameBuffer _frameBuffer;
    GLTexture _frameBufferTexture;
    GLRenderBuffer _frameBufferStencilAndDepth;
    Shader _frameBufferShader;
    Mesh _frameBufferMesh;

    void _InitialiseFrameBufferTest();
    void _FrameBufferTestBegin();
    void _FrameBufferTestEnd();
    void _CleanUpFrameBufferTest();
    // \testing
  };
}// namespace Rendering
}// namespace Application
