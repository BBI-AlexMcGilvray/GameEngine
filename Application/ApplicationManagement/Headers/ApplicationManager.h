#pragma once

#include "SDL2Manager.h"

#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"
#include "ApplicationManagement/Input/Headers/InputManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"
#include "ApplicationManagement/Time/Headers/TimeManager.h"

#include "Core/Functionality/Headers/Event.h"

using namespace Application::GameSystem;
using namespace Application::Input;
using namespace Application::Rendering;
using namespace Application::Time;

using namespace Core::Functionality;

namespace Application
{
	struct ApplicationManager
	{
		ApplicationManager();

		void Run();

	private:
		// Note: the below are in an order such that they should only _possibly_ know about what is above them (as it would need to be for constructors...)
		SDL2Manager SDL;
		FixedStepTimeManager Time;
		RenderManager RenderSystem;
		InputManager Input;
		GameSystemManager GameSystem;

		Delegate<> OnQuit;
		bool Quit = false;

		bool Initialize();
		void Start();
		bool Update();
		void End();
		void CleanUp();
	};
}