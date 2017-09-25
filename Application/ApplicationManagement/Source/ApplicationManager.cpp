#include "../Headers/ApplicationManager.h"

namespace Application
{
	void ApplicationManager::Run()
	{
		Initialize();
		Start();

		while (Loop())
		{}

		End();
		CleanUp();
	}

	bool ApplicationManager::Initialize()
	{
		if (!SDL.Initialize())
		{
			return false;
		}

		return true;
	}

	void ApplicationManager::Start()
	{

	}

	bool ApplicationManager::Loop()
	{
		SDL_Event event;
		while (SDL.Poll(event))
		{
			switch (event.type)
			{
				case SDL_QUIT:
				{
					return false;
				}
				case SDL_KEYDOWN:
				{
					Input.HandleInput(InputEvent<KeyboardButtonData>(InputEventType::KeyboardEvent, event.key.timestamp, event.key.windowID, GetKeyboardButton(event.key.keysym.sym), GetButtonState(event.key.type)));
				}
			}
		}

		// game manager update (will update game logic, colliders, game object, renderers)

		return true;
	}

	void ApplicationManager::End()
	{

	}

	void ApplicationManager::CleanUp()
	{
		SDL.CleanUp();
	}
}