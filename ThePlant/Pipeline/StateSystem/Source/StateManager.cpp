#include "Pipeline/StateSystem/Headers/StateManager.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application {
StateManager::StateManager(Rendering::RenderManager &renderSystem, Input::InputManager &inputSystem)
  : RenderSystem(renderSystem), InputSystem(inputSystem)
{
}

void StateManager::Initialize()
{
  // knowing what state to push first can be in a config file, or based on an instantation of a specific templated type
  PushState();

  CurrentState = SystemState::Initialized;
}

void StateManager::Start()
{
  for (int i = 0; i < States.size(); i++) {
    States[i]->Start();
  }

  CurrentState = SystemState::Started;
}

void StateManager::Update(Second dt)
{
  if (CurrentState == SystemState::Transitioning) {
    ChangeToState(States[States.size() - 1].get());
    // Transition(dt);
  }

  GetActiveState().Update(dt);
}

void StateManager::End()
{
  for (int i = 0; i < States.size(); i++) {
    States[i]->End();
  }

  CurrentState = SystemState::Ended;
}

void StateManager::CleanUp()
{
  for (int i = 0; i < States.size(); i++) {
    States[i]->CleanUp();
  }

  CurrentState = SystemState::Clean;
}

void StateManager::PushState(StateTransitionInfo transitionInfo)
{
  States.push_back(MakeUnique<State>(RenderSystem, InputSystem));
  States[States.size() - 1]->Initialize();

  GoToState(States[States.size() - 1].get(), transitionInfo);
}

// void StateManager::PushState(AssetData<State> state, StateTransitionInfo transitionInfo)
//{

//}

// void StateManager::PushState(AsseName<State> state, StateTransitionInfo transitionInfo)
//{

//}

void StateManager::GoToState(Ptr<State> state, StateTransitionInfo transitionInfo)
{
  TransitionInfo = transitionInfo;

  switch (TransitionInfo.Process) {
  case TransitionProcess::PreEmptive: {
    break;
  }
  case TransitionProcess::Immediate: {
    ChangeToState(state);
    break;
  }
  case TransitionProcess::Transition: {
    CurrentState = SystemState::Transitioning;
    break;
  }
  }
}

void StateManager::PopState()
{
  if (States.size() > 0) {
    RemoveState(States[States.size() - 1].get());
  }
}

void StateManager::RemoveState(Ptr<State> state)
{
  for (Core::size i = States.size(); i >= 0; i--) {
    if (States[i].get() == state) {
      if (States[i].get() == ActiveState) {
        if (i > 0) {
          ActiveState = States[i - 1].get();
        } else {
          ActiveState = nullptr;
        }
      }

      if (States[i].get() == PreviousState) {
        if (i > 0) {
          PreviousState = States[i - 1].get();
        } else {
          PreviousState = nullptr;
        }
      }

      States.erase(States.begin() + i);
      break;
    }
  }
}

StateManager::SystemState StateManager::CurrentSystemState() const
{
  return CurrentState;
}

State& StateManager::GetActiveState() const
{
  return *ActiveState;
}

void StateManager::ChangeToState(Ptr<State> state)
{
  DEBUG_ASSERT(state != nullptr);

  if (ActiveState != nullptr) {
    ActiveState->End();
  }

  PreviousState = ActiveState;
  ActiveState = state;

  if (CurrentState != SystemState::None) {
    ActiveState->Start();
  }

  CurrentState = SystemState::Displaying;
  StateChanged();
}
}// namespace Application