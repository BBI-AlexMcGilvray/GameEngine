#pragma once

#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Geometric/Headers/World.h"
#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"
#include "ApplicationManagement/Input/Headers/InputManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

using namespace Core;

namespace Application {
struct State
{
  Event<> StateDeleted;

  State(Rendering::RenderManager &renderSystem, Input::InputManager &inputSystem);
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetName<State> state);
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetData<State> state);

  void Initialize();
  void Start();
  void Update(Second dt);
  void End();
  void CleanUp();

  //Ptr<Transform> CreateNewNode(String name);

private:
  Core::UniquePtr<Geometric::World> Hierarchy;
  GameSystem::GameSystemManager GameSystem;
};
}// namespace Application