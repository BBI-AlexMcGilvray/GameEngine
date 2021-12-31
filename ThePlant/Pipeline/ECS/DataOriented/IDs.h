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

    ArchetypeId& operator=(ArchetypeId&& other)
    {
        _archetypeId = std::move(other._archetypeId);

        return *this;
    }

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

    EntityId& operator=(EntityId&& other)
    {
        _entityId = std::move(other._entityId);

        return *this;
    }

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
