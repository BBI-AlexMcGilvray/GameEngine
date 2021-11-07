#pragma once

#include <vector>

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Event.h"

#include "Pipeline/Input/Headers/InputManager.h"
#include "Pipeline/Rendering/Headers/RenderManager.h"

#include "Pipeline/StateSystem/Headers/State.h"

using namespace Core;

namespace Application {
struct StateManager
{
  enum class SystemState {
    Initialized,
    Started,
    Displaying,
    Transitioning,
    Ended,
    Clean,
    None
  };

  enum class TransitionProcess {
    PreEmptive,// state is added, but not gone to
    Immediate,// state is added and gone to immediately
    Transition,// state is added and transitioned to
  };

  enum class TransitionStyle {
    FadeOut,
    FadeIn,
    FadeOutFadeIn
  };

  Event<> StateChanged;

  // maybe this should be a transition manager or something? can be done later
  struct StateTransitionInfo
  {
    TransitionProcess Process;
    TransitionStyle Style;
    Second Duration;

    StateTransitionInfo(TransitionProcess process = TransitionProcess::Immediate, TransitionStyle style = TransitionStyle::FadeOut, Second duration = Second(0))
      : Process(process), Style(style), Duration(duration)
    {}
  };

  StateManager(Rendering::RenderManager &renderSystem, Input::InputManager &inputSystem);

  void Initialize();
  void Start();
  void Update(Second dt);
  void End();
  void CleanUp();

  void PushState(StateTransitionInfo transitionInfo = StateTransitionInfo());
  // void PushState(AssetData<State> state, StateTransitionInfo transitionInfo = StateTransitionInfo());
  // void PushState(AsseName<State> state, StateTransitionInfo transitionInfo = StateTransitionInfo());
  void GoToState(Ptr<State> state, StateTransitionInfo transitionInfo = StateTransitionInfo());
  void PopState();
  void RemoveState(Ptr<State> state);

  SystemState CurrentSystemState() const;
  State& GetActiveState() const;

private:
  void ChangeToState(Ptr<State> state);

  // needs references to pass to states
  Rendering::RenderManager &RenderSystem;
  Input::InputManager &InputSystem;

  std::vector<UniquePtr<State>> States;

  SystemState CurrentState = SystemState::None;
  StateTransitionInfo TransitionInfo;
  Ptr<State> ActiveState = nullptr;
  Ptr<State> PreviousState = nullptr;
};
}// namespace Application