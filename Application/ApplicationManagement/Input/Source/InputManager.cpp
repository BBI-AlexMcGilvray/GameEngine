#include "ApplicationManagement/Input/Headers/InputManager.h"

namespace Application
{
	namespace Input
	{
		InputManager::InputManager(const SDL2Manager& sdl)
			: SDL(sdl)
		{

		}

		void InputManager::Initialize()
		{
			// create controller logic mapping
			// have controller logic mapping initialize
		}

		void InputManager::HandleInput(SharedPtr<InputEventBase> event)
		{
			switch (event->GetInputEventType())
			{
			case InputEventType::Undetermined:
			{
				return;
			}
			case InputEventType::MouseClickedEvent:
			{
				return HandleMouseClick(static_pointer_cast<InputEvent<MouseClickedData>>(event));
			}
			case InputEventType::MouseMovedEvent:
			{
				return HandleMouseMovement(static_pointer_cast<InputEvent<MouseMovedData>>(event));
			}
			case InputEventType::MouseWheelEvent:
			{
				return HandleMouseWheel(static_pointer_cast<InputEvent<MouseWheeledData>>(event));
			}
			case InputEventType::KeyboardEvent:
			{
				return HandleKeyboardInput(static_pointer_cast<InputEvent<KeyboardButtonData>>(event));
			}
			}
		}

		void InputManager::CleanUp()
		{
			// have controller mapping save any changed made during gameplay (?)
		}

		void InputManager::Update()
		{
			PollSDL();
		}

		void InputManager::PollSDL()
		{
			// this loop should probably be in the InputManager
			SDL_Event event;
			while (SDL.Poll(event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
				{
					// send of quit event
					Quit();
				}
				case SDL_KEYDOWN:
				{
					HandleInput(MakeShared<InputEvent<KeyboardButtonData>>(InputEventType::KeyboardEvent, event.key.timestamp, event.key.windowID, GetKeyboardButton(event.key.keysym.sym), GetButtonState(event.key.type)));
				}
				}
			}
		}

		void InputManager::HandleMouseClick(SharedPtr<const InputEvent<MouseClickedData>> event)
		{

		}

		void InputManager::HandleMouseMovement(SharedPtr<const InputEvent<MouseMovedData>> event)
		{

		}

		void InputManager::HandleMouseWheel(SharedPtr<const InputEvent<MouseWheeledData>> event)
		{

		}

		void InputManager::HandleKeyboardInput(SharedPtr<const InputEvent<KeyboardButtonData>> event)
		{

		}
	}
}