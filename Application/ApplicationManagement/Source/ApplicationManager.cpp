#include "ApplicationManagement/Headers/ApplicationManager.h"

#include <iostream>

namespace Application
{
	ApplicationManager::ApplicationManager()
		: Input(&SDL)
		, OnQuit([this]()
			{
				Quit = true;
				return false;
			}, Input.Quit)
	{

	}

	void ApplicationManager::Run()
	{
		if (!Initialize())
		{
			std::cout << "Failed to initialize application" << std::endl;
			return;
		}

		Start();

		while (!Quit && Update())
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

		GameSystem.Initialize();
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
		Input.Update();

		// game manager update (will update game logic, colliders, game object, renderers)
		auto dt = Time.Update();

		// update everything
		while (dt > 0_s)
		{
			// update everything
			GameSystem.Update(dt);

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
		GameSystem.CleanUp();
		SDL.CleanUp();
	}
}