#pragma once

#include "Core/IdTypes/RuntimeId.h"
#include "Core/IdTypes/InstanceId.h"

namespace Application {
struct ArchetypeId;
template <>
struct ::std::hash<ArchetypeId>;

using ArchetypeInstanceId = Core::instanceId<ArchetypeId>;
struct ArchetypeId
{
    friend struct ::std::hash<ArchetypeId>;

    ArchetypeId() = default;

    ArchetypeId(const ArchetypeInstanceId& archetypeId)
    : _archetypeId(archetypeId)
    {}

    ArchetypeId(const ArchetypeId&) = default;
    ArchetypeId(ArchetypeId&&) = default;
    ArchetypeId& operator=(const ArchetypeId&) = default;
    ArchetypeId& operator=(ArchetypeId&&) = default;

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
    ArchetypeInstanceId _archetypeId;
};

struct EntityId;
template <>
struct ::std::hash<EntityId>;

using EntityInstanceId = Core::instanceId<EntityId>;
struct EntityId
{
    friend struct ::std::hash<EntityId>;

    EntityId() = default;

    EntityId(const EntityInstanceId& entityId)
    : _entityId(entityId)
    {}

    EntityId(const EntityId&) = default;
    EntityId(EntityId&&) = default;
    EntityId& operator=(const EntityId&) = default;
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
    EntityInstanceId _entityId;
};

struct Entity
{
    friend struct Archetype;
    
    Entity() = default;
    
    Entity(const EntityId& entityId, const ArchetypeId& archetypeId)
    : _entityId(entityId)
    , _archetypeId(archetypeId)
    {}

    Entity(const ArchetypeId& archetypeId)
    : _entityId(Core::GetInstanceId<EntityId>())
    , _archetypeId(archetypeId)
    {}

    // since entities will only be accessed by snapshot and all changes will be delayed, shouldn't be an issue copying entities
    Entity(Entity&& other) = default;
    Entity(const Entity&) = default;
    Entity& operator=(Entity&& other) = default;
    Entity& operator=(const Entity&) = default;

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
    Core::instanceIdHasher<Application::ArchetypeId> _hasher;
};

template <>
struct std::hash<Application::EntityId>
{
    size_t operator()(const Application::EntityId& entityId) const
    {
        return _hasher(entityId._entityId);
    }

private:
    Core::instanceIdHasher<Application::EntityId> _hasher;
};
