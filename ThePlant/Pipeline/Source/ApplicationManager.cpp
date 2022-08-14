#include "Pipeline/Headers/ApplicationManager.h"

#include <iostream>

#include "Pipeline/Time/Headers/TimeSettings.h"

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

namespace Application {
Core::Threading::ThreadManager& ApplicationManager::ThreadManager()
{
  return _threadManager;
}

Core::Threading::TaskManager& ApplicationManager::TaskManager()
{
  return _taskManager;
}
  
Time::TimeSystem& ApplicationManager::TimeSystem()
{
  return _timeSystem;
}

Data::AssetManager& ApplicationManager::AssetManager()
{
  return _assetManager;
}

AssetLoaderFactory& ApplicationManager::AssetLoaderFactory()
{
  return _assetLoader;
}

SDL2Manager& ApplicationManager::SDLManager()
{
  return _sdl;
}

Animation::AnimationManager &ApplicationManager::AnimationManager()
{
  return _animationSystem;
}

Rendering::RenderManager &ApplicationManager::RenderManager()
{
  return _renderSystem;
}

Rendering::ShaderManager& ApplicationManager::ShaderManager()
{
  return _shaderManager;
}

Input::InputManager &ApplicationManager::InputManager()
{
  return _inputSystem;
}

StateManager &ApplicationManager::StateManager()
{
  return _stateSystem;
}

ApplicationManager::ApplicationManager()
  : _serviceManager(*this)
  , _timeSystem(Application::Time::FIXED_30FPS)
  , _assetLoader(*this)
  , _shaderManager(_assetManager)
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
  if (!Initialize()) {
    std::cout << "Failed to initialize application" << std::endl;
    return;
  }

  Start();

  // take a look at Unity's order of execution and work on cleaning up execution order
  //      - https://docs.unity3d.com/Manual/ExecutionOrder.html
  while (!_quit)
  {    
    DEBUG_PROFILE_SCOPE("ApplicationManager::Run");
    _timeSystem.Update();
    while (_timeSystem.TakeFixedStep() && !quit()) { // checking quit here as well to enforce responsiveness (otherwise we don't quit until timesteps are caught up)
      Core::Second dt = _timeSystem.GetDeltaTime();
      Update(dt);
    // #ifdef MULTITHREADED_RENDERING // NOTE: not actually used due to current location of define
        Render(); // when threaded, this pushes the current buffer to the next thread, if we only did it once we would duplicate render data per frame
    // #endif
    }
  // #ifndef MULTITHREADED_RENDERING // NOTE: not actually used due to current location of define - need to fix, bottom should NOT be commented
      // Render(); // if rendering is not threaded, then we only render once per frame (otherwise waste time)
  // #endif
  }

  End();
  CleanUp();
}

bool ApplicationManager::Initialize()
{
  // possible we want to thread this to make it faster

  if (!_sdl.Initialize(*this)) {
    return false;
  }

  _timeSystem.Initialize();
  _animationSystem.Initialize();
  _renderSystem.Initialize(_sdl, _threadManager.GetThread());
  _inputSystem.initialize();

  return true;
}

void ApplicationManager::Start()
{
  _timeSystem.Start();
  _sdl.Start();
  _animationSystem.Start();
  _renderSystem.Start();
  _inputSystem.start();
}

void ApplicationManager::Update(Core::Second dt)
{
  DEBUG_PROFILE_SCOPE("ApplicationManager::Update");
  _inputSystem.update(dt); // inputs first to ensure up-to-date state
  _animationSystem.Update(dt);
  _stateSystem.Update(dt); // animations must be updated before the state (ecs)
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
  _renderSystem.End(_threadManager);
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