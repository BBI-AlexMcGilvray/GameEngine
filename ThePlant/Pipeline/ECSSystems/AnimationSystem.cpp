#include "Pipeline/ECSSystems/AnimationSystem.h"

namespace Application {
void SkeletonAnimationSystem::_ApplyAnimations(Animation::AnimationManager& animationManager, Core::Ptr<Archetype> archetype) const
{
    const std::vector<EntityId>& entities = archetype->GetEntities();
    std::vector<AnimationComponent>& animationComponents = archetype->GetComponents<AnimationComponent>();
    Core::Ptr<std::vector<PositionComponent>> positions = archetype->HasComponent<PositionComponent>() ? &(archetype->GetComponents<PositionComponent>()) : nullptr;
    Core::Ptr<std::vector<ScaleComponent>> scales = archetype->HasComponent<ScaleComponent>() ? &(archetype->GetComponents<ScaleComponent>()) : nullptr;
    Core::Ptr<std::vector<RotationComponent>> rotations = archetype->HasComponent<RotationComponent>() ? &(archetype->GetComponents<RotationComponent>()) : nullptr;

    VERIFY(positions == nullptr || positions->size() == animationComponents.size());
    VERIFY(scales == nullptr || scales->size() == animationComponents.size());
    VERIFY(rotations == nullptr || rotations->size() == animationComponents.size());

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
} // namespace Application