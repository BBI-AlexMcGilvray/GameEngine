#include "ApplicationManagement/Animation/Headers/AnimatorComponent.h"

namespace Application {
namespace Animation {
  AnimatorComponent::AnimatorComponent(Core::Ptr<EntityBase> entity, Core::Ptr<AnimationManager> animationManager)
    : Component<AnimatorComponent>(entity, this), _animationManager(animationManager)
  {
  }

  Core::Ptr<Animator> AnimatorComponent::SetAnimator(Core::UniquePtr<Animator> animator)
  {
    ASSERT(_animator == nullptr);
    _animator = _animationManager->AddAnimator(move(animator));
    return _animator;
  }

  void AnimatorComponent::RemoveAnimator(Core::Ptr<Animator> animator)
  {
    if (_animator == animator) {
      _animationManager->RemoveAnimator(animator);
      _animator = nullptr;
    }
  }
}// namespace Animation
}// namespace Application