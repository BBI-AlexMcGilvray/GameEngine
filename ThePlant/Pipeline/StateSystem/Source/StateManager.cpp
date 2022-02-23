#include "Pipeline/StateSystem/Headers/StateManager.h"

#include "Core/Debugging/Headers/Macros.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Application {
StateManager::StateManager(ApplicationManager& applicationManager)
: _applicationManager(applicationManager)
{}

void StateManager::Update(Second dt)
{
  GetActiveState().Update(dt);
}

void StateManager::RemoveState(const Core::instanceId<State>& state)
{
  _GetState(state).CleanUp();
  _states.erase(state);
}

void StateManager::GoToState(const Core::instanceId<State>& state)
{
  VERIFY(_states.find(state) != _states.end(), "Going to state that does not exist");

  if (_activeState.IsValid())
  {
    GetActiveState().End();
  }
  _activeState = state;
  GetActiveState().Start();

  if (stateChanged)
  {
    stateChanged();
  }
}

State& StateManager::GetActiveState() const
{
  return _GetState(_activeState);
}

State& StateManager::_GetState(const Core::instanceId<State>& state) const
{
  Core::Ptr<State> activeState = _states.at(state).get();
  return *activeState;
}
}// namespace Application