#include "Pipeline/GameSystem/Headers/GameSystemManager.h"

#include "Pipeline/StateSystem/Headers/State.h"

namespace Application {
namespace GameSystem {
  GameSystemManager::GameSystemManager(Ptr<State> parentState, Rendering::RenderManager &renderSystem, Input::InputManager &inputSystem)
    : ParentState(parentState), RenderSystem(renderSystem), InputSystem(inputSystem)
  {}

  void GameSystemManager::Initialize()
  {}

  void GameSystemManager::Start()
  {}

  void GameSystemManager::Update(Second dt)
  {
    Scheduler.Update(dt);
    ObjectManager.Update(dt);
  }

  void GameSystemManager::End()
  {}

  void GameSystemManager::CleanUp()
  {}
}// namespace GameSystem
}// namespace Application