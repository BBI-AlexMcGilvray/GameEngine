#include "Pipeline/Headers/ApplicationManager.h"

#include <iostream>

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

namespace Application {
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

Data::AssetManager& ApplicationManager::AssetManager()
{
  return _assetManager;
}

ApplicationManager::ApplicationManager()
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

  if (!_sdl.Initialize(*this)) {
    return false;
  }

  _animationSystem.Initialize();
  _renderSystem.Initialize(_sdl);
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