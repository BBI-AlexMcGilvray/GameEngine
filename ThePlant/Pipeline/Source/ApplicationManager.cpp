#include "Pipeline/Headers/ApplicationManager.h"

#include <iostream>

namespace Application {
Core::UniquePtr<ApplicationManager> ApplicationManager::Instance = nullptr;

Core::Ptr<ApplicationManager> ApplicationManager::Application()
{
  if (Instance == nullptr) {
    Instance = MakeUnique<ApplicationManager>(ConstructorTag());
  }

  return Instance.get();
}

SDL2Manager& ApplicationManager::AppSDLManager()
{
  return Application()->SDL;
}

AnimationManager &ApplicationManager::AppAnimationManager()
{
  return Application()->AnimationSystem;
}

RenderManager &ApplicationManager::AppRenderManager()
{
  return Application()->RenderSystem;
}

InputManager &ApplicationManager::AppInputManager()
{
  return Application()->InputSystem;
}

StateManager &ApplicationManager::AppStateManager()
{
  return Application()->StateSystem;
}

Data::AssetManager& ApplicationManager::AppAssetManager()
{
  return Application()->_assetManager;
}

ECS& ApplicationManager::AppECS()
{
  return Application()->_ecsSystem;
}

ApplicationManager::ApplicationManager(ConstructorTag tag)
  : InputSystem(SDL), StateSystem(RenderSystem, InputSystem), OnQuit([this]() {
      Quit = true;
      return false;
    }
  , InputSystem.Quit)
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

  while (!Quit)
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

  if (!SDL.Initialize()) {
    return false;
  }

  AnimationSystem.Initialize();
  RenderSystem.Initialize(SDL.GetWindowManager());
  InputSystem.initialize();
  StateSystem.Initialize();

  return true;
}

void ApplicationManager::Start()
{
  SDL.Start();
  AnimationSystem.Start();
  RenderSystem.Start();
  InputSystem.start();
  StateSystem.Start();
}

void ApplicationManager::Update()
{
  InputSystem.update();
}

void ApplicationManager::Update(Core::Second dt)
{
  // update everything
  StateSystem.Update(dt);

  AnimationSystem.Update(dt);
  RenderSystem.Update(dt);
}

void ApplicationManager::End()
{
  StateSystem.End();
  InputSystem.end();
  AnimationSystem.End();
  RenderSystem.End();
  SDL.End();
}

void ApplicationManager::CleanUp()
{
  // possible we want to thread this to make it faster (since saving could be done)
  StateSystem.CleanUp();
  InputSystem.cleanUp();
  RenderSystem.CleanUp();
  AnimationSystem.CleanUp();
  SDL.CleanUp();
}
}// namespace Application