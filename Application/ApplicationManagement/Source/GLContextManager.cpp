#include "ApplicationManagement/Headers/GLContextManager.h"

namespace Application
{
	GLContextManager::GLContextManager(SDL_Window* window)
	{
		Context = SDL_GL_CreateContext(window);
	}

	const SDL_GLContext GLContextManager::GetContext() const
	{
		return Context;
	}

	void GLContextManager::CleanUp()
	{
		SDL_GL_DeleteContext(Context);
	}
}