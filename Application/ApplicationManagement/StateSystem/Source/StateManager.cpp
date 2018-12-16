#include "ApplicationManagement/StateSystem/Headers/StateManager.h"

#include "ApplicationManagement/StateSystem/Headers/State.h"

namespace Application
{
	void StateManager::Initialize()
	{
		CurrentState = SystemState::Initialized;
	}

	void StateManager::Update(Second dt)
	{
		if (CurrentState == SystemState::Transitioning)
		{
			// Transition(dt);
		}

		ActiveState()->Update(dt);
	}

	void StateManager::CleanUp()
	{
		for (int i = 0; i < States.size; i++)
		{
			States[i].CleanUp();
		}

		CurrentState = SystemState::Clean;
	}

	void StateManager::PushState()
	{
		Push(States, MakeUnique<State>());
	}

	// void StateManager::PushState(AssetData<State> state)
	//{

	//}

	// void StateManager::PushState(AsseName<State> state)
	//{

	//}

	void StateManager::PopState()
	{
		Pop(States);
	}

	void StateManager::RemoveState(Ptr<State> state)
	{
		for (int i = 0; i < States.size(); i++)
		{
			if (States[i].get() == state)
			{
				RemoveIndex(States, i);
			}
		}
	}

	StateManager::SystemState StateManager::CurrentSystemState() const
	{
		return CurrentState;
	}

	Ptr<State> StateManager::ActiveState() const
	{
		if (States.size < 1)
		{
			return nullptr;
		}

		return States[States.size];
	}
}