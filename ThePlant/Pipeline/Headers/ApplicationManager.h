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
  // should this be here? Currently exists for IMGUI, but maybe we want a UI manager or something and go through that for debug vs other ui?
  SDL2Manager& SDLManager();

  Animation::AnimationManager &AnimationManager();
  Rendering::RenderManager &RenderManager();
  Rendering::ShaderManager& ShaderManager(); // this should be the material manager, and material manager should hold a shader manager (as materials need shaders)
  Input::InputManager &InputManager();
  StateManager &StateManager();
  // could potentially break this up into longterm and shorterm asset managers for consistent behaviour
  Data::AssetManager& AssetManager();

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
  // Note: the below are in an order such that they should only _possibly_ know about what is above them (as it would need to be for constructors...)
  Application::SDL2Manager _sdl;
  Data::AssetManager _assetManager;
  Animation::AnimationManager _animationSystem;
  Rendering::RenderManager _renderSystem;
  Rendering::ShaderManager _shaderManager;
  Input::InputManager _inputSystem;
  Application::ServiceManager _serviceManager;
  Application::StateManager _stateSystem;

  Delegate<> _onQuit;
  bool _quit = false;
};
}// namespace Application