#pragma once

#include "Core/Headers/Service.h"

#include "Core/Debugging/Memory/MemoryTracker.h"
#include "Core/Debugging/Profiling/Profiler.h"

namespace Application {
struct ServiceManager
{
    ServiceManager();

private:
    Core::ServiceToken<Core::Memory::MemoryTracker> _memory;
    Core::ServiceToken<Core::Profiling::Profiler> _profiler;
};
}// namespace Application