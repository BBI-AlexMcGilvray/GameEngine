#pragma once

#include "Dependencies/Includes/GLEW/glew.h"

#include "Dependencies/Includes/SDL2/SDL.h"
#include "Dependencies/Includes//SDL2/SDL_opengl.h"

namespace Application
{
	struct GLContextManager
	{
		const SDL_GLContext GetContext() const;

		bool Initialize(SDL_Window* window);
		void CleanUp();

	private:
		SDL_Window* Window = nullptr;
		SDL_GLContext Context;
	};
}