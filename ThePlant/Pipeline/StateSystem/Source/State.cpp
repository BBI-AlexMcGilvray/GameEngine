#include "Pipeline/StateSystem/Headers/State.h"

#include "Core/Headers/Hash.h"

#include "Data/AssetTypes/EntityData.h"

#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
State::State(Application::ApplicationManager& applicationManager, const Core::Math::Float3& worldSize, const Application::Physics::Settings& physicsSettings)
: _applicationManager(applicationManager)
, _collisionManager(_ecs, worldSize)
, _physicsSettings(physicsSettings)
{}

State::State(Application::ApplicationManager& applicationManager, const Data::AssetData<Data::StateData>& assetData)
: _applicationManager(applicationManager)
, _collisionManager(_ecs, assetData->worldSize)
, _physicsSettings{ assetData->physics.gravity }
{}

State::~State()
{
  if (stateDeleted)
  {
    stateDeleted();
  }
}

Core::Threading::ThreadManager& State::ThreadManager() { return _applicationManager.ThreadManager(); }
Core::Threading::TaskManager& State::TaskManager() { return _applicationManager.TaskManager(); }
Application::Time::TimeSystem& State::TimeSystem() { return _applicationManager.TimeSystem(); }
Data::AssetManager& State::AssetManager() { return _applicationManager.AssetManager(); }
AssetLoaderFactory& State::AssetLoaderFactory() { return _applicationManager.AssetLoaderFactory(); }
EntityFactory& State::EntityFactory() { return _applicationManager.EntityFactory(); }
SDL2Manager& State::SDLManager() { return _applicationManager.SDLManager(); }
UI::IMGUI::Manager& State::IMGUI() { return _applicationManager.IMGUI(); }
Input::InputManager& State::InputManager() { return _applicationManager.InputManager(); }
Application::ApplicationManager& State::ApplicationManager() { return _applicationManager; }
Animation::AnimationManager& State::AnimationManager() { return _applicationManager.AnimationManager(); }
Collision::CollisionManager& State::CollisionManager() { return _collisionManager; }
ECS& State::ECS() { return _ecs; }
Application::Physics::Settings& State::PhysicsSettings() { return _physicsSettings; }
Rendering::RenderManager& State::RenderManager() { return _applicationManager.RenderManager(); }
Rendering::ShaderManager& State::ShaderManager() { return _applicationManager.ShaderManager(); }
Rendering::MaterialManager& State::MaterialManager() { return _applicationManager.MaterialManager(); }
Rendering::MeshManager& State::MeshManager() { return _applicationManager.MeshManager(); }
StateManager& State::StateManager() { return _applicationManager.StateManager(); }

void State::Initialize()
{}

void State::Start()
{};

void State::Update(Core::Second dt)
{
  _PreECSUpdate(dt);
  _ecs.Update();
  _PostECSUpdate(dt);
}

void State::End()
{};
}// namespace Application