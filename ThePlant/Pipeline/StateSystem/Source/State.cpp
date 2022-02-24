#include "Pipeline/StateSystem/Headers/State.h"

#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
State::State(Application::ApplicationManager& applicationManager, const Core::Math::Float3& worldSize)
: _applicationManager(applicationManager)
, _collisionManager(_ecs, worldSize)
{}

State::~State()
{
  if (stateDeleted)
  {
    stateDeleted();
  }
}

SDL2Manager& State::SDLManager() { return _applicationManager.SDLManager(); }
Application::ApplicationManager& State::ApplicationManager() { return _applicationManager; }
Animation::AnimationManager& State::AnimationManager() { return _applicationManager.AnimationManager(); }
Collision::CollisionManager& State::CollisionManager() { return _collisionManager; }
ECS& State::ECS() { return _ecs; }
Rendering::RenderManager& State::RenderManager() { return _applicationManager.RenderManager(); }
Rendering::ShaderManager& State::ShaderManager() { return _applicationManager.ShaderManager(); }
Input::InputManager& State::InputManager() { return _applicationManager.InputManager(); }
StateManager& State::StateManager() { return _applicationManager.StateManager(); }
Data::AssetManager& State::AssetManager() { return _applicationManager.AssetManager(); }

void State::Update(Second dt)
{
  _PreECSUpdate(dt);
  _ecs.Update();
  _PostECSUpdate(dt);
}
}// namespace Application