#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

namespace Application {
namespace Input {
  /*
		These should take in some action and make a response - which will either consume, or pass along the input).
		*/
  struct InputReceiverBase
  {
    InputReceiverBase();
    ~InputReceiverBase();

    void Initialize();
    void CleanUp();

    void SubscribeTo(Ptr<InputReceiverBase> parent);
    void EndSubscriptionToParent();

    void AddSubscriber(Ptr<InputReceiverBase> receiver);
    void RemoveSubscriber(Ptr<InputReceiverBase> receiver);

    Ptr<const InputReceiverBase> HandleInput(Ptr<const InputEventBase> event) const;

  private:
    Ptr<InputReceiverBase> ParentReceiver = nullptr;
    List<Ptr<InputReceiverBase>> ChildReceivers;

    virtual bool HandlesInput(Ptr<const InputEventBase> event) const = 0;
  };
}// namespace Input
}// namespace Application