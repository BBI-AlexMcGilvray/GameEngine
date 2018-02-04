#include "ApplicationManagement/Input/Headers/InputManager.h"

namespace Application
{
	namespace Input
	{
		InputManager::InputManager(Ptr<const SDL2Manager> sdl)
			: SDL(sdl)
		{

		}

		void InputManager::Initialize()
		{
			// create controller logic mapping
			// have controller logic mapping initialize
		}

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

		void InputManager::CleanUp()
		{
			// have controller mapping save any changed made during gameplay (?)
		}

		bool InputManager::Update()
		{
			return PollSDL();
		}

		bool InputManager::PollSDL()
		{
			// this loop should probably be in the InputManager
			SDL_Event event;
			while (SDL->Poll(event))
			{
				switch (event.type)
				{
				case SDL_QUIT:
				{
					// send of quit event
					Quit();
					return false;
				}
				case SDL_KEYDOWN:
				{
					HandleInput(InputEvent<KeyboardButtonData>(InputEventType::KeyboardEvent, event.key.timestamp, event.key.windowID, GetKeyboardButton(event.key.keysym.sym), GetButtonState(event.key.type)));
				}
				}
			}
			
			return true;
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
}