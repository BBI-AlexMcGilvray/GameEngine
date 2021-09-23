#pragma once

#include "Core/Headers/TimeDefs.h"

#include "Pipeline/Geometric/Headers/World.h"
#include "Pipeline/GameSystem/Headers/GameSystemManager.h"
#include "Pipeline/Input/Headers/InputManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

using namespace Core;

namespace Application {
struct State
{
  Event<> StateDeleted;

  State(Rendering::RenderManager &renderSystem, Input::InputManager &inputSystem);
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetName<State> state);
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetData<State> state);

  Geometric::World& getHierarchy();

  void Initialize();
  void Start();
  void Update(Second dt);
  void End();
  void CleanUp();

private:
  Core::UniquePtr<Geometric::World> Hierarchy;
  GameSystem::GameSystemManager GameSystem;
};
}// namespace Application