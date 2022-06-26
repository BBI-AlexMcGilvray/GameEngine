#include "Pipeline\Time\Headers\TimeSystem.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application {
namespace Time {
  TimeSystem::TimeSystem(const TimeSettings& timeSettings)
  : _timeSettings(timeSettings)
  {
  }

  const TimeSettings& TimeSystem::GetTimeSettings() const
  {
    return _timeSettings;
  }

  void TimeSystem::SetFutureTimeSettings(const TimeSettings& futureSettings)
  {
    VERIFY(!_futureSettingsSet);
    _futureSettingsSet = true;
    _futureSettings = futureSettings;
  }

  void TimeSystem::Initialize()
  {
    _timeManager.Initialize();
    _stepPreviousTick = _timeManager.initialTime;
    _stepCurrentTick = _timeManager.initialTime;

    _futureSettingsSet = false;
  }

  void TimeSystem::Start()
  {
    _timeManager.Start();
  }

  void TimeSystem::Update()
  {
    _ApplyFutureSettings();

    _timeManager.Update();
    _stepPreviousTick = _timeManager.previousTick;
  }

  bool TimeSystem::TakeFixedStep()
  {
    if (_timeSettings.fixedTimeStep && _stepCurrentTick < _timeManager.currentTick)
    {
      _ApplyFutureSettings();
      
      _stepPreviousTick = _stepCurrentTick;
      _stepCurrentTick = std::min(_stepPreviousTick + Second(_timeSettings.maxTimeStep), _timeManager.currentTick);
      return true;
    }

    return false;
  }

  // affected by settings
  Second TimeSystem::GetDeltaTime() const
  {
    if (!_timeSettings.fixedTimeStep)
    {
      return GetRawDeltaTime() * _timeSettings.timeScale;
    }

    return (_stepCurrentTick - _stepPreviousTick) * _timeSettings.timeScale;
  }
  
  // not affected by settings
  Second TimeSystem::GetRawDeltaTime() const
  {
    return _timeManager.GetDeltaTime();
  }

  Second TimeSystem::GetRawTimeSpan() const
  {
    return _timeManager.GetTimeSpan();
  }

  void TimeSystem::End()
  {
    _timeManager.End();
  }

  void TimeSystem::CleanUp()
  {
    _timeManager.CleanUp();
  }

  void TimeSystem::_ApplyFutureSettings()
  {
    if (_futureSettingsSet)
    {
      _timeSettings = _futureSettings;
    }
    _futureSettingsSet = false;
  }
}// namespace Time
}// namespace Application