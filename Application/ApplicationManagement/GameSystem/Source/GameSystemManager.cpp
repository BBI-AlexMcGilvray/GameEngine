#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

namespace Application
{
	namespace GameSystem
	{
		GameSystemManager::GameSystemManager(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
			: RObjectManager(&renderSystem), RenderSystem(renderSystem), InputSystem(inputSystem)
		{

		}

		void GameSystemManager::Initialize()
		{
			RObjectManager.Initialize();

			// move this to the world node
			testCamera = MakeUnique<Rendering::Camera>(1024.0f / 800.0f);
			RenderSystem.SetCamera(testCamera.get());
		}

		void GameSystemManager::Start()
		{
			RObjectManager.Start();
			RenderSystem.AttachRenderObjectManager(&RObjectManager);
		}

		void GameSystemManager::Update(Second dt)
		{
			Scheduler.Update(dt);
			ObjectManager.Update(dt);
		}

		void GameSystemManager::End()
		{
			RenderSystem.DettachRenderObjectManager(&RObjectManager);
			RObjectManager.End();
		}

		void GameSystemManager::CleanUp()
		{
			RObjectManager.CleanUp();
		}
	}
}