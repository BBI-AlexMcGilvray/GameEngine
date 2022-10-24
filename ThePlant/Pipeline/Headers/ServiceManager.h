#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/Service.h"

#include "Core/Debugging/Memory/MemoryTracker.h"
#include "Core/Debugging/Profiling/Profiler.h"
#include "Core/Logging/Logger.h"

#include "Pipeline/Factory_Temp/Factory.h"

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
    Core::ServiceToken<Core::Memory::MemoryTracker> _memory; // must be first!

// #ifdef FACTORY
    Core::ServiceToken<Editor::Factory> _factory; // this should be gated by FACTORY defines
// #endif // FACTORY

    Core::ServiceToken<ApplicationWrapper> _application;
    Core::ServiceToken<Core::Profiling::Profiler> _profiler;

    Core::ServiceToken<Core::Logging::Logger> _logger;
};
}// namespace Application