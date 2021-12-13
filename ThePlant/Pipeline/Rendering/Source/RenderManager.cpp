#include "Pipeline\Rendering\Headers\RenderManager.h"

#include "Core/Logging/Logger.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Functionality;

namespace Application {
namespace Rendering {
  RenderManager::RenderManager()
  {}

  void RenderManager::Initialize(WindowManager &window, Color clearColor)
  {
    ObjectShaderManager.Initialize();

    Window = &window;

    InitialColor = WHITE;
    ClearColor = clearColor;

    // don't render everything, but set up the default state
    RenderStart();
    RenderEnd();
  }

  void RenderManager::Start()
  {
    // this is getting called correctly, but the problem is the camera is not initialized AFTER this - incorrectly
    RenderCamera = nullptr;
  }

  void RenderManager::AttachRenderObjectManager(Ptr<State> state, Ptr<RenderObjectManager> objectManager)
  {
    ObjectManagers.insert(std::make_pair(std::move(state), std::move(objectManager)));
  }

  void RenderManager::DettachRenderObjectManager(Ptr<State> state)
  {
    ObjectManagers.erase(state);
  }

  void RenderManager::AttachMaterialManager(Core::Ptr<State> state, Core::Ptr<MaterialManager> materialManager)
  {
    MaterialManagers.insert(std::make_pair(std::move(state), std::move(materialManager)));
  }

  void RenderManager::DettachMaterialManager(Core::Ptr<State> state)
  {
    MaterialManagers.erase(state);
  }

  void RenderManager::AttachCameraManager(Core::Ptr<State> state, Core::Ptr<CameraManager> cameraManager)
  {
    CameraManagers.insert(std::make_pair(std::move(state), std::move(cameraManager)));
  }

  void RenderManager::DettachCameraManager(Core::Ptr<State> state)
  {
    CameraManagers.erase(state);
  }

  Core::Ptr<State> RenderManager::GetActiveState()
  {
    return ActiveState;
  }

  void RenderManager::SetActiveState(Ptr<State> state)
  {
    if (state == nullptr) {
      DEBUG_LOG("RenderManager", "Active state can't be null!");
      return;
    }

    if (ActiveState == state) {
      return;
    }

    ActiveState = state;
  }

  void RenderManager::DeactivateState(Ptr<State> state)
  {
    if (ActiveState == state) {
      ActiveState = nullptr;
    }
  }

  Ptr<RenderObjectManager> RenderManager::GetObjectManagerForState(Ptr<State> state)
  {
    return ObjectManagers[state];
  }

  Core::Ptr<MaterialManager> RenderManager::GetMaterialManagerForState(Core::Ptr<State> state)
  {
    return MaterialManagers[state];
  }

  Core::Ptr<CameraManager> RenderManager::GetCameraManagerForState(Core::Ptr<State> state)
  {
    return CameraManagers[state];
  }

  void RenderManager::Update(Second dt)
  {
    // update render object manager
    if (ActiveState != nullptr) {
      CameraManagers[ActiveState]->Update(dt);
      MaterialManagers[ActiveState]->Update(dt);
      ObjectManagers[ActiveState]->Update(dt);

      RenderCamera = CameraManagers[ActiveState]->GetCamera();
    }
#if _DEBUG// check in debug to find errors, no errors should exist in live
    if (RenderCamera == nullptr) {
      DEBUG_ERROR("RenderManager", "NO RENDER CAMERA IN RENDER MANAGER!");
      return;
    }
#endif
    Render();
  }

  void RenderManager::Render()
  {
    RenderStart();
    RenderMiddle();
    RenderEnd();
  }

  void RenderManager::End()
  {
  }

  void RenderManager::CleanUp()
  {
    ObjectShaderManager.CleanUp();
  }

  void RenderManager::SetOpenGLAttributes()
  {
    // starting with version 3.2 of OpenGL as it is modern and should be runnable by most video cards
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);

    // we are going to use double buffering (this only sets a 23bit Z buffer)
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // facing and culling
    glEnable(GL_CULL_FACE | GL_DEPTH_TEST);
    glFrontFace(GL_CW);
    glCullFace(GL_BACK);

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

  Ptr<const Camera> RenderManager::GetCamera() const
  {
    return RenderCamera;
  }

  // testing
  void RenderManager::QueueRender(const Context& context)
  {
    _contexts.emplace_back(context);
  }

  void RenderManager::QueueRender(const SkinnedContext& context)
  {
    _skinnedContexts.emplace_back(context);
  }
  // \testing

  void RenderManager::RenderStart()
  {
    glClearColor(ClearColor.R, ClearColor.G, ClearColor.B, ClearColor.A);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // to render lines of triangles in mesh and both front and back
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  void RenderManager::RenderMiddle()
  {
    // NOTE: If rendering shadows and the like, we need to DISABLE culling of faces so that they are taken into account for shadows! (I think)

    // render manager render call
    auto initialMVP = RenderCamera->GetTransformationMatrix();
    if (ActiveState != nullptr) {
      // MaterialManagers probably does not need a render call
      //MaterialManagers[ActiveState]->Render(initialMVP, InitialColor);
      ObjectManagers[ActiveState]->Render(initialMVP, InitialColor);
    }

    // testing
    // in the future, we should have an array of cameras (?) that we populate based on the CameraComponents (they determine matrix based on their matching WorldTransformComponent)
    // then we iterate over each context for each camera
    // this is also where we would do culling (unless that is another system?)
    _renderer_NEW.StartFrame();
    for (auto& context : _contexts)
    {
      context.mvp = RenderCamera->GetTransformationMatrix() * context.mvp;
      _renderer_NEW.SetShader(context.material.shader);
      _renderer_NEW.DrawMesh(context);
    }

    for (auto& context : _skinnedContexts)
    {
      context.context.mvp = RenderCamera->GetTransformationMatrix() * context.context.mvp;
      _renderer_NEW.SetShader(context.context.material.shader);
      _renderer_NEW.DrawMesh(context);
    }
    _renderer_NEW.SetShader(Shader_NEW()); // this should be done in the EndFrame call?
    _renderer_NEW.EndFrame();
    // \testing
  }

  void RenderManager::RenderEnd()
  {    
    // delete queued contexts
    _contexts.clear();
    _skinnedContexts.clear();
    
    SDL_GL_SwapWindow(Window->GetWindow());
  }
}// namespace Rendering
}// namespace Application