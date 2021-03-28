#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

#include "ApplicationManagement/StateSystem/Headers/State.h"

#include "ApplicationManagement/Rendering/Headers/SingleCameraManager.h"

namespace Application
{
	namespace GameSystem
	{
		GameSystemManager::GameSystemManager(Ptr<State> parentState, Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
			: ParentState(parentState)
			, RObjectManager(&renderSystem)
			, MaterialManager(&renderSystem)
			, _cameraManager(MakeUnique<Rendering::SingleCameraManager>(&renderSystem))
			, RenderSystem(renderSystem)
			, InputSystem(inputSystem)
		{

		}

		void GameSystemManager::Initialize()
		{
			RObjectManager.Initialize();
			MaterialManager.Initialize();

			RenderSystem.AttachRenderObjectManager(ParentState, &RObjectManager);
			RenderSystem.AttachMaterialManager(ParentState, &MaterialManager);
			RenderSystem.AttachCameraManager(ParentState, _cameraManager.get());
		}

		void GameSystemManager::Start()
		{
			RObjectManager.Start();
			MaterialManager.Start();
			_cameraManager->Start();

			RenderSystem.SetActiveState(ParentState);
		}

		void GameSystemManager::Update(Second dt)
		{
			Scheduler.Update(dt);
			ObjectManager.Update(dt);
		}

		void GameSystemManager::End()
		{
			RenderSystem.DettachMaterialManager(ParentState);
			RenderSystem.DettachRenderObjectManager(ParentState);
			RenderSystem.DettachCameraManager(ParentState);

			RObjectManager.End();
			MaterialManager.End();
			_cameraManager->End();
		}

		void GameSystemManager::CleanUp()
		{
			MaterialManager.CleanUp();
			RObjectManager.CleanUp();
			_cameraManager->CleanUp();
		}
	}
}