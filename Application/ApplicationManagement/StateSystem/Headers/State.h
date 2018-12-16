#pragma once

#include "Core/Headers/TimeDefs.h"

#include "ApplicationManagement/Geometric/Headers/Node.h"
#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

using namespace Core;

namespace Application
{
	struct State
	{
		State();
		// State(AssetName<State> state);
		// State(AssetData<State> state);

		void Initialize();
		void Update(Second dt);
		void CleanUp();

	private:
		Geometric::Node Hierarchy;
		GameSystem::GameSystemManager GameSystem;
	};
}