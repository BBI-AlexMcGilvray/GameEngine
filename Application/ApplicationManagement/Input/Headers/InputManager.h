#pragma once

#include "InputEvent.h"

namespace Application
{
	namespace Input
	{
		struct InputManager
		{
			void Initialize();
			void HandleInput(InputEventBase&& event);
			void CleanUp();

		private:
			void HandleMouseClick(InputEvent<MouseClickedData>* event);
			void HandleMouseMovement(InputEvent<MouseMovedData>* event);
			void HandleMouseWheel(InputEvent<MouseWheeledData>* event);

			void HandleKeyboardInput(InputEvent<KeyboardButtonData>* event);
		};
	}
}