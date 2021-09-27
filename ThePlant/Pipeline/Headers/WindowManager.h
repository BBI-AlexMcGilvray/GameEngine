#pragma once

#include "Dependencies/Includes/sdl.h"
#include "Dependencies/Includes/glew.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/CoreDefs.h"

using namespace Core;

namespace Application {
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
  Ptr<SDL_Window> _window;
};
}// namespace Application