#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/Headers/TimeDefs.h"

using namespace Core;

namespace Application {
namespace Time {
  struct TimeManager
  {
    TimePoint initialTime;
    TimePoint previousTick;
    TimePoint currentTick;

    TimeManager();

    void Initialize();
    void Start();

    virtual Second Update();

    void End();
    void CleanUp();

    Second GetDeltaTime() const;
    Second GetTimeSpan() const;

  private:
    SteadyClock Clock;
  };
}// namespace Time
}// namespace Application