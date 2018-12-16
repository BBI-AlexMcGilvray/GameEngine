#include "ApplicationManagement/StateSystem/Headers/StateManager.h"

namespace Application
{
	StateManager::StateManager(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
		: RenderSystem(renderSystem), InputSystem(inputSystem)
	{

	}

	void StateManager::Initialize()
	{
		// knowing what state to push first can be in a config file, or based on an instantation of a specific templated type
		PushState();
		ActiveState()->Initialize();

		CurrentState = SystemState::Initialized;
	}

	void StateManager::Start()
	{
		for (int i = 0; i < States.size(); i++)
		{
			States[i]->Start();
		}

		CurrentState = SystemState::Started;
	}

	void StateManager::Update(Second dt)
	{
		if (CurrentState == SystemState::Transitioning)
		{
			// Transition(dt);
		}

		ActiveState()->Update(dt);
	}

	void StateManager::End()
	{
		for (int i = 0; i < States.size(); i++)
		{
			States[i]->End();
		}

		CurrentState = SystemState::Ended;
	}

	void StateManager::CleanUp()
	{
		for (int i = 0; i < States.size(); i++)
		{
			States[i]->CleanUp();
		}

		CurrentState = SystemState::Clean;
	}

	void StateManager::PushState()
	{
		Push(States, MakeUnique<State>(RenderSystem, InputSystem));
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
		if (States.size() < 1)
		{
			return nullptr;
		}

		return States[States.size() - 1].get();
	}
}