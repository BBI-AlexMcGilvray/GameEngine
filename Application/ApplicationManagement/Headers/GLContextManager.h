#pragma once

#include "Dependencies/Includes/GLEW/glew.h"

#include "Dependencies/Includes/SDL2/SDL.h"
#include "Dependencies/Includes//SDL2/SDL_opengl.h"

#include "Core/Headers/PtrDefs.h"

using namespace Core;

namespace Application
{
	struct GLContextManager
	{
		const SDL_GLContext GetContext() const;

		bool Initialize(Ptr<SDL_Window> window);
		void CleanUp();

	private:
		Ptr<SDL_Window> Window = nullptr;
		SDL_GLContext Context;
	};
}