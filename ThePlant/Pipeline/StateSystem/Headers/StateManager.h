#pragma once

#include <vector>

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/IdTypes/InstanceId.h"

#include "Core/Functionality/Headers/Event.h"

#include "Pipeline/StateSystem/Headers/State.h"

using namespace Core;

namespace Application {
struct ApplicationManager;
struct State;

struct StateManager
{
  Core::Functionality::Event<> stateChanged;

  StateManager(ApplicationManager& applicationManager);

  void Update(Second dt);

  template <typename STATE, typename ...ARGS>
  Core::instanceId<State> AddState(ARGS&& ...args)
  {
    Core::instanceId<State> newId = GetInstanceId<State>();

    _states.emplace(std::make_pair(newId, std::make_unique<STATE>(_applicationManager, std::forward<ARGS>(args)...)));
    _GetState(newId).Initialize();

    return newId;
  }

  template <typename STATE, typename ...ARGS>
  Core::instanceId<State> AddAndGoToState(ARGS&& ...args)
  {
    Core::instanceId<State> newId = GetInstanceId<State>();

    _states.emplace(std::make_pair(newId, std::make_unique<STATE>(_applicationManager, std::forward<ARGS>(args)...)));
    _GetState(newId).Initialize();

    GoToState(newId);

    return newId;
  }

  void RemoveState(const Core::instanceId<State>& state);

  void GoToState(const Core::instanceId<State>& state);

  State& GetActiveState() const;

private:
  ApplicationManager& _applicationManager;

  std::unordered_map<Core::instanceId<State>, std::unique_ptr<State>, Core::instanceIdHasher<State>> _states;
  Core::instanceId<State> _activeState;

  State& _GetState(const Core::instanceId<State>& state) const;
};
}// namespace Application