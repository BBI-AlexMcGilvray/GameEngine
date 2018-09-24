#pragma once

// this is needed if we want to link to GLEW statically (for some reason...)
#define GLEW_STATIC

#include "Dependencies/Includes/SDL2/SDL.h"
#include "Dependencies/Includes/GLEW/glew.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/CoreDefs.h"

using namespace Core;

namespace Application
{
	struct WindowManager
	{
		String Name;
		int Width;
		int Height;

		WindowManager(String name = "DEFAULT WINDOW", int width = 1024, int height = 800);

		Ptr<SDL_Window> GetWindow() const;

		bool Initialize();
		void CleanUp();

	private:
		Ptr<SDL_Window> Window;
	};
}