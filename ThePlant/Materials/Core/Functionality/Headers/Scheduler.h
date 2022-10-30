#pragma once

#include <vector>
#include <utility>

#include "Core/Functionality/Headers/Function.h"
#include "Core/Functionality/Headers/LockerBase.h"
#include "Core/Headers/TimeDefs.h"

namespace Core {
namespace Functionality {
  struct SchedulerBase : LockerBase
  {
    virtual ~SchedulerBase() = default;

    void Update(Second dt);

    void Add(VoidFunction<Second> func, Second key = 0_s);

    bool IsDirty() const;

  protected:
    // All scheduled functions, sorted by Second
    std::vector<std::pair<Second, VoidFunction<Second>>> _scheduledFunctions;
    bool _dirty;

    void _Dirty();
    void _Sort();
    virtual void _Execute(VoidFunction<Second> &func, Second dt);
    void _Prune(size_t callsExecuted);
  };
}// namespace Functionality
}// namespace Core