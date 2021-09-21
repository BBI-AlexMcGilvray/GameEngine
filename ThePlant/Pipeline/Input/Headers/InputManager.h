#pragma once

#include "InputEvent.h"

#include "Pipeline/Headers/SDL2Manager.h"

#include "Pipeline/Input/Headers/InputController.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Core::Functionality;

namespace Application {
namespace Input {
  struct InputManager
  {
    Event<> Quit;

    InputManager(const SDL2Manager &sdl);

    void initialize();
    void start();

    template <typename T, typename ...Args>
    void setInputController(Args... args)
    {
      setInputController(std::make_unique<T>(std::forward<Args>(args)...));
    }
    void setInputController(UniquePtr<IInputController> controller);
    void update();

    void end();
    void cleanUp();

  private:
    const SDL2Manager &_SDL;
    UniquePtr<IInputController> _controller;

    virtual void _pollSDL();
  };
}// namespace Input
}// namespace Application