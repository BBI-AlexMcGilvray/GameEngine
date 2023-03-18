#include "Pipeline\Rendering\Headers\RenderManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Headers/ApplicationManager.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Functionality;

namespace Application {
namespace Rendering {
  RenderManager::RenderManager()
  {}

  CameraManager& RenderManager::GetCameraManager()
  {
    return _cameraManager;
  }

  void RenderManager::Initialize(SDL2Manager& sdlManager, Input::InputManager& inputManager, Core::Threading::Thread&& renderThread, Color clearColor)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    _sdlManager = &sdlManager;
    _inputManager = &inputManager;

    _initialColor = WHITE;
    _clearColor = clearColor;

    // don't render everything, but set up the default state
    // _RenderStart();
    // _RenderEnd();

    _renderThread = std::move(renderThread);
  }

  void RenderManager::Start()
  {
    SCOPED_MEMORY_CATEGORY("Rendering");

    _rendering = true;
    // when multithreaded, we need input to be polled on the same thread as the displays (mostly due to IMGUI, but it makes sense regardless)
  #ifdef MULTITHREADED_RENDERING
    // NOTE: Apparently opengl context is thread-specific. If we are using threaded rendering, then we need to create the opengl context on that thread
    // https://stackoverflow.com/questions/21048927/initializing-opengl-context-in-another-thread-than-the-rendering
    // https://gmane.comp.lib.sdl.narkive.com/WK0DM9bJ/sdl-opengl-context-and-threads
    // Additional note:
    //    - seems sdl uses vsync automatically. either way it seems that the true frame rate is not being displayed by IMGUI due to using GPU calls
    //        - may want our own timers to know 'render thread' frame rate and 'game logic' frame rate
    SDL_GL_MakeCurrent(_sdlManager->GetWindowManager().GetWindow(), nullptr);
    _renderThread.SetTaskAndRun(std::packaged_task<void()>([this]
    {
      SDL_GL_MakeCurrent(_sdlManager->GetWindowManager().GetWindow(), _sdlManager->GetContextManager().GetContext());
      while (_rendering)
      {
        DEBUG_PROFILE_SCOPE("Render Thread"); // this thread is currently locked at 13ms, apparently by sdl's vsync (see above)
        _inputManager->ThreadedUpdate();
        _RenderStart();
        _RenderMiddle();
        _RenderEnd();
      }
    }));
  #endif
  }

  void RenderManager::Render()
  {
    _mainThreadRenderFrame.OrderLayers();

    RenderFrame movingFrame; // this is just immediately moved below, is temp variable only
    _mainThreadRenderFrame.MoveTo(movingFrame);
    _renderFrames.WriteBuffer(std::move(movingFrame));
    _mainThreadRenderFrame.Clear(); // tidy-up whatever wasn't cleaned by the MoveTo

  #ifndef MULTITHREADED_RENDERING
    SDL_GL_MakeCurrent(_sdlManager->GetWindowManager().GetWindow(), _sdlManager->GetContextManager().GetContext());
    _RenderStart();

    _RenderMiddle();

    _RenderEnd();
  #endif
  }

  void RenderManager::End(Core::Threading::ThreadManager& threadManager)
  {
    _rendering = false;
  #ifdef MULTITHREADED_RENDERING
    _renderThread.Complete();
  #endif
    threadManager.ReturnThread(std::move(_renderThread));
  }

  void RenderManager::CleanUp()
  {
  }

  void RenderManager::SetOpenGLAttributes()
  {
    // starting with version 3.2 of OpenGL as it is modern and should be runnable by most video cards
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    // we are going to use double buffering (this only sets a 23bit Z buffer)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);

    // SDL_GL_CONTEXT_PROFILE_CORE uses only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  }

  void RenderManager::SetOpenGLState()
  {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    // facing and culling
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
  }

#if DEBUG
  void RenderManager::VerifyOpenGLAttributes()
  {
    // In the future, the attribute values should be stored in a struct so that they are not floating magic numbers
    // Would also enable reading them from a file and such

    int attributeValue = -100;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &attributeValue);
    ASSERT(attributeValue == 4);

    attributeValue = -100;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &attributeValue);
    ASSERT(attributeValue == 5);

    attributeValue = -100;
    SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &attributeValue);
    ASSERT(attributeValue == 1);
  }
#endif

  void RenderManager::QueueCamera(const RenderCamera& camera)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    _mainThreadRenderFrame.QueueCamera(camera);
  }

  void RenderManager::_RenderStart()
  {
    DEBUG_PROFILE_SCOPE("_RenderStart");

    auto& window = _sdlManager->GetWindowManager();
    glViewport(0, 0, window.Width, window.Height);
    glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A); // probably don't need this anymore since it would be done when we render the main camera
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // same as above
  }

  void RenderManager::_RenderMiddle()
  {
    DEBUG_PROFILE_SCOPE("_RenderMiddle");

    const auto& frameData = _renderFrames.ReadBuffer();

    // NOTE: If rendering shadows and the like, we need to DISABLE culling of faces so that they are taken into account for shadows! (I think)
    frameData.Render(_Renderer, _clearColor);
    _Renderer.SetShader(Shader()); // this should be done in the EndFrame call?

    _renderFrames.ReturnBuffer(frameData);

    _displayManager.Render(_Renderer);
  }

  void RenderManager::_RenderEnd()
  {        
    DEBUG_PROFILE_SCOPE("_RenderEnd");
    
    SDL_GL_SwapWindow(_sdlManager->GetWindowManager().GetWindow());
  }
}// namespace Rendering
}// namespace Application