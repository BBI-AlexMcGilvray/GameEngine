#pragma once

#include "Core/Reflection/Reflectable.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
// refers to parent, entities can only have ONE parent
struct LifetimeComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    // lifetime < 0 implies infinite
    float lifetime;

    LifetimeComponent() = default;
    LifetimeComponent(const LifetimeComponent&) = default;
    LifetimeComponent(LifetimeComponent&&) = default;
    LifetimeComponent& operator=(const LifetimeComponent&) = default;
    LifetimeComponent& operator=(LifetimeComponent&&) = default;

    LifetimeComponent(float lifetime)
    : lifetime(lifetime)
    {
        VERIFY(lifetime > 0.0f, "Lifetimes must be positive! If you want an infinite lifetime, remove this component");
    }

    bool operator==(const LifetimeComponent& other) const
    {
        return lifetime == other.lifetime;
    }
    bool operator !=(const LifetimeComponent& other) const { return !(*this == other); }
};
}// namespace Application