#include "Pipeline/Headers/ServiceManager.h"

#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
ServiceManager::ServiceManager(ApplicationManager& application)
{
    _memory = SET_DEBUG_SERVICE(Core::Memory::MemoryTracker); // must be added first and destroyed last

    // should have a SET_FACTORY_SERVICE
    _factory = SET_DEBUG_SERVICE(Editor::Factory, application);
    // \ should have a SET_FACTORY_SERVICE
    
    _application = SET_DEBUG_SERVICE(ApplicationWrapper, &application);
    _profiler = SET_DEBUG_SERVICE(Core::Profiling::Profiler);
    
    _logger = SET_SERVICE(Core::Logging::Logger, Core::Logging::Logger::ServiceOnlyConstructionTag());
}
}// namespace Application