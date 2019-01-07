#include "ApplicationManagement/Headers/ApplicationManager.h"

#include <iostream>

namespace Application
{
	Core::UniquePtr<ApplicationManager> ApplicationManager::Instance = nullptr;

	Core::Ptr<ApplicationManager> ApplicationManager::Application()
	{
		if (Instance == nullptr)
		{
			Instance = MakeUnique<ApplicationManager>(ConstructorTag());
		}

		return Instance.get();
	}

	FixedStepTimeManager& ApplicationManager::AppTime()
	{
		return Application()->Time;
	}

	RenderManager& ApplicationManager::AppRenderSystem()
	{
		return Application()->RenderSystem;
	}

	InputManager& ApplicationManager::AppInputSystem()
	{
		return Application()->InputSystem;
	}

	StateManager& ApplicationManager::AppStateSystem()
	{
		return Application()->StateSystem;
	}

	ApplicationManager::ApplicationManager(ConstructorTag tag)
		: InputSystem(SDL)
		, StateSystem(RenderSystem, InputSystem)
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
		StateSystem.Initialize();

		return true;
	}

	void ApplicationManager::Start()
	{
		SDL.Start();
		Time.Start();
		RenderSystem.Start();
		InputSystem.Start();
		StateSystem.Start();
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
			StateSystem.Update(dt);

			RenderSystem.Update(dt);

			dt = Time.GetAccumulatedTime();
		}

		return true;
	}

	void ApplicationManager::End()
	{
		StateSystem.End();
		InputSystem.End();
		RenderSystem.End();
		Time.End();
		SDL.End();
	}

	void ApplicationManager::CleanUp()
	{
		// possible we want to thread this to make it faster (since saving could be done)
		StateSystem.CleanUp();
		InputSystem.CleanUp();
		RenderSystem.CleanUp();
		Time.CleanUp();
		SDL.CleanUp();
	}
}