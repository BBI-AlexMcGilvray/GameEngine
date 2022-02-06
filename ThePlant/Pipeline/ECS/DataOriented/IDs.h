#pragma once

#include "Core/IdTypes/IncrementalId.h"
#include "Core/IdTypes/RuntimeId.h"

namespace Application {
struct ArchetypeId;
template <>
struct ::std::hash<ArchetypeId>;

struct ArchetypeId
{
    friend struct ::std::hash<ArchetypeId>;

    ArchetypeId() = default;

    ArchetypeId(const Core::IncrementalId& archetypeId)
    : _archetypeId(archetypeId)
    {}

    ArchetypeId(const ArchetypeId& other) = default;
    ArchetypeId(ArchetypeId&& other) = default;
    ArchetypeId& operator=(const ArchetypeId& other) = default;
    ArchetypeId& operator=(ArchetypeId&& other) = default;

    bool IsValid() const
    {
        return _archetypeId.IsValid();
    }

    bool operator==(const ArchetypeId& other) const
    {
        return (_archetypeId == other._archetypeId);
    }
    bool operator!=(const ArchetypeId& other) const
    {
        return !(*this == other);
    }

    bool operator<(const ArchetypeId& other) const
    {
        return _archetypeId < other._archetypeId;
    }
    bool operator<=(const ArchetypeId& other) const
    {
        return !(other < *this);
    }
    bool operator>(const ArchetypeId& other) const
    {
        return !(*this <= other);
    }
    bool operator>=(const ArchetypeId& other) const
    {
        return !(*this < other);
    }

    // explicit operator const IncrementalId() const { return _archetypeId; }

private:
    Core::IncrementalId _archetypeId;
};

struct EntityId;
template <>
struct ::std::hash<EntityId>;

struct EntityId
{
    friend struct ::std::hash<EntityId>;

    EntityId() = default;

    EntityId(const Core::IncrementalId& entityId)
    : _entityId(entityId)
    {}

    EntityId(const EntityId& other) = default;
    EntityId(EntityId&& other) = default;
    EntityId& operator=(const EntityId& other) = default;
    EntityId& operator=(EntityId&&) = default;

    bool IsValid() const
    {
        return _entityId.IsValid();
    }

    bool operator==(const EntityId& other) const
    {
        return (_entityId == other._entityId);
    }
    bool operator!=(const EntityId& other) const
    {
        return !(*this == other);
    }

    bool operator<(const EntityId& other) const
    {
        return _entityId < other._entityId;
    }
    bool operator<=(const EntityId& other) const
    {
        return !(other < *this);
    }
    bool operator>(const EntityId& other) const
    {
        return !(*this <= other);
    }
    bool operator>=(const EntityId& other) const
    {
        return !(*this < other);
    }

    // explicit operator const IncrementalId() const { return _entityId; }

private:
    Core::IncrementalId _entityId;
};

struct Entity
{
    friend struct Archetype;
    
    Entity() = default;
    
    Entity(const ArchetypeId& archetypeId)
    : _entityId(Core::GetIncrementalId())
    , _archetypeId(archetypeId)
    {}

    Entity(Entity&& other)
    : _entityId(std::move(other._entityId))
    , _archetypeId(std::move(other._archetypeId))
    {}

    Entity& operator=(Entity&& other)
    {
        _entityId = std::move(other._entityId);
        _archetypeId = std::move(other._archetypeId);

        return *this;
    }

    // entities should only be moved.
    // we should only have one reference to it as the archetypes can be changed and it would be impossible to track otherwise
    Entity(const Entity& other) = delete;
    Entity& operator=(const Entity& other) = delete;

    const EntityId& GetEntityId() const
    {
        return _entityId;
    }

    const ArchetypeId& GetArchetypeId() const
    {
        return _archetypeId;
    }

    bool IsValid() const
    {
        return _archetypeId.IsValid() && _entityId.IsValid();
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
}// namespace Application

template <>
struct std::hash<Application::ArchetypeId>
{
    size_t operator()(const Application::ArchetypeId& archetypeId) const
    {
        return _hasher(archetypeId._archetypeId);
    }

private:
    std::hash<Core::IncrementalId> _hasher;
};

template <>
struct std::hash<Application::EntityId>
{
    size_t operator()(const Application::EntityId& entityId) const
    {
        return _hasher(entityId._entityId);
    }

private:
    std::hash<Core::IncrementalId> _hasher;
};
