#pragma once

#include "SDL2Manager.h"

#include "Data/Headers/AssetManager.h"

#include "Pipeline/Animation/Headers/AnimationManager.h"
#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/Headers/ServiceManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/StateSystem/Headers/StateManager.h"
#include "Pipeline/Input/Headers/InputManager.h"
#include "Pipeline/Rendering/Shaders/ShaderManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"
#include "Pipeline/Time/Headers/TimeManager.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Application::Animation;
using namespace Application::Input;
using namespace Application::Rendering;
using namespace Application::Time;

using namespace Core::Functionality;

namespace Application {
struct ApplicationManager
{
  static Core::Ptr<ApplicationManager> Application();

  // should this be here? Currently exists for IMGUI, but maybe we want a UI manager or something and go through that for debug vs other ui?
  static SDL2Manager& AppSDLManager();

  static Animation::AnimationManager &AppAnimationManager();
  // static Collision::CollisionManager &AppCollisionManager();
  static Rendering::RenderManager &AppRenderManager();
  static Rendering::ShaderManager& AppShaderManager();
  static Input::InputManager &AppInputManager();
  static StateManager &AppStateManager();
  // could potentially break this up into longterm and shorterm asset managers for consistent behaviour
  static Data::AssetManager& AppAssetManager();
  // static ECS& AppECS();

private:
  // to make sure that constructor can't be called except through static Application() method to get instance
  struct ConstructorTag
  {
    ConstructorTag() = default;
  };

public:
  ApplicationManager(ConstructorTag tag);

  // This should only be called in the Pipeline project
  // Otherwise, the lifetime methods should be called explicitly
  void Run();

  bool quit()
  {
    return _quit;
  }

  bool Initialize();
  void Start();

  // update things that do not need time
  // should only be called once a frame
  void Update();
  // update things that do need time
  // can be called multiple times per frame (but total dt should not pass the frame dt)
  void Update(Core::Second dt);

  void End();
  void CleanUp();

private:
  // Note: the below are in an order such that they should only _possibly_ know about what is above them (as it would need to be for constructors...)
  SDL2Manager _sdl;
  // ECS _ecsSystem;
  Data::AssetManager _assetManager;
  // Collision::CollisionManager _collisionManager;
  Animation::AnimationManager _animationSystem;
  Rendering::RenderManager _renderSystem;
  Rendering::ShaderManager _shaderManager;
  Input::InputManager _inputSystem;
  ServiceManager _serviceManager;
  StateManager _stateSystem;

  Delegate<> _onQuit;
  bool _quit = false;

  static Core::UniquePtr<ApplicationManager> _instance;
};
}// namespace Application