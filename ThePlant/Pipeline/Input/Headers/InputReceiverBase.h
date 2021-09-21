#pragma once

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

namespace Application {
namespace Input {
  class IInputReceiver
  {
  public:
    IInputReceiver() = default;
    virtual ~IInputReceiver() = default;

    virtual void initialize() {}
    virtual void cleanUp() {}

    virtual bool handleInput(Ptr<const InputEventBase> event) const = 0;
  };

  /*
		These should take in some action and make a response - which will either consume, or pass along the input).
		*/
  class ParentInputReceiver : public IInputReceiver
  {
  public:
    ParentInputReceiver() = default;
    ~ParentInputReceiver();

    void addChild(Ptr<IInputReceiver> receiver);
    void removeChild(Ptr<IInputReceiver> receiver);

    bool handleInput(Ptr<const InputEventBase> event) const override;

  private:
    std::vector<Ptr<IInputReceiver>> _children;
  };
}// namespace Input
}// namespace Application