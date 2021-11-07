#include "Pipeline/Headers/WindowManager.h"

namespace Application {
WindowManager::WindowManager(std::string name, int width, int height)
  : Name(name), Width(width), Height(height)
{
}

Ptr<SDL_Window> WindowManager::GetWindow() const
{
  return _window;
}

bool WindowManager::Initialize()
{
  _window = SDL_CreateWindow(Name.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

  return true;
}

void WindowManager::CleanUp()
{
  if (_window) {
    SDL_DestroyWindow(_window);
  }
}
}// namespace Application