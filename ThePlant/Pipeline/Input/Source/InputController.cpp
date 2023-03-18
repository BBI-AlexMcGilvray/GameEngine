#pragma once

#include "Pipeline/Input/Headers/InputController.h"

namespace Application {
namespace Input {
    ParentInputReceiver& DefaultInputController::getReceiver()
    {
      return _receiver;
    }

    void DefaultInputController::Update(Core::Second deltaTime)
    {
      _receiver.Update(deltaTime);
    }

    void DefaultInputController::handleInput(InputEvent&& inputEvent)
    {
      _receiver.handleInput(inputEvent);
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