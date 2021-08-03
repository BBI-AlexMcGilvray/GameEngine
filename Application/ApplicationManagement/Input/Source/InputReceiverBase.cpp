#pragma once

#include "ApplicationManagement/Input/Headers/InputReceiverBase.h"

namespace Application {
namespace Input {
  InputReceiverBase::InputReceiverBase()
  {
  }

  InputReceiverBase::~InputReceiverBase()
  {
    EndSubscriptionToParent();

    for (auto receiver : ChildReceivers) {
      receiver->EndSubscriptionToParent();
    }
  }

  void InputReceiverBase::Initialize()
  {
  }

  void InputReceiverBase::CleanUp()
  {
  }

  void InputReceiverBase::SubscribeTo(Ptr<InputReceiverBase> parent)
  {
    EndSubscriptionToParent();

    ParentReceiver = parent;
    if (ParentReceiver != nullptr) {
      ParentReceiver->AddSubscriber(this);
    }
  }

  void InputReceiverBase::EndSubscriptionToParent()
  {
    if (ParentReceiver != nullptr) {
      ParentReceiver->RemoveSubscriber(this);
      ParentReceiver = nullptr;
    }
  }

  void InputReceiverBase::AddSubscriber(Ptr<InputReceiverBase> receiver)
  {
    Push(ChildReceivers, receiver);
  }

  void InputReceiverBase::RemoveSubscriber(Ptr<InputReceiverBase> receiver)
  {
    Remove(ChildReceivers, receiver);
  }

  Ptr<const InputReceiverBase> InputReceiverBase::HandleInput(Ptr<InputEventBase const> event) const
  {
    if (HandlesInput(event)) {
      return this;
    }

    for (auto receiver : ChildReceivers) {
      if (auto focus = receiver->HandleInput(event)) {
        return focus;
      }
    }

    return nullptr;
  }
}// namespace Input
}// namespace Application