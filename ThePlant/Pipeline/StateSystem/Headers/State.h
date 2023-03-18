#pragma once

#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

#include "Data/Headers/AssetData.h"
#include "Data/AssetTypes/StateData.h"

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
class EntityFactory;
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
namespace UI {
  namespace IMGUI {
    class Manager;
  }
}

struct State
{
  Core::Functionality::Event<> stateDeleted;

  State(Application::ApplicationManager& applicationManager, const Core::Math::Float3& worldSize, const Application::Physics::Settings& physicsSettings);
  // states can be created using an AssetData<StateData>. We don't do this through the AssetLoaderFactory because we can't dictate if we want to go to it or just load it
  State(Application::ApplicationManager& applicationManager, const Data::AssetData<Data::StateData>& asset);

  virtual ~State();

  Core::Threading::ThreadManager& ThreadManager();
  Core::Threading::TaskManager& TaskManager();
  
  Application::Time::TimeSystem& TimeSystem();

  Data::AssetManager& AssetManager();
  AssetLoaderFactory& AssetLoaderFactory();
  EntityFactory& EntityFactory();

  SDL2Manager& SDLManager();

  UI::IMGUI::Manager& IMGUI();

  Input::InputManager& InputManager();  
  Application::ApplicationManager& ApplicationManager();
  Animation::AnimationManager& AnimationManager();
  Collision::CollisionManager& CollisionManager();
  ECS& ECS();
  Application::Physics::Settings& PhysicsSettings();
  Rendering::RenderManager& RenderManager();
  Rendering::ShaderManager& ShaderManager();
  Rendering::MaterialManager& MaterialManager();
  StateManager& StateManager();

  virtual void Initialize();
  virtual void Start();
  void Update(Core::Second dt);
  virtual void End();
  virtual void CleanUp() {};

protected:
  Application::ApplicationManager& _applicationManager;
  Application::ECS _ecs;
  Collision::CollisionManager _collisionManager;
  Application::Physics::Settings _physicsSettings;

  // custom state types should override these to get their desired behaviours
  virtual void _PreECSUpdate(Core::Second dt) {};
  virtual void _PostECSUpdate(Core::Second dt) {};
};
}// namespace Application