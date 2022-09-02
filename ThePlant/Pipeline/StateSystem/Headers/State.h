#pragma once

#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

#include "Pipeline/AssetHandling/EntityFactory.h"
#include "Pipeline/Collision/CollisionManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/Physics/PhysicsSettings.h"

namespace Core
{
namespace Threading
{
class TaskManager;
class ThreadManager;
}
}

namespace Data
{
class AssetManager;
}

namespace Application {
struct ApplicationManager;
class AssetLoaderFactory;
struct SDL2Manager;
struct StateManager;

namespace Time
{
  struct TimeSystem;
}

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
  struct MaterialManager;
  struct RenderManager;
  class ShaderManager;
}

struct State
{
  Core::Functionality::Event<> stateDeleted;

  State(Application::ApplicationManager& applicationManager, const Core::Math::Float3& worldSize, const Application::Physics::Settings& physicsSettings);
  // we will need states to be data-driven, though maybe this is not the proper way to do it (instead, have a CreateState method or something)
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetName<State> state);
  // State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem, AssetData<State> state);

  virtual ~State();

  Core::Threading::ThreadManager& ThreadManager();
  Core::Threading::TaskManager& TaskManager();
  
  Application::Time::TimeSystem& TimeSystem();

  Data::AssetManager& AssetManager();
  AssetLoaderFactory& AssetLoaderFactory();

  SDL2Manager& SDLManager();
  Application::ApplicationManager& ApplicationManager();
  EntityFactory& EntityFactory();
  Animation::AnimationManager& AnimationManager();
  Collision::CollisionManager& CollisionManager();
  ECS& ECS();
  Application::Physics::Settings& PhysicsSettings();
  Rendering::RenderManager& RenderManager();
  Rendering::ShaderManager& ShaderManager();
  Rendering::MaterialManager& MaterialManager();
  Input::InputManager& InputManager();
  StateManager& StateManager();

  virtual void Initialize();
  virtual void Start();
  void Update(Core::Second dt);
  virtual void End();
  virtual void CleanUp() {};

protected:
  Application::ApplicationManager& _applicationManager;
  Application::EntityFactory _entityFactory;
  Application::ECS _ecs;
  Collision::CollisionManager _collisionManager;
  Application::Physics::Settings _physicsSettings;

  // custom state types should override these to get their desired behaviours
  virtual void _PreECSUpdate(Core::Second dt) {};
  virtual void _PostECSUpdate(Core::Second dt) {};
};
}// namespace Application