#include "Pipeline\Time\Headers\TimeManager.h"

namespace Application {
namespace Time {
  TimeManager::TimeManager()
  {
  }

  void TimeManager::Initialize()
  {
    initialTime = Clock.now();

    previousTick = initialTime;
    currentTick = initialTime;
  }

  void TimeManager::Start()
  {
  }

  Second TimeManager::Update()
  {
    previousTick = currentTick;
    currentTick = Clock.now();

    return GetDeltaTime();
  }

  void TimeManager::End()
  {
  }

  void TimeManager::CleanUp()
  {
  }

  Second TimeManager::GetDeltaTime() const
  {
    return (currentTick - previousTick);
  }

  Second TimeManager::GetTimeSpan() const
  {
    return (currentTick - initialTime);
  }
}// namespace Time
}// namespace Application