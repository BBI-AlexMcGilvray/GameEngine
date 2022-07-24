#pragma once

#include "InputEvent.h"

#include "Pipeline/Headers/SDL2Manager.h"

#include "Pipeline/Input/Headers/InputController.h"
#include "Pipeline/Input/Headers/InputEvent.h"
#include "Pipeline/Input/Headers/InputState.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Core::Functionality;

namespace Application {
namespace Input {
  /*
  Notes:
  - Apparently this must be called on the same thread that initializes the video system
  - Even though we then move our rendering context to a different thread, seems to work fine
  - Maybe there is a way to make sure IMGUI intercepts certain events (ex: scroll wheel)
  - Probably don't need to have this update on a separate thread (it should be light, and we want to make sure that the current data is valid - not accidentally lose stuff)
    - if this was triple-buffered, we'd likely lose events
    - as it stands, SDL polls the system on it's own, then Poll_Events called to sdl polls IT'S events, so we won't lose inputs as-is
  */
  struct InputManager
  {
    Event<> Quit;

    InputManager(const SDL2Manager &sdl);

    Ptr<IInputController> operator->();

    void initialize();
    void start();

    template <typename T, typename ...Args>
    void setInputController(Args... args)
    {
			SCOPED_MEMORY_CATEGORY("Input");
      setInputController(MakeUnique<T>(std::forward<Args>(args)...));
    }
    void setInputController(UniquePtr<IInputController> controller);
    void update(Core::Second deltaTime);

    void end();
    void cleanUp();

    template <typename STATE_TYPE, typename TRACKER_INPUT>
    const STATE_TYPE& GetState(const TRACKER_INPUT& input) const
    {
      return _state.GetState<STATE_TYPE>(input);
    }

  private:
    const SDL2Manager &_SDL;
    UniquePtr<IInputController> _controller;
    MouseAndKeyboardState _state;

    void _PollSDL(Core::Second dt);
    void _HandleEvent(SDL_Event&&);
    void _UpdateState(const InputEventBase& event);
  };

  // the above should be an InputControllerManager
  // then we need the InputManager to have an InputControllerManager and an InputState
  //    - update polls events + updates the input state, THEN we iterate over the controllers and update them
  //    * do we need controllers? or just receivers... go over the logic split again
}// namespace Input
}// namespace Application