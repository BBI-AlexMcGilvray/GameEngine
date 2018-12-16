#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Input/Headers/InputManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

#include "ApplicationManagement/StateSystem/Headers/State.h"

using namespace Core;

namespace Application
{
	struct StateManager
	{
		enum class SystemState
		{
			Initialized,
			Started,
			Displaying,
			Transitioning,
			Ended,
			Clean,
			None
		};

		StateManager(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem);

		void Initialize();
		void Start();
		void Update(Second dt);
		void End();
		void CleanUp();

		void PushState();
		// void PushState(AssetData<State> state);
		// void PushState(AsseName<State> state);
		void PopState();
		void RemoveState(Ptr<State> state);

		SystemState CurrentSystemState() const;
		Ptr<State> ActiveState() const;

	private:
		// needs references to pass to states
		Rendering::RenderManager& RenderSystem;
		Input::InputManager& InputSystem;

		SystemState CurrentState = SystemState::None;
		List<UniquePtr<State>> States;
	};
}