#pragma once

#include "WindowManager.h"
#include "GLContextManager.h"

namespace Application
{
	struct SDL2Manager
	{
		SDL2Manager() = default;

		bool Initialize();
		void Start();

		int Poll(SDL_Event& event) const;

		void End();
		void CleanUp();

		WindowManager& GetWindowManager();
		GLContextManager& GetContextManager();

	private:
		WindowManager MainWindow;
		GLContextManager MainContext;

		void CheckSDLError(int line);
	};
}