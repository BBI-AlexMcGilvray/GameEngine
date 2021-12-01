#pragma once

#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"
#include "Pipeline/ECS/DataOriented/Systems/SystemManager.h"

namespace Application
{
    // this is the only class that should be referenced externally, everything should go through this (but be handled by the ArchetypeManager and SystemManager)
    class SystemManager
    {
    public:
        SystemManager()
        : _systems(_archetypes)
        {}

        SystemManager(const SystemManager&) = delete;
        SystemManager(SystemManager&&) = delete;
        SystemManager& operator=(const SystemManager&) = delete;
        SystemManager& operator=(SystemManager&&) = delete;

        // we need all calls that ArchetypeManager and SystemManager have and forward to them respectively

    private:
        ArchetypeManager _archetypes;
        SystemManager _systems;
    };
} // namespace Application