#pragma once

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
// refers to parent, entities can only have ONE parent
struct ParentComponent
{
    EntityId entity;

    ParentComponent() = default;
    ParentComponent(const ParentComponent&) = default;
    ParentComponent(ParentComponent&&) = default;
    ParentComponent& operator=(const ParentComponent&) = default;
    ParentComponent& operator=(ParentComponent&&) = default;

    ParentComponent(const EntityId& entity)
    : entity(entity)
    {}

    bool operator==(const ParentComponent& other) const
    {
        return entity == other.entity;
    }
    bool operator !=(const ParentComponent& other) const { return !(*this == other); }
};

// refers to child, entities can have many children
struct ChildComponent
{
    std::vector<EntityId> children;

    ChildComponent() = default;
    ChildComponent(const ChildComponent&) = default;
    ChildComponent(ChildComponent&&) = default;
    ChildComponent& operator=(const ChildComponent&) = default;
    ChildComponent& operator=(ChildComponent&&) = default;

    ChildComponent(const std::vector<EntityId>& children)
    : children(children)
    {}

    void AddChild(const EntityId& entity)
    {
        SCOPED_MEMORY_CATEGORY("ECS");
    #if DEBUG
        if (_HasChild(entity))
        {
            CORE_THROW("ChildComponent", "Trying to add a child twice!");
            return;
        }
    #endif

        children.push_back(entity);
    }

    void RemoveChild(const EntityId& entity)
    {
        auto place = std::find(children.begin(), children.end(), entity);
        if (place == children.end())
        {
            CORE_THROW("ChildComponent", "Trying to remove a child that does not exist!");
            return;
        }

        children.erase(place);
    }

    bool operator==(const ChildComponent& other) const
    {
        return children == other.children;
    }
    bool operator !=(const ChildComponent& other) const { return !(*this == other); }

private:
    bool _HasChild(const EntityId& entity)
    {
        return std::find(children.begin(), children.end(), entity) != children.end();
    }
};
}// namespace Application