#pragma once

#include "InputEvent.h"

#include "ApplicationManagement/Headers/SDL2Manager.h"

#include "ApplicationManagement/Input/Headers/InputController.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Core::Functionality;

namespace Application
{
	namespace Input
	{
		struct InputManager
		{
			Event<> Quit;

			InputManager(const SDL2Manager& sdl);

			void Initialize();
			void Start();

			void Update();

			void End();
			void CleanUp();

		private:
			const SDL2Manager& SDL;
			UniquePtr<InputController> Controller;

			virtual void PollSDL();
		};
	}
}