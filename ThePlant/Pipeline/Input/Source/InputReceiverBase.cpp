#include "Pipeline/Input/Headers/InputReceiverBase.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

namespace Application {
namespace Input {
  ParentInputReceiver::~ParentInputReceiver()
  {
    _children.clear();
  }

  void ParentInputReceiver::addChild(Ptr<IInputReceiver> receiver)
  {
    SCOPED_MEMORY_CATEGORY("Input");
    _children.push_back(receiver);
  }

  void ParentInputReceiver::removeChild(Ptr<IInputReceiver> receiver)
  {
    if (auto location = std::find(_children.begin(), _children.end(), receiver); location != _children.end())
    {
      _children.erase(location);      
    }
  }

  bool ParentInputReceiver::handleInput(Core::Second dt, Ptr<InputEventBase const> event)
  {
    for (auto& child : _children)
    {
      if (child->handleInput(dt, event))
      {
        return true;
      }
    }

    return false;
  }
}// namespace Input
}// namespace Application