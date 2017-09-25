#pragma once

#include "SDL2Manager.h"
#include "ApplicationManagement/Input/Headers/InputManager.h"

using namespace Input;

namespace Application
{
	struct ApplicationManager
	{
		void Run();

	private:
		SDL2Manager SDL;
		InputManager Input;

		bool Initialize();
		void Start();
		bool Loop();
		void End();
		void CleanUp();
	};
}