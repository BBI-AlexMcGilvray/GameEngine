#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

using namespace Core;

namespace Application
{
	struct State;

	struct StateManager
	{
		enum class SystemState
		{
			Initialized,
			Displaying,
			Transitioning,
			Clean,
			None
		};

		void Initialize();
		void Update(Second dt);
		void CleanUp();

		void PushState();
		// void PushState(AssetData<State> state);
		// void PushState(AsseName<State> state);
		void PopState();
		void RemoveState(Ptr<State> state);

		SystemState CurrentSystemState() const;
		Ptr<State> ActiveState() const;

	private:
		SystemState CurrentState = SystemState::None;
		List<UniquePtr<State>> States;
	};
}