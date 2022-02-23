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

SDL2Manager& State::SDLManager() { return _applicationManager.AppSDLManager(); }
Application::ApplicationManager& State::ApplicationManager() { return _applicationManager; }
Animation::AnimationManager& State::AnimationManager() { return _applicationManager.AppAnimationManager(); }
Collision::CollisionManager& State::CollisionManager() { return _collisionManager; }
ECS& State::ECS() { return _ecs; }
Rendering::RenderManager& State::RenderManager() { return _applicationManager.AppRenderManager(); }
Rendering::ShaderManager& State::ShaderManager() { return _applicationManager.AppShaderManager(); }
Input::InputManager& State::InputManager() { return _applicationManager.AppInputManager(); }
StateManager& State::StateManager() { return _applicationManager.AppStateManager(); }
Data::AssetManager& State::AssetManager() { return _applicationManager.AppAssetManager(); }

void State::Update(Second dt)
{
  _PreECSUpdate(dt);
  _ecs.Update();
  _PostECSUpdate(dt);
}
}// namespace Application