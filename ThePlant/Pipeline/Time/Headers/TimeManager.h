#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/Headers/TimeDefs.h"

using namespace Core;

namespace Application {
namespace Time {
  /*
			NOTE:

			PreviousTick = CurrentTick;
			CurrentTick = Clock.now();

			dt = (CurrentTick - PreviousTick);

			every 20 ticks, dt is double the standard value. WHY?
		*/

  struct TimeManager
  {
    TimePoint InitialTime;
    TimePoint PreviousTick;
    TimePoint CurrentTick;

    TimeManager();

    void Initialize();
    void Start();

    virtual Second Update();

    void End();
    void CleanUp();

    Second GetDeltaTime();
    Second GetTimeSpan();

  private:
    SteadyClock Clock;
  };

  /*
			Fixed time step time manager based on: https://gafferongames.com/post/fix_your_timestep/
		*/

  struct FixedStepTimeManager : public TimeManager
  {
    Second MaxStepSize;

    FixedStepTimeManager(Second maxStepSize = Second(167.0f));// 0.0167 is 1 frame if we do 60 frames per second (or 167 milliseconds)

    Second Update() override;

    Second GetAccumulatedTime();

  private:
    Second Accumulator = 0_s;
  };
}// namespace Time
}// namespace Application