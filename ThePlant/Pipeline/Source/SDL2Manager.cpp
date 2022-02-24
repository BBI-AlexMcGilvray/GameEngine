#include "Pipeline/Headers/SDL2Manager.h"

#include "Pipeline/Headers/ApplicationManager.h"

#include <iostream>
#include <stdlib.h>
#include <string>

namespace Application {
bool SDL2Manager::Initialize(ApplicationManager& applicationManager)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    return false;
  }

  if (!MainWindow.Initialize()) {
    CheckSDLError(__LINE__);
    return false;
  }

  // NOTE!! https://stackoverflow.com/questions/47188856/cant-make-opengl-glew-and-sdl2-work-together
  applicationManager.RenderManager().SetOpenGLAttributes();

  if (!MainContext.Initialize(MainWindow.GetWindow())) {
    std::cout << "Failed to initialize GLContent!" << std::endl;
    return false;
  }

#if DEBUG
  // This is just to verify that our attributes are being set to what we want them to be
  applicationManager.RenderManager().VerifyOpenGLAttributes();
#endif

  glewExperimental = true;
  GLenum glewError = glewInit();
  if (glewError != GLEW_OK) {
    std::cout << "Error initializing GLEW! Error: " << glewGetErrorString(glewError) << std::endl;
    return false;
  }

  return true;
}

void SDL2Manager::Start()
{
}

int SDL2Manager::Poll(SDL_Event &event) const
{
  return SDL_PollEvent(&event);
}

void SDL2Manager::End()
{
}

void SDL2Manager::CleanUp()
{
  MainContext.CleanUp();

  MainWindow.CleanUp();

  SDL_Quit();
}

WindowManager &SDL2Manager::GetWindowManager()
{
  return MainWindow;
}

GLContextManager &SDL2Manager::GetContextManager()
{
  return MainContext;
}

void SDL2Manager::CheckSDLError(int line)
{
  std::string error = SDL_GetError();

  if (error != "") {
    std::cout << "SLD Error : " << error << std::endl;

    if (line != -1)
      std::cout << "\nLine : " << line << std::endl;

    SDL_ClearError();
  }
}
}// namespace Application