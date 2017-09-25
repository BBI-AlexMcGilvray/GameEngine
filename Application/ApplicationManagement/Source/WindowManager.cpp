#include "../Headers/WindowManager.h"

namespace Application
{
	WindowManager::WindowManager(std::string windowName, int width, int height)
	{
		Window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	}

	SDL_Window* WindowManager::GetWindow() const
	{
		return Window;
	}

	void WindowManager::CleanUp()
	{
		SDL_DestroyWindow(Window);
	}
}