#include "ApplicationManagement/StateSystem/Headers/State.h"

namespace Application
{
	State::State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
		: GameSystem(renderSystem, inputSystem)
	{

	}

	void State::Initialize()
	{
		GameSystem.Initialize();
	}

	void State::Start()
	{
		GameSystem.Start();
	}

	void State::Update(Second dt)
	{
		Hierarchy.Update(dt);
		GameSystem.Update(dt);
	}

	void State::End()
	{
		GameSystem.End();
	}

	void State::CleanUp()
	{
		GameSystem.CleanUp();
	}
}