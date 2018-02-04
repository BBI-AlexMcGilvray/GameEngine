#pragma once

#include "InputEvent.h"

#include "ApplicationManagement/Headers/SDL2Manager.h"

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

			InputManager(Ptr<const SDL2Manager> sdl);

			void Initialize();
			void HandleInput(InputEventBase&& event);
			void CleanUp();

			virtual bool Update();

		private:
			Ptr<const SDL2Manager> SDL;

			virtual bool PollSDL();

			virtual void HandleMouseClick(InputEvent<MouseClickedData>* event);
			virtual void HandleMouseMovement(InputEvent<MouseMovedData>* event);
			virtual void HandleMouseWheel(InputEvent<MouseWheeledData>* event);

			virtual void HandleKeyboardInput(InputEvent<KeyboardButtonData>* event);
		};
	}
}