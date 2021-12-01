#include "Pipeline/ECS/DataOriented/ArchetypeManager.h"

#include <stdexcept>

namespace Application {
void ArchetypeManager::RemoveEntity(const Entity& entity)
{
    if (!_HasArchetype(entity.GetArchetypeId()))
    {
        return;
    }
    _GetArchetype(entity.GetArchetypeId()).RemoveEntity(entity);
}

bool ArchetypeManager::_HasArchetype(const TypeCollection& archetypeTypes)
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

bool ArchetypeManager::_HasArchetype(const ArchetypeId& archetypeId)
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
}// namespace Application
