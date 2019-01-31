#include "ApplicationManagement/StateSystem/Headers/State.h"

namespace Application
{
	State::State(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
		: Hierarchy(Core::MakeUnique<Geometric::World>(this))
		, GameSystem(this, renderSystem, inputSystem)
	{

	}

	void State::Initialize()
	{
		Hierarchy->Initialize();
		GameSystem.Initialize();
	}

	void State::Start()
	{
		// NEED TO SORT OUT THE ORDERING - start is when content start is called, systems should be set up by then
		// and what about pre-loading other states? that needs to work in here too
		Hierarchy->Start();
		GameSystem.Start();
	}

	void State::Update(Second dt)
	{
		Hierarchy->Update(dt);
		GameSystem.Update(dt);
	}

	void State::End()
	{
		Hierarchy->End();
		GameSystem.End();
	}

	void State::CleanUp()
	{
		Hierarchy->CleanUp();
		GameSystem.CleanUp();
	}
}