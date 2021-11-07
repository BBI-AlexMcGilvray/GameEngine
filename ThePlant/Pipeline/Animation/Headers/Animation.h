#pragma once

#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Animation {
  class Animation
  {
  public:
    virtual ~Animation() = default;

    virtual void Evaluate(Core::Second time) = 0;
  };
}// namespace Animation
}// namespace Application