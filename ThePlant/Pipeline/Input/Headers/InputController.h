#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"

#include "Pipeline/Input/Headers/InputReceiverBase.h"

namespace Application {
namespace Input {
  /*
		These controllers should take the input and map it to a specific action given some data.

		Then, that action is passed down to the receivers (starting with the focus, and moving on if it does not consume the input).
		*/
  class IInputController
  {
  public:
    IInputController() = default;
    virtual ~IInputController() = default;

    virtual void initialize() {}
    virtual void cleanUp() {}

    virtual void handleInput(UniquePtr<const InputEventBase> inputEvent) const = 0;

    // all controllers should be able to add/remove receivers
    // the receivers live elsewhere though, should be non_null_ptrs
    virtual void addReceiver(Ptr<IInputReceiver> receiver) = 0;
    virtual void removeReceiver(Ptr<IInputReceiver> receiver) = 0;
  };

  class DefaultInputController : public IInputController
  {
  public:
    ParentInputReceiver& getReceiver();

    void handleInput(UniquePtr<const InputEventBase> inputEvent) const override;
    
    void addReceiver(Ptr<IInputReceiver> receiver) override;
    void removeReceiver(Ptr<IInputReceiver> receiver) override;

  private:
    ParentInputReceiver _receiver;
  };
}// namespace Input
}// namespace Application