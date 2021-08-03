#include "ApplicationManagement/Headers/WindowManager.h"

namespace Application {
WindowManager::WindowManager(String name, int width, int height)
  : Name(name), Width(width), Height(height)
{
}

Ptr<SDL_Window> WindowManager::GetWindow() const
{
  return Window;
}

bool WindowManager::Initialize()
{
  Window = SDL_CreateWindow(Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  return true;
}

void WindowManager::CleanUp()
{
  if (Window) {
    SDL_DestroyWindow(Window);
  }
}
}// namespace Application