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
		void Run();

	private:
		SDL2Manager SDL;
		InputManager Input;
		RenderManager Renderer;
		FixedStepTimeManager Time;

		bool Initialize();
		void Start();
		bool Loop();
		void End();
		void CleanUp();
	};
}