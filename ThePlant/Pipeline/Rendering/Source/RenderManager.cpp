#include "Pipeline\Rendering\Headers\RenderManager.h"

#include "Core/Logging/Logger.h"

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

  void RenderManager::Initialize(WindowManager &window, Color clearColor)
  {
    _window = &window;

    _initialColor = WHITE;
    _clearColor = clearColor;

    // don't render everything, but set up the default state
    _RenderStart();
    _RenderEnd();
  }

  void RenderManager::Start()
  {
    
  }

  void RenderManager::Render()
  {
    _RenderStart();
    _RenderMiddle();
    _RenderEnd();
  }

  void RenderManager::End()
  {
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

    glEnable(GL_DEPTH_TEST);
    // facing and culling
    // glEnable(GL_CULL_FACE);
    // glFrontFace(GL_CW);
    // glCullFace(GL_BACK);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // turns on wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// turns off wireframe mode

    // SDL_GL_CONTEXT_PROFILE_CORE uses only the newer version, deprecated functions are disabled
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
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

  // testing
  void RenderManager::QueueRender(const Context& context)
  {
    _renderFrame.contexts.emplace_back(context);
  }

  void RenderManager::QueueRender(const SkinnedContext& context)
  {
    _renderFrame.skinnedContexts.emplace_back(context);
  }
  // \testing

  void RenderManager::_RenderStart()
  {
    glClearColor(_clearColor.R, _clearColor.G, _clearColor.B, _clearColor.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // to render lines of triangles in mesh and both front and back
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  void _RenderFrameForCamera(Renderer& renderer, const Float4x4& camera, RenderFrame& renderFrame)
  {
    // NOTE: if we want shaders to get a delta time, we can provide that here by adding a field to the contexts (and providing a delta time)
    for (auto& context : renderFrame.contexts)
    {
      context.mvp = camera * context.mvp;
      renderer.SetShader(context.material.shader);
      renderer.DrawMesh(context);
    }

    for (auto& context : renderFrame.skinnedContexts)
    {
      context.context.mvp = camera * context.context.mvp;
      renderer.SetShader(context.context.material.shader);
      renderer.DrawMesh(context);
    }
    renderer.SetShader(Shader()); // this should be done in the EndFrame call?
  }

  void RenderManager::_RenderMiddle()
  {
    // NOTE: If rendering shadows and the like, we need to DISABLE culling of faces so that they are taken into account for shadows! (I think)
    for (auto& camera : _cameraManager.GetCameras())
    {
      _RenderFrameForCamera(_Renderer, camera, _renderFrame);
    }
    _cameraManager.ClearCameras();
  }

  void RenderManager::_RenderEnd()
  {    
    // delete queued contexts
    _renderFrame.contexts.clear();
    _renderFrame.skinnedContexts.clear();
    
    SDL_GL_SwapWindow(_window->GetWindow());
  }
}// namespace Rendering
}// namespace Application