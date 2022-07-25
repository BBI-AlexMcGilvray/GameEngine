#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/Service.h"

#include "Core/Debugging/Memory/MemoryTracker.h"
#include "Core/Debugging/Profiling/Profiler.h"
#include "Core/Logging/Logger.h"

namespace Application {
struct ApplicationManager;

struct ApplicationWrapper
{
    Core::Ptr<ApplicationManager> application;

    ApplicationWrapper(Core::Ptr<ApplicationManager> application)
    : application(application)
    {}
};

struct ServiceManager
{
    ServiceManager(ApplicationManager& application);

private:
    Core::ServiceToken<ApplicationWrapper> _application;
    Core::ServiceToken<Core::Memory::MemoryTracker> _memory;
    Core::ServiceToken<Core::Profiling::Profiler> _profiler;

    Core::ServiceToken<Core::Logging::Logger> _logger;
};
}// namespace Application