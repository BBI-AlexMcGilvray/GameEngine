#pragma once

#include "Core/Debugging/Headers/Macros.h"

namespace Core {
namespace Functionality {
  struct LockerBase
  {
    void lock()
    {
      _lockCount++;
    }

    bool unlock()
    {
      _lockCount--;

      return isLocked();
    }

    bool isLocked()
    {
      DEBUG_ASSERT(_lockCount > 0, "LOCK COUNT DROPPING BELOW 0");
      return (_lockCount > 0);
    }

  private:
    int _lockCount = 0;
  };
}// namespace Functionality
}// namespace Core