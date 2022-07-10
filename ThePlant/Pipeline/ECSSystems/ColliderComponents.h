#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Application
{
// NOTES:
/*
- we may want to replace 'isStatic' with an enum of { Dynamic, Static_Dirty, Static_Placed }
    - Dynamic means removed + placed each tick
    - Static_Dirty means it needs to be placed this tick (and must be removed on the tick it was dirtied on)
    - Static_Placed means it has been placed and doesn't get removed until it is set to Static_Dirty
- problem: OctTree does not know about the component, how would we make sure the two values are synced?
    - have the ColliderManagers required to set the data on both? [ideal?]
        - this would mean the Collision data would need to have a reference to the two OctTreeContents as well
    - or when inserting the Static_Dirty component we search and remove the existing one, since it would not be the case most of the time?
        - but then any case where multiple items are dirtied would result in a significantly heavier frame
*/
enum class ColliderState
{
    Dynamic,
    Static_Dirty,
    Static_Placed
};

struct ColliderComponent
{
    Core::Geometric::Shape3D shape;
    bool trigger;
    ColliderState state;

    ColliderComponent() = default;
    ColliderComponent(const ColliderComponent&) = default;
    ColliderComponent(ColliderComponent&&) = default;
    ColliderComponent& operator=(const ColliderComponent&) = default;
    ColliderComponent& operator=(ColliderComponent&&) = default;

    ColliderComponent(const Core::Geometric::Shape3D& shape, const bool& trigger, const ColliderState& state)
    : shape(shape)
    , trigger(trigger)
    , state(state)
    {}

    bool operator==(const ColliderComponent& other) const
    {
        return shape == other.shape && trigger == other.trigger && state == other.state;
    }
    bool operator !=(const ColliderComponent& other) const { return !(*this == other); }
};
} // namespace Application