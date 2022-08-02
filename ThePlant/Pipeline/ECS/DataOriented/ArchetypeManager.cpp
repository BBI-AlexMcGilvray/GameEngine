#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"

#include <stdexcept>

#include "Pipeline/ECS/DataOriented/EntityHandler.h"

namespace Application {
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
        _ApplyHandler(entityChange.second);
    }
    _entityChanges.clear();
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

void ArchetypeManager::_CreateEntityHandler(const EntityId& entity, EntityState state)
{
    _entityChanges.emplace(entity, (state == EntityState::New) ? EntityHandler(entity) : EntityHandler(GetTemporaryEntitySnapshot(entity)));
}

EntityHandler& ArchetypeManager::_GetEntityHandler(const EntityId& entity, EntityState state)
{
    if (_entityChanges.find(entity) == _entityChanges.end())
    {
        _CreateEntityHandler(entity, state);
    }
    else
    {
        VERIFY(state != EntityState::New, "If we are making a new one, it should not exist!");
    }

    return _entityChanges.at(entity);
}


void ArchetypeManager::_ApplyHandler(const EntityHandler& handler)
{
    EntityId entity = handler.GetEntity();

    if (handler.GetChanges().HasAllFlags(EntityChange::Deleted))
    {
        _RemoveEntity(entity);
        return;
    }

    Core::Ptr<Archetype> oldArchetype = nullptr;
    if (!handler.GetChanges().HasAllFlags(EntityChange::Created))
    {
        oldArchetype = &_GetArchetype(handler.GetArchetype());
    }

    TypeCollection newArchetypeType = handler.GetFinalArchetype();
    if (!_HasArchetype(newArchetypeType))
    {
        _archetypes.emplace_back(handler.CreateArchetype(oldArchetype));
    }
    Archetype& newArchetype = _GetArchetype(newArchetypeType);

    // only transfer if it already existed
    if (oldArchetype != nullptr)
    {
        oldArchetype->TransferEntityTo(entity, newArchetype);
    }
    else
    {
        newArchetype.AddEntity(entity);
    }

    handler.CreateNewComponents(newArchetype);
}

void ArchetypeManager::_RemoveEntity(const EntityId& entity)
{
    _GetArchetype(entity).RemoveEntity(entity);
}
}// namespace Application
