#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

#include "Pipeline/Animation/Headers/AnimationManager.h"
#include "Pipeline/Animation/Headers/AnimationTargets.h"

#include "Pipeline/Debugging/Profiling/Utils.h"

namespace Application {
struct SkeletonAnimationSystem  : public System<SkeletonAnimationSystem>
{
    SkeletonAnimationSystem(Animation::AnimationManager& animationManager)
    : System<SkeletonAnimationSystem>("SkeletonAnimationSystem")
    , _animationManager(animationManager)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        DEBUG_PROFILE_SCOPE(GetSystemName());

        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<AnimationComponent, BoneComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyAnimations(_animationManager, archetype);
        }
    }

    private:

        Animation::AnimationManager& _animationManager;

        void SkeletonAnimationSystem::_ApplyAnimations(Animation::AnimationManager& animationManager, Core::Ptr<Archetype> archetype) const;
};

struct AnimationSystem : public CompoundSystem<AnimationSystem,
SkeletonAnimationSystem>
{
    AnimationSystem(Animation::AnimationManager& animationManager)
    : CompoundSystem<AnimationSystem,
        SkeletonAnimationSystem>("AnimationSystem", animationManager)
    {}
    // maybe want custom logic to handle dependency for parallel execution?
};
} // namespace Application