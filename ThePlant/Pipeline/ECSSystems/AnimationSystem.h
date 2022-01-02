#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

#include "Pipeline/Animation/Headers/AnimationManager.h"
#include "Pipeline/Animation/Headers/AnimationTargets.h"

namespace Application {
struct SkeletonAnimationSystem  : public ISystem
{
    SkeletonAnimationSystem(Animation::AnimationManager& animationManager)
    : _animationManager(animationManager)
    {}

    Core::runtimeId_t GetSystem() const { return Core::GetTypeId<SkeletonAnimationSystem>(); };

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<AnimationComponent, BoneComponent, ParentComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyAnimations(_animationManager, archetype);
        }
    }

    private:

        Animation::AnimationManager& _animationManager;

        void SkeletonAnimationSystem::_ApplyAnimations(Animation::AnimationManager& animationManager, Core::Ptr<Archetype> archetype) const;
};

struct FILLER : public System<FILLER>
{
    enum class TAG
    {
        Creator
    };

    FILLER(const TAG&)
    {}

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        // do nothing, not a real system
    }
};

struct AnimationSystem : public CompoundSystem<AnimationSystem,
SkeletonAnimationSystem,
FILLER> // FILLER is needed so a tuple can be created
{
    AnimationSystem(Animation::AnimationManager& animationManager)
    : CompoundSystem<AnimationSystem,
        SkeletonAnimationSystem,
        FILLER>(animationManager, FILLER::TAG::Creator)
    {}
    // maybe want custom logic to handle dependency for parallel execution?
};
} // namespace Application