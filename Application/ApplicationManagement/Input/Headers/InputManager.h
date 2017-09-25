#pragma once

#include "InputEvent.h"

namespace Input
{
	struct InputManager
	{
		void HandleInput(InputEventBase&& event);

	private:
		void HandleMouseClick(InputEvent<MouseClickedData>* event);
		void HandleMouseMovement(InputEvent<MouseMovedData>* event);
		void HandleMouseWheel(InputEvent<MouseWheeledData>* event);

		void HandleKeyboardInput(InputEvent<KeyboardButtonData>* event);
	};
}