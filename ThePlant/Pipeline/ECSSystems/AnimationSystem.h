#pragma once

#include <vector>

#include "Pipeline/ECS/DataOriented/Systems/System.h"
#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

#include "Pipeline/Animation/Headers/AnimationManager.h"
#include "Pipeline/Animation/Headers/AnimationTargets.h"

namespace Application {
struct SkeletonAnimationSystem  : public ISystem
{
    SkeletonAnimationSystem(AnimationManager& animationManager)
    : _animationManager(animationManager)
    {}

    Core::runtimeId_t GetSystem() const { return Core::GetTypeId<SkeletonAnimationSystem>(); };

    void Execute(ArchetypeManager& archetypeManager) const override
    {
        std::vector<Core::Ptr<Archetype>> affectedArchetypes = archetypeManager.GetArchetypesContaining<AnimationComponent, BoneComponent>();

        for (auto& archetype : affectedArchetypes)
        {
            _ApplyToArchetype(_animationManager, archetype);
        }
    }

    /*
        - Get all AnimatorComponents
            - Iterate and increase the 'animationTime' by a given delta time
            - Update the Animators accordingly
        - Get all AnimationComponents
            - For each, query the Animator for the given target
            - Apply the result to the affected components
    */

    private:
        AnimationManager& _animationManager;

        void _ApplyToArchetype(AnimationManager& animationManager, Core::Ptr<Archetype> archetype) const
        {
            std::vector<AnimationComponent>& animationComponents = archetype->GetComponents<AnimationComponent>();
            std::vector<BoneComponent>& bones = archetype->GetComponents<BoneComponent>();
            Core::Ptr<std::vector<PositionComponent>> positions = archetype->HasComponent<PositionComponent>() ? &(archetype->GetComponents<PositionComponent>()) : nullptr;
            Core::Ptr<std::vector<ScaleComponent>> scales = archetype->HasComponent<ScaleComponent>() ? &(archetype->GetComponents<ScaleComponent>()) : nullptr;
            Core::Ptr<std::vector<RotationComponent>> rotations = archetype->HasComponent<RotationComponent>() ? &(archetype->GetComponents<RotationComponent>()) : nullptr;

            VERIFY(animationComponents.size() == bones.size());
            VERIFY(positions == nullptr || positions->size() == animationComponents.size());
            VERIFY(scales == nullptr || scales->size() == animationComponents.size());
            VERIFY(rotations == nullptr || rotations->size() == animationComponents.size());

            for (size_t index = 0; index < animationComponents.size(); ++index)
            {
                const auto& animationComponent = animationComponents[index];
                Animator& animator = animationManager.GetAnimator(animationComponent.animatorId);

                // checking the animation for if it affects the target or not is inefficient - but fine for now
                // in the future, maybe we want the animator to query the entity instead? may still have the same issue. may just need a more efficient way
                if (positions != nullptr && animator.AffectingTarget<Animation::Attribute::Position>(animationComponent.animationTarget))
                {
                    (*positions)[index].position = animator.Evaluate<Core::Math::Float3, Animation::Attribute::Position>(animationComponent.animationTarget);
                }

                if (scales != nullptr && animator.AffectingTarget<Animation::Attribute::Scale>(animationComponent.animationTarget))
                {
                    (*scales)[index].scale = animator.Evaluate<Core::Math::Float3, Animation::Attribute::Scale>(animationComponent.animationTarget);
                }

                if (rotations != nullptr && animator.AffectingTarget<Animation::Attribute::Rotation>(animationComponent.animationTarget))
                {
                    (*rotations)[index].rotation = animator.Evaluate<Core::Math::FQuaternion, Animation::Attribute::Rotation>(animationComponent.animationTarget);
                }
            }
        }
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
    AnimationSystem(AnimationManager& animationManager)
    : CompoundSystem<AnimationSystem,
        SkeletonAnimationSystem,
        FILLER>(animationManager, FILLER::TAG::Creator)
    {}
    // maybe want custom logic to handle dependency for parallel execution?
};
} // namespace Application