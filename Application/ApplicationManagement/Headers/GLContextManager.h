#pragma once

#include "Dependencies/Includes/glew.h"

#include "Dependencies/Includes/sdl.h"
#include "Dependencies/Includes/sdl_opengl.h"

#include "Core/Headers/PtrDefs.h"

using namespace Core;

namespace Application {
struct GLContextManager
{
  const SDL_GLContext GetContext() const;

  bool Initialize(Ptr<SDL_Window> window);
  void CleanUp();

private:
  Ptr<SDL_Window> Window = nullptr;
  SDL_GLContext Context;
};
}// namespace Application