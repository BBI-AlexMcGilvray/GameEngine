#pragma once

#include "Dependencies/Includes/SDL2/SDL.h"
#include "Dependencies/Includes/GLEW/glew.h"

#include <string>

namespace Application
{
	struct WindowManager
	{
		std::string Name;
		int Width;
		int Height;

		WindowManager(std::string name = "DEFAULT WINDOW", int width = 512, int height = 512);

		SDL_Window* GetWindow() const;

		bool Initialize();
		void CleanUp();

	private:
		SDL_Window* Window;
	};
}