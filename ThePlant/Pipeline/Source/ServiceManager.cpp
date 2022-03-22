#include "Pipeline/Headers/ServiceManager.h"

namespace Application {
ServiceManager::ServiceManager()
{
    _memory = SET_DEBUG_SERVICE(Core::Memory::MemoryTracker); // must be added first and destroyed last
    _profiler = SET_DEBUG_SERVICE(Core::Profiling::Profiler);
    
    _logger = SET_SERVICE(Core::Logging::Logger, Core::Logging::Logger::ServiceOnlyConstructionTag());
}
}// namespace Application