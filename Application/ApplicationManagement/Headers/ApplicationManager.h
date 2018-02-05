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
		// Perhaps make these UniquePtr<>s to the base types so that they can be changed and modified on the fly?
		SDL2Manager SDL;
		GameSystemManager GameSystem;
		InputManager Input; // particularly this one
		RenderManager Renderer;
		FixedStepTimeManager Time;

		Delegate<> OnQuit;
		bool Quit = false;

		bool Initialize();
		void Start();
		bool Update();
		void End();
		void CleanUp();
	};
}