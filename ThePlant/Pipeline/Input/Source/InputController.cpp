#pragma once

#include "Pipeline/Input/Headers/InputController.h"

namespace Application {
namespace Input {
    ParentInputReceiver& DefaultInputController::getReceiver()
    {
      return _receiver;
    }

    void DefaultInputController::handleInput(UniquePtr<const InputEventBase> inputEvent) const
    {
      _receiver.handleInput(inputEvent.get());
    }

    void DefaultInputController::addReceiver(Ptr<IInputReceiver> receiver)
    {
      _receiver.addChild(receiver);
    }

    void DefaultInputController::removeReceiver(Ptr<IInputReceiver> receiver)
    {
      _receiver.removeChild(receiver);
    }
}// namespace Input
}// namespace Application