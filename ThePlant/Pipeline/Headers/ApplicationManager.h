#pragma once

#include "SDL2Manager.h"

#include "Core/Threading/ThreadManager.h"
#include "Core/Threading/TaskManager.h"

#include "Data/Headers/AssetManager.h"

#include "Pipeline/Animation/Headers/AnimationManager.h"
#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/AssetHandling/EntityFactory.h"
#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/Headers/ServiceManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/StateSystem/Headers/StateManager.h"
#include "Pipeline/Input/Headers/InputManager.h"
#include "Pipeline/Rendering/Headers/MaterialManager.h"
#include "Pipeline/Rendering/Shaders/ShaderManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"
#include "Pipeline/Time/Headers/TimeSystem.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Application::Animation;
using namespace Application::Input;
using namespace Application::Rendering;

using namespace Core::Functionality;

namespace Application {
struct ApplicationManager
{
  Core::Threading::ThreadManager& ThreadManager();
  Core::Threading::TaskManager& TaskManager();
  
  Time::TimeSystem& TimeSystem();

  // could potentially break this up into longterm and shorterm asset managers for consistent behaviour
  Data::AssetManager& AssetManager();
  AssetLoaderFactory& AssetLoaderFactory();
  EntityFactory& EntityFactory();

  // should this be here? Currently exists for IMGUI, but maybe we want a UI manager or something and go through that for debug vs other ui?
  SDL2Manager& SDLManager();

  Animation::AnimationManager &AnimationManager();
  Rendering::RenderManager &RenderManager();
  Rendering::ShaderManager& ShaderManager(); // this should be the material manager, and material manager should hold a shader manager (as materials need shaders)
  Rendering::MaterialManager& MaterialManager();
  Input::InputManager &InputManager();
  StateManager &StateManager();

  ApplicationManager();

  // This should only be called in the Pipeline project
  // Otherwise, the lifetime methods should be called explicitly
  void Run();

  bool quit()
  {
    return _quit;
  }

  bool Initialize();
  void Start();

  void Update(Core::Second dt);
  void Render();

  void End();
  void CleanUp();

private:
  // must be first so that it is destroyed last and created first to track all properly
  // otherwise something could be made with it that persists after this is destroyed, which would error when we try to destroy that object
  Application::ServiceManager _serviceManager;

  Time::TimeSystem _timeSystem;
  // Note: the below are in an order such that they should only _possibly_ know about what is above them (as it would need to be for constructors...)
  Core::Threading::ThreadManager _threadManager;
  Core::Threading::TaskManager _taskManager;

  Data::AssetManager _assetManager;
  Application::AssetLoaderFactory _assetLoader;
  Application::EntityFactory _entityFactory;

  Application::SDL2Manager _sdl;
  Animation::AnimationManager _animationSystem;
  Rendering::ShaderManager _shaderManager;
  Rendering::MaterialManager _materialManager;
  Rendering::RenderManager _renderSystem;
  Input::InputManager _inputSystem;
  Application::StateManager _stateSystem;

  Delegate<> _onQuit;
  bool _quit = false;
};
}// namespace Application