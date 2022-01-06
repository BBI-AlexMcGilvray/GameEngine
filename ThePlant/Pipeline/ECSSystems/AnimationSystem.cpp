#include "Pipeline/ECSSystems/AnimationSystem.h"

namespace Application {
void SkeletonAnimationSystem::_ApplyAnimations(Animation::AnimationManager& animationManager, Core::Ptr<Archetype> archetype) const
{
    const std::vector<EntityId>& entities = archetype->GetEntities();
    std::vector<AnimationComponent>& animationComponents = archetype->GetComponents<AnimationComponent>();
    std::vector<BoneComponent>& boneComponents = archetype->GetComponents<BoneComponent>();
    Core::Ptr<std::vector<PositionComponent>> positions = archetype->HasComponent<PositionComponent>() ? &(archetype->GetComponents<PositionComponent>()) : nullptr;
    Core::Ptr<std::vector<ScaleComponent>> scales = archetype->HasComponent<ScaleComponent>() ? &(archetype->GetComponents<ScaleComponent>()) : nullptr;
    Core::Ptr<std::vector<RotationComponent>> rotations = archetype->HasComponent<RotationComponent>() ? &(archetype->GetComponents<RotationComponent>()) : nullptr;

    DEBUG_ASSERT(positions == nullptr || positions->size() == animationComponents.size());
    DEBUG_ASSERT(scales == nullptr || scales->size() == animationComponents.size());
    DEBUG_ASSERT(rotations == nullptr || rotations->size() == animationComponents.size());

    for (size_t index = 0; index < animationComponents.size(); ++index)
    {
        const auto& animationComponent = animationComponents[index];
        Animation::Animator& animator = animationManager.GetAnimator(animationComponent.animatorId);

        // checking the animation for if it affects the target or not is inefficient - but fine for now
        // in the future, maybe we want the animator to query the entity instead? may still have the same issue. may just need a more efficient way
        if (positions != nullptr && animator.AffectingTarget<Animation::Attribute::Position>(animationComponent.animationTarget))
        {
            (*positions)[index].position = animator.Evaluate<Core::Math::Float3, Animation::Attribute::Position>(animationComponent.animationTarget);
        }
        else
        {
            (*positions)[index].position = boneComponents[index].defaultState.GetPosition();
        }

        if (scales != nullptr && animator.AffectingTarget<Animation::Attribute::Scale>(animationComponent.animationTarget))
        {
            (*scales)[index].scale = animator.Evaluate<Core::Math::Float3, Animation::Attribute::Scale>(animationComponent.animationTarget);
        }
        else
        {
            (*scales)[index].scale = boneComponents[index].defaultState.GetScale();
        }

        if (rotations != nullptr && animator.AffectingTarget<Animation::Attribute::Rotation>(animationComponent.animationTarget))
        {
            (*rotations)[index].rotation = animator.Evaluate<Core::Math::FQuaternion, Animation::Attribute::Rotation>(animationComponent.animationTarget);
        }
        else
        {
            (*rotations)[index].rotation = boneComponents[index].defaultState.GetRotation();
        }
    }
}
} // namespace Application