#include "Pipeline/ECS/DataOriented/Systems/SystemManager.h"

namespace Application
{
    SystemManager::SystemManager(const ArchetypeManager& archetypeManager)
    : _archetypeManager(archetypeManager)
    {}

    void SystemManager::Update()
    {
        if (_IsDirty())
        {
            _OrderSetForDependencies();
        }

        for (auto& system : _systems)
        {
            system->Execute(_archetypeManager);
        }
    }

    void SystemManager::_OrderSetForDependencies()
    {
        // somehow sort all systems based on their dependencies to other systems

        _Clean();
    }
} // namespace Application