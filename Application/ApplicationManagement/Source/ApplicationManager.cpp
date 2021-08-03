#include "ApplicationManagement/Headers/ApplicationManager.h"

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

FixedStepTimeManager &ApplicationManager::AppTimeManager()
{
  return Application()->Time;
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

ApplicationManager::ApplicationManager(ConstructorTag tag)
  : InputSystem(SDL), StateSystem(RenderSystem, InputSystem), OnQuit([this]() {
      Quit = true;
      return false;
    },
                                                                InputSystem.Quit)
{
}

void ApplicationManager::Run()
{
  if (!Initialize()) {
    std::cout << "Failed to initialize application" << std::endl;
    return;
  }

  Start();

  while (!Quit && Update()) {}

  End();
  CleanUp();
}

bool ApplicationManager::Initialize()
{
  // possible we want to thread this to make it faster

  if (!SDL.Initialize()) {
    return false;
  }

  Time.Initialize();
  AnimationSystem.Initialize();
  RenderSystem.Initialize(SDL.GetWindowManager());
  InputSystem.Initialize();
  StateSystem.Initialize();

  return true;
}

void ApplicationManager::Start()
{
  SDL.Start();
  Time.Start();
  AnimationSystem.Start();
  RenderSystem.Start();
  InputSystem.Start();
  StateSystem.Start();
}

bool ApplicationManager::Update()
{
  InputSystem.Update();// gets input through SDL

  // game manager update (will update game logic, colliders, game object, renderers)
  auto dt = Time.Update();

  // update everything
  while (dt > 0_s) {
    // update everything
    StateSystem.Update(dt);

    AnimationSystem.Update(dt);
    RenderSystem.Update(dt);

    dt = Time.GetAccumulatedTime();
  }

  return true;
}

void ApplicationManager::End()
{
  StateSystem.End();
  InputSystem.End();
  AnimationSystem.End();
  RenderSystem.End();
  Time.End();
  SDL.End();
}

void ApplicationManager::CleanUp()
{
  // possible we want to thread this to make it faster (since saving could be done)
  StateSystem.CleanUp();
  InputSystem.CleanUp();
  RenderSystem.CleanUp();
  AnimationSystem.CleanUp();
  Time.CleanUp();
  SDL.CleanUp();
}
}// namespace Application