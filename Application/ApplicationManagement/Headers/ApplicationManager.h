#pragma once

#include "SDL2Manager.h"
#include "ApplicationManagement/Input/Headers/InputManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"
#include "ApplicationManagement/Time/Headers/TimeManager.h"

using namespace Application::Input;
using namespace Application::Rendering;
using namespace Application::Time;

namespace Application
{
	struct ApplicationManager
	{
		ApplicationManager();

		void Run();

	private:
		// Perhaps make these UniquePtr<>s to the base types so that they can be changed and modified on the fly?
		SDL2Manager SDL;
		InputManager Input; // particularly this one
		RenderManager Renderer;
		FixedStepTimeManager Time;

		bool Initialize();
		void Start();
		bool Update();
		void End();
		void CleanUp();
	};
}