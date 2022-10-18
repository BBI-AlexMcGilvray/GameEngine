#pragma once

#include <string>

#include "Core/Reflection/Reflectable.h"
#include "Core/IdTypes/InstanceId.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Animation
{
    class Animator;
} // namespae Animation

struct AnimationComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Core::instanceId<Animation::Animator> animatorId;
    Core::Hash animationTarget; // ideally we make this not a string, but it is for now to identify what bone is what

    AnimationComponent() = default;
    AnimationComponent(const AnimationComponent&) = default;
    AnimationComponent(AnimationComponent&&) = default;
    AnimationComponent& operator=(const AnimationComponent&) = default;
    AnimationComponent& operator=(AnimationComponent&&) = default;

    AnimationComponent(const Core::instanceId<Animation::Animator>& animatorId, const Core::Hash& animationTarget)
    : animatorId(animatorId)
    , animationTarget(animationTarget)
    {}

    bool operator==(const AnimationComponent& other) const
    {
        return animatorId == other.animatorId && animationTarget == other.animationTarget;
    }
    bool operator !=(const AnimationComponent& other) const { return !(*this == other); }
};

struct AnimatorComponent
{
    NOTHING_REFLECTABLE() // should actually contain the components
    Core::instanceId<Animation::Animator> animatorId;

    AnimatorComponent() = default;
    AnimatorComponent(const AnimatorComponent&) = default;
    AnimatorComponent(AnimatorComponent&&) = default;
    AnimatorComponent& operator=(const AnimatorComponent&) = default;
    AnimatorComponent& operator=(AnimatorComponent&&) = default;

    AnimatorComponent(const Core::instanceId<Animation::Animator>& animatorId)
    : animatorId(animatorId)
    {}

    bool operator==(const AnimatorComponent& other) const
    {
        return animatorId == other.animatorId;
    }
    bool operator !=(const AnimatorComponent& other) const { return !(*this == other); }
};
}// namespace Application