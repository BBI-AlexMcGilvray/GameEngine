#pragma once

#include <memory>
#include <stdexcept>
#include <vector>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/IdTypes/RuntimeId.h"

#include "Pipeline/ECS/DataOriented/Archetype.h"
#include "Pipeline/ECS/DataOriented/Component.h"
#include "Pipeline/ECS/DataOriented/ComponentCreator.h"
#include "Pipeline/ECS/DataOriented/TypeCollection.h"

namespace Application {
struct EntityCreator
{
    // get the representation of the desired archetype
    TypeCollection GetArchetype() const;
    // if the archetype does not exist, this will create one
    Archetype CreateArchetype() const;
    // given the archetype that matches this entity, create the entity within it
    // (ArchetypeManager will use the GetArchetype method - and then potentially the CreateArchetype method - to determine what is passed in here)
    EntityId CreateEntity(Archetype& archetype) const;

    template <typename T, typename ...ARGS>
    EntityCreator& AddComponent(ARGS&& ...args)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
        _componentCreators.emplace_back(std::make_unique<ComponentCreator<T>>(T(std::forward<ARGS>(args)...)));

        return *this; // to allow 'chaining'
    }

    template <typename T>
    void RemoveComponent()
    {
        for (auto& iter = _componentCreators.begin(); iter != _componentCreators.end(); ++iter)
        {
            if (iter->GetComponentType() == Core::GetTypeId<T>())
            {
                _componentCreators.erase(iter);
                return;
            }
        }

        throw std::invalid_argument("trying to remove a component that does not exist for the given entity");
    }

private:
    std::vector<std::unique_ptr<IComponentCreator>> _componentCreators;
};
} // namespace Application