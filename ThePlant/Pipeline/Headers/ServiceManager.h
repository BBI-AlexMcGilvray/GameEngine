#pragma once

#include "Core/Headers/Service.h"

#include "Pipeline/Debugging/Profiling/Profiler.h"

namespace Application {
struct ServiceManager
{
    ServiceManager();

private:
    Core::ServiceToken<Profiling::Profiler> _profiler;
};
}// namespace Application