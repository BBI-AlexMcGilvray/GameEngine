#pragma once

#include "WindowManager.h"
#include "GLContextManager.h"

namespace Application {
struct ApplicationManager;

struct SDL2Manager
{
  SDL2Manager() = default;

  bool Initialize(ApplicationManager& applicationManager);
  void Start();

  int Poll(SDL_Event &event) const;

  void End();
  void CleanUp();

  WindowManager &GetWindowManager();
  GLContextManager &GetContextManager();

private:
  WindowManager MainWindow;
  GLContextManager MainContext;

  void CheckSDLError(int line);
};
}// namespace Application