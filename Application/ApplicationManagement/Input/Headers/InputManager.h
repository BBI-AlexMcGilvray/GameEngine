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

			InputManager(const SDL2Manager& sdl);

			void Initialize();
			void CleanUp();

			virtual void Update();

		private:
			const SDL2Manager& SDL;

			virtual void PollSDL();

			void HandleInput(SharedPtr<InputEventBase> event);

			// the below should probably be moved into having a default 'InputController' struct for each type of input combination (mouse, keyboard, joystick...)
			virtual void HandleMouseClick(SharedPtr<const InputEvent<MouseClickedData>> event);
			virtual void HandleMouseMovement(SharedPtr<const InputEvent<MouseMovedData>> event);
			virtual void HandleMouseWheel(SharedPtr<const InputEvent<MouseWheeledData>> event);

			virtual void HandleKeyboardInput(SharedPtr<const InputEvent<KeyboardButtonData>> event);
		};
	}
}