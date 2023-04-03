#include "Pipeline\Rendering\Headers\RenderManager.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Headers/ApplicationManager.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Functionality;

namespace Application {
namespace Rendering {
  RenderManager::RenderManager(ShaderManager& shaderManager, MeshManager& meshManager)
  : _cameraManager(meshManager)
  , _Renderer(shaderManager, _cameraManager, meshManager)
  {}

  CameraManager& RenderManager::GetCameraManager()
  {
    return _cameraManager;
  }

  void RenderManager::Initialize(SDL2Manager& sdlManager, Input::InputManager& inputManager, Color clearColor)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    _sdlManager = &sdlManager;
    _inputManager = &inputManager;

    _initialColor = WHITE;
    _clearColor = clearColor;

    // don't render everything, but set up the default state
    // _RenderStart();
    // _RenderEnd();
  }

  void RenderManager::Start()
  {}

#ifdef MULTITHREADED_RENDERING
  void RenderManager::ThreadedRender()
  {
    _RenderStart();
    _RenderMiddle();
    _RenderEnd(); 
  }
#endif

  void RenderManager::Render()
  {
    _mainThreadRenderFrame.OrderLayers();

    RenderFrame movingFrame; // this is just immediately moved below, is temp variable only
    _mainThreadRenderFrame.MoveTo(movingFrame);
    _renderFrames.WriteBuffer(std::move(movingFrame));
    _mainThreadRenderFrame.Clear(); // tidy-up whatever wasn't cleaned by the MoveTo

  #ifndef MULTITHREADED_RENDERING
    _RenderStart();
    _RenderMiddle();
    _RenderEnd();
  #endif
  }

  void RenderManager::End()
  {}

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

  void RenderManager::QueueCamera(RenderCamera&& camera)
  {
    SCOPED_MEMORY_CATEGORY("Rendering");
    _mainThreadRenderFrame.QueueCamera(std::move(camera));
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
    _Renderer.ClearShader(); // this should be done in the EndFrame call?

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