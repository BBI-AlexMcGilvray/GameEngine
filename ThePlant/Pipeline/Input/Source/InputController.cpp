#pragma once

#include "Pipeline/Input/Headers/InputController.h"

namespace Application {
namespace Input {
  void InputController::Initialize()
  {
  }

  void InputController::CleanUp()
  {
  }

  void InputController::SetParentReceiver(Ptr<const InputReceiverBase> parentReceiver)
  {
    if (parentReceiver == Receiver) {
      return;
    }

    Receiver = parentReceiver;
    FocusedReceiver = nullptr;
  }

  void InputController::ClearFocus()
  {
    SetFocus(nullptr);
  }

  void InputController::HandleInput(UniquePtr<const InputEventBase> inputEvent)
  {
    if (Receiver == nullptr) {
      return;
    }

    if (FocusedReceiver != nullptr && FocusedReceiver->HandleInput(inputEvent.get())) {
      return;
    }

    SetFocus(Receiver->HandleInput(inputEvent.get()));
  }

  void InputController::SetFocus(Ptr<const InputReceiverBase> focusedReceiver)
  {
    FocusedReceiver = focusedReceiver;
  }
}// namespace Input
}// namespace Application