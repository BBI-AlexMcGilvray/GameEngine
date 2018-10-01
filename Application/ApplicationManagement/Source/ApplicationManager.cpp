#include "ApplicationManagement/Headers/ApplicationManager.h"

#include <iostream>

namespace Application
{
	ApplicationManager::ApplicationManager()
		: InputSystem(SDL)
		, GameSystem(RenderSystem, InputSystem)
		, OnQuit([this]()
			{
				Quit = true;
				return false;
			}, InputSystem.Quit)
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
		RenderSystem.SetOpenGLAttributes();

		if (!SDL.Initialize())
		{
			return false;
		}

		Time.Initialize();
		RenderSystem.Initialize(SDL.GetWindowManager());
		InputSystem.Initialize();
		GameSystem.Initialize();

		return true;
	}

	void ApplicationManager::Start()
	{
		SDL.Start();
		Time.Start();
		RenderSystem.Start();
		InputSystem.Start();
		GameSystem.Start();
	}

	bool ApplicationManager::Update()
	{
		InputSystem.Update(); // gets input through SDL

		// game manager update (will update game logic, colliders, game object, renderers)
		auto dt = Time.Update();

		// update everything
		while (dt > 0_s)
		{
			// update everything
			GameSystem.Update(dt);

			RenderSystem.Update(dt);

			dt = Time.GetAccumulatedTime();
		}

		return true;
	}

	void ApplicationManager::End()
	{
		GameSystem.End();
		InputSystem.End();
		RenderSystem.End();
		Time.End();
		SDL.End();
	}

	void ApplicationManager::CleanUp()
	{
		// possible we want to thread this to make it faster (since saving could be done)
		GameSystem.CleanUp();
		InputSystem.CleanUp();
		RenderSystem.CleanUp();
		Time.CleanUp();
		SDL.CleanUp();
	}
}