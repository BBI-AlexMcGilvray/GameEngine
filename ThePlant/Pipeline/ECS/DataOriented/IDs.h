#pragma once

#include "IncrementalId.h"

#include "../TypeId/TypeId.h"

struct ArchetypeId
{
    ArchetypeId(const IncrementalId& archetypeId)
    : _archetypeId(archetypeId)
    {}

    ArchetypeId(const ArchetypeId& other)
    : _archetypeId(other._archetypeId)
    {}

    ArchetypeId(ArchetypeId&& other)
    : _archetypeId(std::move(other._archetypeId))
    {}

    ArchetypeId& operator=(const ArchetypeId& other)
    {
        _archetypeId = other._archetypeId;

        return *this;
    }

    bool operator==(const ArchetypeId& other) const
    {
        return (_archetypeId == other._archetypeId);
    }

    bool operator!=(const ArchetypeId& other) const
    {
        return !(*this == other);
    }

    // explicit operator const IncrementalId() const { return _archetypeId; }

private:
    IncrementalId _archetypeId;
};

struct EntityId
{
    EntityId(const IncrementalId& entityId)
    : _entityId(entityId)
    {}

    EntityId(const EntityId& other)
    : _entityId(other._entityId)
    {}

    EntityId(EntityId&& other)
    : _entityId(std::move(other._entityId))
    {}

    EntityId& operator=(const EntityId& other)
    {
        _entityId = other._entityId;

        return *this;
    }

    bool operator==(const EntityId& other) const
    {
        return (_entityId == other._entityId);
    }

    bool operator!=(const EntityId& other) const
    {
        return !(*this == other);
    }

    // explicit operator const IncrementalId() const { return _entityId; }

private:
    IncrementalId _entityId;
};

struct Entity
{
    friend struct Archetype;
    
    Entity(const ArchetypeId& archetypeId)
    : _entityId(GetIncrementalId())
    , _archetypeId(archetypeId)
    {}

    Entity(const Entity& other)
    : _entityId(other._entityId)
    , _archetypeId(other._archetypeId)
    {}

    Entity(Entity&& other)
    : _entityId(std::move(other._entityId))
    , _archetypeId(std::move(other._archetypeId))
    {}

    Entity& operator=(const Entity& other)
    {
        _entityId = other._entityId;
        _archetypeId = other._archetypeId;

        return *this;
    }

    Entity& operator=(Entity&& other)
    {
        _entityId = std::move(other._entityId);
        _archetypeId = std::move(other._archetypeId);

        return *this;
    }

    const EntityId& GetEntityId() const
    {
        return _entityId;
    }

    const ArchetypeId& GetArchetypeId() const
    {
        return _archetypeId;
    }

    bool operator==(const Entity& other) const
    {
        return (_entityId == other._entityId && _archetypeId == other._archetypeId);
    }

    bool operator!=(const Entity& other) const
    {
        return !(*this == other);
    }

private:
    EntityId _entityId;
    ArchetypeId _archetypeId;

    void _SetArchetypeId(const ArchetypeId& archetypeId)
    {
        _archetypeId = archetypeId;
    }
};