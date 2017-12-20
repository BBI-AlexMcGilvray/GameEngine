#include "ApplicationManagement/Headers/GLContextManager.h"

#include <iostream>

namespace Application
{
	const SDL_GLContext GLContextManager::GetContext() const
	{
		return Context;
	}

	bool GLContextManager::Initialize(Ptr<SDL_Window> window)
	{
		Window = window;

		Context = SDL_GL_CreateContext(Window);

		if (!Context)
		{
			std::cout << "Failed to create OpenGL context! SDL Error: " << SDL_GetError() << std::endl;
			return false;
		}

		return true;
	}

	void GLContextManager::CleanUp()
	{
		if (Context)
		{
			SDL_GL_DeleteContext(Context);
		}
	}
}