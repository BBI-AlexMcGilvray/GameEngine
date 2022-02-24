#include "Pipeline/Headers/ApplicationManager.h"

#include <iostream>

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

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
    DEBUG_PROFILE_SCOPE("ApplicationManager::Run");
    Core::Second dt = time.Update();
    while (dt > 0_s) {
      Update(dt);
      dt = time.GetAccumulatedTime();
    }
    Render();

    // clear before final pop to not clear the final stack.
    // however, this means that the displayed data is one frame behind
    DEBUG_CLEAR_PROFILE();
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

void ApplicationManager::Update(Core::Second dt)
{
  DEBUG_PROFILE_SCOPE("ApplicationManager::Update");
  _inputSystem.update();
  _animationSystem.Update(dt);
  _stateSystem.Update(dt); // animations should be updated before the state (ecs)
}

void ApplicationManager::Render()
{
  DEBUG_PROFILE_SCOPE("ApplicationManager::Render");
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