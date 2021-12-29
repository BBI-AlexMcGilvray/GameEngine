#include "Pipeline/Animation/Headers/AnimationManager.h"

#include "Pipeline/Animation/Headers/SkeletonAnimation.h"

namespace Application {
namespace Animation {
  AnimationManager::AnimationManager()
  {}

  void AnimationManager::Initialize()
  {
  }

  void AnimationManager::Start()
  {
  }

  void AnimationManager::Update(const Core::Second& dt)
  {
    for (auto& animator : _animators)
    {
      animator.second.Update(dt);
    }
  }

  void AnimationManager::End()
  {
  }

  void AnimationManager::CleanUp()
  {
  }

  Core::instanceId<Animator> AnimationManager::CreateAnimator(Data::AssetManager& assetManager, const std::vector<Data::AssetName<Data::Rendering::SkeletonAnimationData>>& animations)
  {
    Core::instanceId<Animator> newAnimatorId = Core::GetInstanceId<Animator>();

    Animator newAnimator;

    for (const auto& animation : animations)
    {
      newAnimator.AddAnimation(CreateAnimation(assetManager, animation));
    }

    _animators.emplace(newAnimatorId, newAnimator);

    return newAnimatorId;
  }

  void AnimationManager::RemoveAnimator(const Core::instanceId<Animator>& animator)
  {
    _animators.erase(animator);
  }
}// namespace Animation
}// namespace Application