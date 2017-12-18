#pragma once

#include "Dependencies/Includes/GLEW/glew.h"

#include "Dependencies/Includes/SDL2/SDL.h"
#include "Dependencies/Includes//SDL2/SDL_opengl.h"

namespace Application
{
	struct GLContextManager
	{
		GLContextManager() = delete;
		GLContextManager(SDL_Window* window);

		const SDL_GLContext GetContext() const;

		bool Initialize();
		void CleanUp();

	private:
		SDL_Window* Window = nullptr;
		SDL_GLContext Context;
	};
}