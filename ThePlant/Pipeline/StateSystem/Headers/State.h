#pragma once

#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"

using namespace Core;

namespace Data
{
class AssetManager;
}

namespace Application {
struct ApplicationManager;
struct SDL2Manager;
struct StateManager;

namespace Animation
{
  class AnimationManager;
}
namespace Collision
{
  struct CollisionManager;
}
namespace Input
{
  struct InputManager;
}
namespace Rendering
{
  struct RenderManager;
  class ShaderManager;
}

struct State
{
  Core::Functionality::Event<> stateDeleted;

  State(Application::ApplicationManager& applicationManager, const Core::Math::Float3& worldSize);
  // we will need states to be data-driven, though maybe this is not the proper way to do it (instead, have a CreateState method or something)
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetName<State> state);
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetData<State> state);

  virtual ~State();

  SDL2Manager& SDLManager();
  Application::ApplicationManager& ApplicationManager();
  Animation::AnimationManager& AnimationManager();
  Collision::CollisionManager& CollisionManager();
  ECS& ECS();
  Rendering::RenderManager& RenderManager();
  Rendering::ShaderManager& ShaderManager();
  Input::InputManager& InputManager();
  StateManager& StateManager();
  Data::AssetManager& AssetManager();

  virtual void Initialize() {};
  virtual void Start() {};
  void Update(Second dt);
  virtual void End() {};
  virtual void CleanUp() {};

protected:
  Application::ApplicationManager& _applicationManager;
  Application::ECS _ecs;
  Collision::CollisionManager _collisionManager;

  // custom state types should override these to get their desired behaviours
  virtual void _PreECSUpdate(Second dt) {};
  virtual void _PostECSUpdate(Second dt) {};
};
}// namespace Application