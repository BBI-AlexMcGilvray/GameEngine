#pragma once

#include "WindowManager.h"
#include "GLContextManager.h"

namespace Application
{
	struct SDL2Manager
	{
		bool Initialize();
		int Poll(SDL_Event& event);
		void CleanUp();

		WindowManager& GetWindowManager();
		GLContextManager& GetContextManager();

	private:
		WindowManager MainWindow;
		GLContextManager MainContext;

		void CheckSDLError(int line);
	};
}