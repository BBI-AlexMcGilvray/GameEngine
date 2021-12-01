#pragma once

#include "Materials/Core/Headers/PtrDefs.h"
#include "Materials/Core/Logging/Logger.h"

#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"

#include <set>

namespace Application
{
    class SystemManager
    {
    public:
        SystemManager(const ArchetypeManager& archetypeManager);

        void Update(); // run each system - we need to take care to ensure dependencies are adhered to REGARDLESS OF INSERTION ORDER

        template <typename SYSTEM, typename ...ARGS>
        void AddSystem(ARGS ...args)
        {
            if (_HasSystem<SYSTEM>())
            {
                DEBUG_THROW("SystemManager", "Adding system that already exists! Systems must be unique");
                return;
            }

            _systems.emplace(Core::MakeUnique<T>(std::forward<ARGS>(args)...));
            _Dirty();
        }

    private:
        const ArchetypeManager& _archetypeManager;
        std::set<Core::UniquePtr<ISystem>> _systems;
        bool _systemsDirty = false;

        void _Dirty() { _systemsDirty = true; }
        void _Clean() { _systemsDirty = false; }
        bool _IsDirty() { return _systemsDirty; }

        void _OrderSetForDependencies();

        template <typename SYSTEM>
        bool _HasSystem()
        {
            for (auto& system : _systems)
            {
                if (system.IsSystem<SYSTEM>())
                {
                    return true;
                }
            }

            return false;
        }
    };
} // namespace Application