#include "ApplicationManagement/Headers/ApplicationManager.h"

#include <iostream>

namespace Application
{
	void ApplicationManager::Run()
	{
		if (!Initialize())
		{
			std::cout << "Failed to initialize application" << std::endl;
			return;
		}

		Start();

		while (Update())
		{}

		End();
		CleanUp();
	}

	bool ApplicationManager::Initialize()
	{
		// possible we want to thread this to make it faster

		// NOTE!! https://stackoverflow.com/questions/47188856/cant-make-opengl-glew-and-sdl2-work-together
		Renderer.SetOpenGLAttributes();

		if (!SDL.Initialize())
		{
			return false;
		}

		Input.Initialize();
		Renderer.Initialize(SDL.GetWindowManager());

		return true;
	}

	void ApplicationManager::Start()
	{

	}

	bool ApplicationManager::Update()
	{
		// this loop should probably be in the InputManager
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
		auto dt = Time.Update();
		// update everything

		dt = Time.GetAccumulatedTime();
		while (dt > 0_s)
		{
			// update everything
			Renderer.Update(dt);

			dt = Time.GetAccumulatedTime();
		}

		return true;
	}

	void ApplicationManager::End()
	{

	}

	void ApplicationManager::CleanUp()
	{
		// possible we want to thread this to make it faster (since saving could be done)
		Renderer.CleanUp();
		Input.CleanUp();
		SDL.CleanUp();
	}
}