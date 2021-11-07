#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Scheduler.h"

#include "Pipeline/GameSystem/Headers/GameObjectManager.h"

#include "Pipeline/Input/Headers/InputManager.h"
#include "Pipeline/Rendering/Headers/CameraManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"
#include "Pipeline/Rendering/Headers/RenderObjectManager.h"
#include "Pipeline/Collision/Headers/CollisionManager.h"

using namespace Core;
using namespace Core::Functionality;

using namespace Application::GameSystem::Collision;

namespace Application {
struct State;

// debug
struct Rendering::Camera;

namespace GameSystem {
  // should handle any game-specifc logic on a global scale
  // the rest should be handled by various entities and (almost entirely) their components
  // essentially, this is where the 'hacks' go that can't work as components/need too much info
  struct GameSystemManager
  {
    const Ptr<State> ParentState;

    SchedulerBase Scheduler;
    GameObjectManager ObjectManager;

    // these should all be added in whenever a state is pushed, not as part of the game system
    Rendering::RenderObjectManager RObjectManager;
    Rendering::MaterialManager MaterialManager;
    Core::UniquePtr<Rendering::CameraManager> _cameraManager;// this should likely be specified by the world/data
    //CollisionManager CollisionSystem;

    // the game system manager should hold onto the current 'scene' and be able to switch between scenes (in order to load different game states)

    GameSystemManager(Ptr<State> parentState, Rendering::RenderManager &renderSystem, Input::InputManager &inputSystem);

    void Initialize();
    void Start();
    void Update(Second dt);
    void End();
    void CleanUp();

  private:
    // needs the render system to make changes on a game level. Ex: setting dead screen to red and the like
    Rendering::RenderManager &RenderSystem;
    Input::InputManager &InputSystem;
  };
}// namespace GameSystem
}// namespace Application