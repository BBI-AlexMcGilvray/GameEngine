#pragma once

#include "Core/Headers/CoreDefs.h"

#include "Core/Headers/TimeDefs.h"
#include "Pipeline/Time/Headers/TimeManager.h"
#include "Pipeline/Time/Headers/TimeSettings.h"

using namespace Core;

namespace Application {
namespace Time {
  struct TimeSystem
  {
    TimeSystem() = default;
    TimeSystem(const TimeSettings& timeSettings);

    const TimeSettings& GetTimeSettings() const;
    void SetFutureTimeSettings(const TimeSettings& futureSettings); // sets the time settings starting after this frame

    void Initialize();
    void Start();

    // update, then take steps until completed
    void Update();
    // true if using fixed steps and steps remain
    // false otherwise
    bool TakeFixedStep();

    // affected by settings
    Second GetDeltaTime() const;

    // not affected by settings
    Second GetRawDeltaTime() const;
    Second GetRawTimeSpan() const;

    void End();
    void CleanUp();

  private:
    TimeSettings _timeSettings;
    TimeManager _timeManager;

    TimePoint _stepPreviousTick;
    TimePoint _stepCurrentTick;

    bool _futureSettingsSet;
    TimeSettings _futureSettings;

    void _ApplyFutureSettings();
  };
}// namespace Time
}// namespace Application