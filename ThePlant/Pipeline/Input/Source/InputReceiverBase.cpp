#pragma once

#include "Pipeline/Input/Headers/InputReceiverBase.h"

namespace Application {
namespace Input {
  ParentInputReceiver::~ParentInputReceiver()
  {
    _children.clear();
  }

  void ParentInputReceiver::addChild(Ptr<IInputReceiver> receiver)
  {
    _children.push_back(receiver);
  }

  void ParentInputReceiver::removeChild(Ptr<IInputReceiver> receiver)
  {
    if (auto location = std::find(_children.begin(), _children.end(), receiver); location != _children.end())
    {
      _children.erase(location);      
    }
  }

  bool ParentInputReceiver::handleInput(Ptr<InputEventBase const> event) const
  {
    for (auto& child : _children)
    {
      if (child->handleInput(event))
      {
        return true;
      }
    }

    return false;
  }
}// namespace Input
}// namespace Application