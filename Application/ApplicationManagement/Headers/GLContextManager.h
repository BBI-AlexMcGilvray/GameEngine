#pragma once

#include "../../Dependencies/Includes/SDL2/SDL.h"
#include "../../Dependencies/Includes/GLEW/glew.h"

namespace Application
{
	struct GLContextManager
	{
		GLContextManager() = default;
		GLContextManager(SDL_Window* window);

		const SDL_GLContext GetContext() const;

		void CleanUp();

	private:
		SDL_GLContext Context;
	};
}