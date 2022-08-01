#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"

#include <stdexcept>

#include "Pipeline/ECS/DataOriented/EntityHandler.h"

namespace Application {
EntityId ArchetypeManager::CreateEntity(const EntityHandler& creator)
{
    SCOPED_MEMORY_CATEGORY("ECS");
    auto& archetype = creator.GetArchetype();
    if (!_HasArchetype(archetype))
    {
        _archetypes.emplace_back(creator.CreateArchetype());
    }

    auto& entityArchetype = _GetArchetype(archetype);
    creator.CreateEntity(entityArchetype, entityArchetype.AddEntity());
}

void ArchetypeManager::RemoveEntity(const Entity& entity)
{
    if (!_HasArchetype(entity.GetArchetypeId()))
    {
        return;
    }
    _GetArchetype(entity.GetArchetypeId()).RemoveEntity(entity.GetEntityId());
}

void ArchetypeManager::RemoveEntity(const EntityId& entity)
{
    _GetArchetype(entity).RemoveEntity(entity);
}
        
EntitySnapshot ArchetypeManager::GetTemporaryEntitySnapshot(const Entity& entity)
{
    if (!_HasArchetype(entity.GetArchetypeId()))
    {
        CORE_THROW("ArchetypeManager", "Archetype does not exist for given entity");
    }
    return GetTemporaryEntitySnapshot(entity.GetEntityId());
}

EntitySnapshot ArchetypeManager::GetTemporaryEntitySnapshot(const EntityId& entity)
{
    return _GetArchetype(entity).GetTemporaryEntitySnapshot(entity);
}

void ArchetypeManager::ApplyChanges()
{
    SCOPED_MEMORY_CATEGORY("ECS");
    for (auto& entityChange : _entityChanges)
    {
        const auto& entity = entityChange.first;
        auto& entityChanger = entityChange.second;

        if (entityChanger.GetChanges().HasAllFlags(EntityChange::Deleted))
        {
            RemoveEntity(entity);
        }

        Archetype& oldArchetype = _GetArchetype(entityChanger.GetFinalArchetype());
        TypeCollection newArchetypeType = entityChanger.GetFinalArchetype();
        if (!_HasArchetype(newArchetypeType))
        {
            _archetypes.emplace_back(entityChanger.CreateArchetype());
        }

        Archetype& newArchetype = _GetArchetype(newArchetypeType);
        oldArchetype.TransferEntityTo(entity, newArchetype);

        entityChanger.CreateNewComponents(newArchetype);
    }
}

bool ArchetypeManager::_HasArchetype(const TypeCollection& archetypeTypes) const
{
    for (auto& archetype : _archetypes)
    {
        if (archetype.IsArchetype(archetypeTypes))
        {
            return true;
        }
    }

    return false;
}

bool ArchetypeManager::_HasArchetype(const ArchetypeId& archetypeId) const
{
    for (auto& archetype : _archetypes)
    {
        if (archetype.GetId() == archetypeId)
        {
            return true;
        }
    }

    return false;
}

Archetype& ArchetypeManager::_GetArchetype(const TypeCollection& archetypeTypes)
{
    for (auto& archetype : _archetypes)
    {
        if (archetype.IsArchetype(archetypeTypes))
        {
            return archetype;
        }
    }

    throw std::invalid_argument("archetype does not exist within manager");
}

Archetype& ArchetypeManager::_GetArchetype(const ArchetypeId& archetypeId)
{
    for (auto& archetype : _archetypes)
    {
        if (archetype.GetId() == archetypeId)
        {
            return archetype;
        }
    }

    throw std::invalid_argument("archetype does not exist within manager");
}

Archetype& ArchetypeManager::_GetArchetype(const EntityId& entity)
{
    for (auto& archetype : _archetypes)
    {
        if (archetype.HasEntity(entity))
        {
            return archetype;
        }
    }

    throw std::invalid_argument("archetype does not exist within manager");
}
}// namespace Application
