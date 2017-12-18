#include "ApplicationManagement/Headers/WindowManager.h"

namespace Application
{
	WindowManager::WindowManager(std::string name, int width, int height)
		: Name(name), Width(width), Height(height)
	{

	}

	SDL_Window* WindowManager::GetWindow() const
	{
		return Window;
	}

	bool WindowManager::Initialize()
	{
		Window = SDL_CreateWindow(Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_OPENGL);

		return true;
	}

	void WindowManager::CleanUp()
	{
		SDL_DestroyWindow(Window);
	}
}