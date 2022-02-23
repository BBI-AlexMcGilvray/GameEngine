#pragma once

#include <vector>

#include "Materials/Core/Headers/PtrDefs.h"
#include "Materials/Core/Logging/Logger.h"

#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"
#include "Pipeline/ECS/DataOriented/Systems/System.h"

namespace Application
{
    class SystemManager
    {
    public:
        SystemManager(ArchetypeManager& archetypeManager);

        void Update(); // run each system - we need to take care to ensure dependencies are adhered to REGARDLESS OF INSERTION ORDER

        template <typename SYSTEM, typename ...ARGS>
        ISystem& AddSystem(ARGS ...args)
        {
            if (_HasSystem<SYSTEM>())
            {
                DEBUG_THROW("SystemManager", "Adding system that already exists! Systems must be unique");
                return _GetSystem<SYSTEM>();
            }

            auto& result = _systems.emplace_back(Core::MakeUnique<SYSTEM>(std::forward<ARGS>(args)...));
            _Dirty();

            return *result;
        }

        template <typename SYSTEM>
        void RemoveSystem()
        {
            size_t index = 0;
            for (auto& system : _systems)
            {
                if (system->IsSystem<SYSTEM>())
                {
                    _systems.erase(_systems.begin() + index);
                    return;
                }
                ++index;
            }
        }

    private:
        ArchetypeManager& _archetypeManager;
        std::vector<Core::UniquePtr<ISystem>> _systems;
        bool _systemsDirty = false;

        void _Dirty() { _systemsDirty = true; }
        void _Clean() { _systemsDirty = false; }
        bool _IsDirty() { return _systemsDirty; }

        void _OrderSetForDependencies();

        template <typename SYSTEM>
        bool _HasSystem() const
        {
            for (auto& system : _systems)
            {
                if (system->IsSystem<SYSTEM>())
                {
                    return true;
                }
            }

            return false;
        }

        template <typename SYSTEM>
        ISystem& _GetSystem()
        {
            for (auto& system : _systems)
            {
                if (system->IsSystem<SYSTEM>())
                {
                    return *system;
                }
            }

            throw std::invalid_argument("System does not exist");
        }
    };
} // namespace Application