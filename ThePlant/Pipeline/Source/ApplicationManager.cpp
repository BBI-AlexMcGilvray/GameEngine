#include "Pipeline/Headers/ApplicationManager.h"

#include <iostream>

namespace Application {
Core::UniquePtr<ApplicationManager> ApplicationManager::_instance = nullptr;

Core::Ptr<ApplicationManager> ApplicationManager::Application()
{
  if (_instance == nullptr) {
    _instance = MakeUnique<ApplicationManager>(ConstructorTag());
  }

  return _instance.get();
}

SDL2Manager& ApplicationManager::AppSDLManager()
{
  return Application()->_sdl;
}

Animation::AnimationManager &ApplicationManager::AppAnimationManager()
{
  return Application()->_animationSystem;
}

// Collision::CollisionManager &ApplicationManager::AppCollisionManager()
// {
//   return Application()->_collisionManager;
// }

Rendering::RenderManager &ApplicationManager::AppRenderManager()
{
  return Application()->_renderSystem;
}

Rendering::ShaderManager& ApplicationManager::AppShaderManager()
{
  return Application()->_shaderManager;
}

Input::InputManager &ApplicationManager::AppInputManager()
{
  return Application()->_inputSystem;
}

StateManager &ApplicationManager::AppStateManager()
{
  return Application()->_stateSystem;
}

Data::AssetManager& ApplicationManager::AppAssetManager()
{
  return Application()->_assetManager;
}

// ECS& ApplicationManager::AppECS()
// {
//   return Application()->_ecsSystem;
// }

ApplicationManager::ApplicationManager(ConstructorTag tag)
  // : _collisionManager(_ecsSystem, Core::Math::Float3(1024.0f)) // must be data driven somewhere instead (in the world?)
  : _shaderManager(_assetManager)
  , _inputSystem(_sdl)
  , _stateSystem(*this)
  , _onQuit([this]() {
      _quit = true;
      return false;
    }, _inputSystem.Quit)
{
}

void ApplicationManager::Run()
{
  FixedStepTimeManager time;
  if (!Initialize()) {
    std::cout << "Failed to initialize application" << std::endl;
    return;
  }
  time.Initialize();

  Start();
  time.Start();

  while (!_quit)
  {
    Update();

    Core::Second dt = time.Update();
    while (dt > 0_s) {
      Update(dt);
      dt = time.GetAccumulatedTime();
    }
  }

  End();
  CleanUp();
}

bool ApplicationManager::Initialize()
{
  // possible we want to thread this to make it faster

  if (!_sdl.Initialize()) {
    return false;
  }

  _animationSystem.Initialize();
  _renderSystem.Initialize(_sdl.GetWindowManager());
  _inputSystem.initialize();

  return true;
}

void ApplicationManager::Start()
{
  _sdl.Start();
  _animationSystem.Start();
  _renderSystem.Start();
  _inputSystem.start();
}

void ApplicationManager::Update()
{
  _inputSystem.update();
}

void ApplicationManager::Update(Core::Second dt)
{
  // this may requried the dt passed in for time-reliant systems?
  // _ecsSystem.Update(); // either way, this can't be above as this is only once-per frame (or should be)

  // update everything
  _stateSystem.Update(dt);

  _animationSystem.Update(dt);
  _renderSystem.Render();
}

void ApplicationManager::End()
{
  _inputSystem.end();
  _animationSystem.End();
  _renderSystem.End();
  _sdl.End();
}

void ApplicationManager::CleanUp()
{
  // possible we want to thread this to make it faster (since saving could be done)
  _inputSystem.cleanUp();
  _renderSystem.CleanUp();
  _animationSystem.CleanUp();
  _sdl.CleanUp();
}
}// namespace Application