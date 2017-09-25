#include "../Headers/SDL2Manager.h"

#include <iostream>
#include <stdlib.h>
#include <string>

namespace Application
{
	bool SDL2Manager::Initialize()
	{
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			return false;
		}

		MainWindow = WindowManager();
	
		if (!MainWindow.GetWindow())
		{
			CheckSDLError(__LINE__);
			return false;
		}

		MainContext = GLContextManager(MainWindow.GetWindow());

		return true;
	}

	int SDL2Manager::Poll(SDL_Event& event)
	{
		return SDL_PollEvent(&event);
	}

	void SDL2Manager::CleanUp()
	{
		MainContext.CleanUp();

		MainWindow.CleanUp();

		SDL_Quit();
	}

	WindowManager& SDL2Manager::GetWindowManager()
	{
		return MainWindow;
	}

	GLContextManager& SDL2Manager::GetContextManager()
	{
		return MainContext;
	}

	void SDL2Manager::CheckSDLError(int line)
	{
		std::string error = SDL_GetError();

		if (error != "")
		{
			std::cout << "SLD Error : " << error << std::endl;

			if (line != -1)
				std::cout << "\nLine : " << line << std::endl;

			SDL_ClearError();
		}
	}
}