#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"

#include "ApplicationManagement/Input/Headers/InputReceiverBase.h"

namespace Application {
namespace Input {
  /*
		These controllers should take the input and map it to a specific action given some data.

		Then, that action is passed down to the receivers (starting with the focus, and moving on if it does not consume the input).
		*/
  struct InputController
  {
    InputController() = default;

    void Initialize();
    void CleanUp();

    void SetParentReceiver(Ptr<const InputReceiverBase> parentReceiver);
    void ClearFocus();

    void HandleInput(UniquePtr<const InputEventBase> inputEvent);

  private:
    Ptr<const InputReceiverBase> FocusedReceiver = nullptr;
    Ptr<const InputReceiverBase> Receiver = nullptr;

    void SetFocus(Ptr<const InputReceiverBase> focus);
  };
}// namespace Input
}// namespace Application