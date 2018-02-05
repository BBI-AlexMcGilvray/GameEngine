#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

namespace Application
{
	namespace GameSystem
	{
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