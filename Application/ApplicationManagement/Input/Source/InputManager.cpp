#include "../Headers/InputManager.h"

namespace Input
{
	void InputManager::HandleInput(InputEventBase&& event)
	{
		switch (event.GetInputEventType())
		{
			case InputEventType::Undetermined:
			{
				return;
			}
			case InputEventType::MouseClickedEvent:
			{
				return HandleMouseClick(static_cast<InputEvent<MouseClickedData>*>(&event));
			}
			case InputEventType::MouseMovedEvent:
			{
				return HandleMouseMovement(static_cast<InputEvent<MouseMovedData>*>(&event));
			}
			case InputEventType::MouseWheelEvent:
			{
				return HandleMouseWheel(static_cast<InputEvent<MouseWheeledData>*>(&event));
			}
			case InputEventType::KeyboardEvent:
			{
				return HandleKeyboardInput(static_cast<InputEvent<KeyboardButtonData>*>(&event));
			}
		}
	}

	void InputManager::HandleMouseClick(InputEvent<MouseClickedData>* event)
	{

	}

	void InputManager::HandleMouseMovement(InputEvent<MouseMovedData>* event)
	{

	}

	void InputManager::HandleMouseWheel(InputEvent<MouseWheeledData>* event)
	{

	}

	void InputManager::HandleKeyboardInput(InputEvent<KeyboardButtonData>* event)
	{

	}
}