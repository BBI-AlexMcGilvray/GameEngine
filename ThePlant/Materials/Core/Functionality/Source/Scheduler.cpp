#include "Core/Functionality/Headers/Scheduler.h"

#include <algorithm>

namespace Core {
namespace Functionality {
  void SchedulerBase::Update(Second dt)
  {
    _Sort();

    size_t callsExecuted = 0;
    for (auto &scheduledCall : _scheduledFunctions) {
      scheduledCall.first -= dt;

      if (!isLocked() && scheduledCall.first <= 0_s) {
        // something wrong with the templates to get incorrect type matchup here
        _Execute(scheduledCall.second, dt);
        callsExecuted++;
      }
    }

    _Prune(callsExecuted);
  }

  void SchedulerBase::Add(VoidFunction<Second> func, Second key)
  {
    _scheduledFunctions.emplace_back(key, func);
    _Dirty();
  }

  bool SchedulerBase::IsDirty() const
  {
    return _dirty;
  }

  void SchedulerBase::_Dirty()
  {
    _dirty = true;
  }

  void SchedulerBase::_Sort()
  {
    if (!IsDirty())
    {
      return;
    }

    std::sort(_scheduledFunctions.begin(), _scheduledFunctions.end(), [](std::pair<Second, VoidFunction<Second>> a, std::pair<Second, VoidFunction<Second>> b)
    {
      return a.first < b.first;
    });

    _dirty = false;
  }

  void SchedulerBase::_Execute(VoidFunction<Second> &func, Second dt)
  {
    func(dt);
  }

  void SchedulerBase::_Prune(size_t callsExecuted)
  {
    if (callsExecuted == 0)
    {
      return;
    }
    
    _scheduledFunctions.erase(_scheduledFunctions.begin(), _scheduledFunctions.begin() + callsExecuted);
  }
}// namespace Functionality
}// namespace Core