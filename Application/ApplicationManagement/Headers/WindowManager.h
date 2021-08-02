#pragma once

// this is needed if we want to link to GLEW statically (for some reason...)
#define GLEW_STATIC

#include "Dependencies/SDL2-2.0.14/include/SDL.h"
#include "Dependencies/glew-2.2.0/include/GL/glew.h"

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