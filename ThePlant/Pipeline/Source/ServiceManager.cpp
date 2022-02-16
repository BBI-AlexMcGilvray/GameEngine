#include "Pipeline/Headers/ServiceManager.h"

namespace Application {
ServiceManager::ServiceManager()
{
    _profiler = SET_DEBUG_SERVICE(Profiling::Profiler);
}
}// namespace Application