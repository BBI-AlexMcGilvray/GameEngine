#include "Pipeline/Headers/ApplicationManager.h"

#include <iostream>

#if DEBUG
#include "Core/Debugging/Profiling/Utils.h"
#endif

// #if FACTORY
// should this be here? if not here, where?
#include "Pipeline/Factory_Temp/Factory.h"
// #endif // FACTORY
#include "Pipeline/Time/Headers/TimeSettings.h"
#include "Pipeline/Utils/RegisterUtils.h"

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

EntityFactory& ApplicationManager::EntityFactory()
{
  return _entityFactory;
}

SDL2Manager& ApplicationManager::SDLManager()
{
  return _sdl;
}

UI::IMGUI::Manager& ApplicationManager::IMGUI()
{
  return _imguiUI;
}

Input::InputManager &ApplicationManager::InputManager()
{
  return _inputSystem;
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

Rendering::MaterialManager& ApplicationManager::MaterialManager()
{
  return _materialManager;
}

Rendering::MeshManager& ApplicationManager::MeshManager()
{
  return _meshManager;
}

StateManager &ApplicationManager::StateManager()
{
  return _stateSystem;
}

ApplicationManager::ApplicationManager()
  : _serviceManager(*this)
  , _timeSystem(Application::Time::FIXED_30FPS)
  , _assetLoader(*this)
  , _entityFactory(_assetLoader, _assetManager)
  , _imguiUI(_sdl.GetWindowManager(), _sdl.GetContextManager())
  , _inputSystem(_sdl)
  , _shaderManager(_assetManager, _assetLoader)
  , _materialManager(_assetManager, _assetLoader, _shaderManager)
  , _meshManager(_assetManager, _assetLoader)
  , _renderSystem(_shaderManager, _meshManager)
#if MULTITHREADED_RENDERING
  , _renderThread(*this)
#endif
  , _stateSystem(*this)
#ifndef MULTITHREADED_RENDERING
  , _onQuit([this]() {
      Quit();
      return false;
    }, _inputSystem.Quit)
#endif
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
    while (_timeSystem.TakeFixedStep() && !ShouldQuit()) { // checking quit here as well to enforce responsiveness (otherwise we don't quit until timesteps are caught up)
      Core::Second dt = _timeSystem.GetDeltaTime();
      Update(dt);
    #ifdef MULTITHREADED_RENDERING
        Render(); // when threaded, this pushes the current buffer to the next thread, if we only did it once we would duplicate render data per frame
    #endif
    }
  #ifndef MULTITHREADED_RENDERING
      Render(); // if rendering is not threaded, then we only render once per frame (otherwise waste time)
  #endif
  }

  End();
  CleanUp();
}

bool ApplicationManager::Initialize()
{
  // possible we want to thread this to make it faster

  _timeSystem.Initialize();

#ifdef MULTITHREADED_RENDERING
  CreateAndRunRenderThread(_renderThread, _threadManager.GetThread());
  _renderThread.SetExecutionState(RenderThread::ExecutionState::Initialize);
#else
  if (!_sdl.Initialize(RenderManager())) {
    return false;
  }

  _imguiUI.Initialize();
  _inputSystem.initialize();
  _renderSystem.Initialize(_sdl, _inputSystem);
  SDL_GL_MakeCurrent(_sdl.GetWindowManager().GetWindow(), _sdl.GetContextManager().GetContext());
#endif

  _animationSystem.Initialize();
  // if not threaded, the context is active on this thread

  // should this be here? if not here, where?
  WITH_DEBUG_SERVICE(Editor::Factory)
  (
    service->Initialize();
  )

  RegisterComponents(*this);

  return true;
}

void ApplicationManager::Start()
{
#ifdef MULTITHREADED_RENDERING
  _renderThread.SetExecutionState(RenderThread::ExecutionState::Start);
#else
  _sdl.Start();
  _imguiUI.Start();
  _inputSystem.start();
  _renderSystem.Start();
#endif

  _timeSystem.Start();
  _animationSystem.Start();
  
  // should this be here? if not here, where?
  WITH_DEBUG_SERVICE(Editor::Factory)
  (
    service->Start();
  )

#ifdef MULTITHREADED_RENDERING
  _renderThread.SetExecutionState(RenderThread::ExecutionState::Update);
#endif
}

void ApplicationManager::Update(Core::Second dt)
{
  DEBUG_PROFILE_SCOPE("ApplicationManager::Update");
  _inputSystem.update(dt); // inputs first to ensure up-to-date state
  _animationSystem.Update(dt);
  _stateSystem.Update(dt); // animations must be updated before the state (ecs)
  
  // should this be here? if not here, where?
  WITH_DEBUG_SERVICE(Editor::Factory)
  (
    service->Update(dt);
  )
}

void ApplicationManager::Render()
{
  DEBUG_PROFILE_SCOPE("ApplicationManager::Render");
  _renderSystem.Render();
}

void ApplicationManager::End()
{
  _animationSystem.End();
  _renderSystem.End();
  _inputSystem.end();
  _imguiUI.End();
  _sdl.End();
  
#ifdef MULTITHREADED_RENDERING
  _renderThread.SetExecutionState(RenderThread::ExecutionState::End);
#else
  _renderSystem.End();
  _inputSystem.end();
  _imguiUI.End();
  _sdl.End();
#endif

  // should this be here? if not here, where?
  WITH_DEBUG_SERVICE(Editor::Factory)
  (
    service->End();
  )
}

void ApplicationManager::CleanUp()
{
  // possible we want to thread this to make it faster (since saving could be done)
  _animationSystem.CleanUp();

#ifdef MULTITHREADED_RENDERING
  _renderThread.SetExecutionState(RenderThread::ExecutionState::CleanUp);
  _threadManager.ReturnThread(std::move(_renderThread.ReleaseThread()));
#else
  _renderSystem.CleanUp();
  _inputSystem.cleanUp();
  _imguiUI.CleanUp();
  _sdl.CleanUp();
#endif

  // should this be here? if not here, where?
  WITH_DEBUG_SERVICE(Editor::Factory)
  (
    service->CleanUp();
  )
}
}// namespace Application