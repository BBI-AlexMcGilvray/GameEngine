#pragma once

#include "Dependencies/glew-2.2.0/include/GL/glew.h"

#include "Dependencies/SDL2-2.0.14/include/SDL.h"
#include "Dependencies/SDL2-2.0.14/include/SDL_opengl.h"

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