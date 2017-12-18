#include "ApplicationManagement/Headers/GLContextManager.h"

#include <iostream>

namespace Application
{
	GLContextManager::GLContextManager(SDL_Window* window)
		: Window(window)
	{

	}

	const SDL_GLContext GLContextManager::GetContext() const
	{
		return Context;
	}

	bool GLContextManager::Initialize()
	{
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
		SDL_GL_DeleteContext(Context);
	}
}