#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Scheduler.h"

#include "ApplicationManagement/GameSystem/Headers/GameObjectManager.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

using namespace Core;
using namespace Core::Functionality;

namespace Application
{
	namespace GameSystem
	{
		struct GameSystemManager
		{
			SchedulerBase Scheduler;
			GameObjectManager ObjectManager;

			// the game system manager should hold onto the current 'scene' and be able to switch between scenes (in order to load different game states)

			GameSystemManager(Rendering::RenderManager& renderSystem);

			virtual void Initialize();
			virtual void Update(Second dt);
			virtual void CleanUp();

		private:
			// needs the render system to make changes on a game level. Ex: setting dead screen to red and the like
			Rendering::RenderManager& RenderSystem;
		};
	}
}