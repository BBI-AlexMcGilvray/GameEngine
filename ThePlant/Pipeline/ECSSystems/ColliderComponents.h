#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Application
{
struct ColliderComponent
{
    Core::Geometric::Shape3D shape;
    bool trigger;
    bool isStatic;

    ColliderComponent() = default;
    ColliderComponent(const ColliderComponent&) = default;
    ColliderComponent(ColliderComponent&&) = default;
    ColliderComponent& operator=(const ColliderComponent&) = default;
    ColliderComponent& operator=(ColliderComponent&&) = default;

    ColliderComponent(const Core::Geometric::Shape3D& shape, const bool& trigger, const bool& isStatic)
    : shape(shape)
    , trigger(trigger)
    , isStatic(isStatic)
    {}

    bool operator==(const ColliderComponent& other) const
    {
        return shape == other.shape && trigger == other.trigger && isStatic == other.isStatic;
    }
    bool operator !=(const ColliderComponent& other) const { return !(*this == other); }
};
} // namespace Application