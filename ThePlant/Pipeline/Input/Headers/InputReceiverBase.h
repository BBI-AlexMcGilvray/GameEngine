#pragma once

#include <vector>

#include "InputEvent.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Input {
  class IInputReceiver
  {
  public:
    IInputReceiver() = default;
    virtual ~IInputReceiver() = default;

    virtual void initialize() {}
    virtual void cleanUp() {}

    virtual bool handleInput(Core::Second dt, Ptr<const InputEventBase> event) = 0;
  };

  /*
		These should take in some action and make a response - which will either consume, or pass along the input).

    Should receivers be higher level and be the point at which 'game actions' are used to translate the input events?
    Or should that be at the controller level?
      Probably the receiver level so that one controller exists per game to support multiple receivers
        Ex: Controller holds receiver for gameplay and UI
            Gameplay and UI then translate the lower-level events to different 'actions' (gameplay and ui would translate those differently)
	*/
  class ParentInputReceiver : public IInputReceiver
  {
  public:
    ParentInputReceiver() = default;
    ~ParentInputReceiver();

    void addChild(Ptr<IInputReceiver> receiver);
    void removeChild(Ptr<IInputReceiver> receiver);

    bool handleInput(Core::Second dt, Ptr<const InputEventBase> event) override;

  private:
    std::vector<Ptr<IInputReceiver>> _children;
  };
}// namespace Input
}// namespace Application