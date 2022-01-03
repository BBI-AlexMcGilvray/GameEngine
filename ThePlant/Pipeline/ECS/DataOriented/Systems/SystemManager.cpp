#include "Pipeline/ECS/DataOriented/Systems/SystemManager.h"

#include <algorithm>

#include "Materials/Core/Debugging/Headers/Macros.h"

namespace Application
{
    SystemManager::SystemManager(ArchetypeManager& archetypeManager)
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

    // probably a way to optimize while taking into account the current state of the sorted systems
    void SystemManager::_OrderSetForDependencies()
    {
        std::vector<Core::UniquePtr<ISystem>> sortedSystems;
        
        auto dependenciesSorted = [&sortedSystems, this](const std::set<Core::runtimeId_t>& dependencies)
        {
            for (const auto& dependency : dependencies)
            {
                auto inSystems = std::find_if(_systems.begin(), _systems.end(), [&dependency](const auto& system)
                {
                    return (dependency == system->GetSystem());
                });
                // if the system is not loaded, the dependency is fulfilled (maybe not the most safe...)
                if (inSystems == _systems.end())
                {
                    return true;
                }

                auto& inSorted = std::find_if(sortedSystems.begin(), sortedSystems.end(), [&dependency](const auto& system)
                {
                    return (dependency == system->GetSystem());
                });

                if (inSorted == sortedSystems.end())
                {
                    return false;
                }
            }

            return true;
        };

        while (_systems.size() > 0)
        {
            for (auto& iter = _systems.begin(); iter != _systems.end();/* handled in-loop */)
            {
                const std::set<Core::runtimeId_t>& dependencies = (*iter)->GetDependencies();
                if (dependencies.size() == 0 || dependenciesSorted(dependencies))
                {
                    sortedSystems.emplace_back(std::move(*iter));
                    iter = _systems.erase(iter);
                }
                else
                {
                    ++iter;
                }
            }
        }

        VERIFY(_systems.size() == 0);
        _systems = std::move(sortedSystems);

        _Clean();
    }
} // namespace Application