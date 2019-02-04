#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

#include "ApplicationManagement/StateSystem/Headers/State.h"

namespace Application
{
	namespace GameSystem
	{
		GameSystemManager::GameSystemManager(Ptr<State> parentState, Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
			: ParentState(parentState)
			, RObjectManager(&renderSystem)
			, RenderSystem(renderSystem)
			, InputSystem(inputSystem)
		{

		}

		void GameSystemManager::Initialize()
		{
			RObjectManager.Initialize();

			RenderSystem.AttachRenderObjectManager(ParentState, &RObjectManager);
		}

		void GameSystemManager::Start()
		{
			RObjectManager.Start();
			RenderSystem.SetActiveState(ParentState);
		}

		void GameSystemManager::Update(Second dt)
		{
			Scheduler.Update(dt);
			ObjectManager.Update(dt);
		}

		void GameSystemManager::End()
		{
			RenderSystem.DettachRenderObjectManager(ParentState);
			RObjectManager.End();
		}

		void GameSystemManager::CleanUp()
		{
			RObjectManager.CleanUp();
		}
	}
}