#pragma once

#include "Dependencies/Includes/SDL2/SDL.h"
#include "Dependencies/Includes/GLEW/glew.h"

#include <string>

namespace Application
{
	struct WindowManager
	{
		WindowManager(std::string windowName = "DEFAULT WINDOW", int width = 512, int height = 512);

		SDL_Window* GetWindow() const;

		void CleanUp();

	private:
		SDL_Window* Window;
	};
}