#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

namespace Application
{
	namespace GameSystem
	{
		GameSystemManager::GameSystemManager(Rendering::RenderManager& renderSystem)
			: RenderSystem(renderSystem)
		{

		}

		void GameSystemManager::Initialize()
		{

		}

		void GameSystemManager::Update(Second dt)
		{
			Scheduler.Update(dt);
			ObjectManager.Update(dt);
		}

		void GameSystemManager::CleanUp()
		{

		}
	}
}