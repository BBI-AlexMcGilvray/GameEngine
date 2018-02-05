#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Scheduler.h"

#include "ApplicationManagement/GameSystem/Headers/GameObjectManager.h"

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

			virtual void Initialize();
			virtual void Update(Second dt);
			virtual void CleanUp();
		};
	}
}