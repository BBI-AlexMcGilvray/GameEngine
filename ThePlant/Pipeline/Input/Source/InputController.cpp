#pragma once

#include "Pipeline/Input/Headers/InputController.h"

namespace Application {
namespace Input {
    void DefaultInputController::handleInput(UniquePtr<const InputEventBase> inputEvent) const
    {
      _receiver.handleInput(inputEvent.get());
    }

    ParentInputReceiver& DefaultInputController::getReceiver()
    {
      return _receiver;
    }
}// namespace Input
}// namespace Application