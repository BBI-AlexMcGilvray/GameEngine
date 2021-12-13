#pragma once

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
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

    bool operator==(const ParentComponent& other)
    {
        return entity == other.entity;
    }
};
}// namespace Application