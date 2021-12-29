#pragma once

#include <unordered_map>

#include "Core/Headers/TimeDefs.h"
#include "Core/IdTypes/InstanceId.h"

#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"

#include "Pipeline/Animation/Headers/Animator.h"

namespace Application {
namespace Animation {
  class AnimationManager
  {
    // ~ Need a way to handle animators no longer being relevant for the current state
    // ~ The animation manager should handle holding all animations and have them just be referenced by the animators to limit data footprint and have them accessible by all
  public:
    AnimationManager();

    void Initialize();
    void Start();

    void Update(const Core::Second& dt);

    void End();
    void CleanUp();

    Core::instanceId<Animator> CreateAnimator(Data::AssetManager& assetManager, const std::vector<Data::AssetName<Data::Rendering::SkeletonAnimationData>>& animations);

    void RemoveAnimator(const Core::instanceId<Animator>& animator);

  private:
    std::unordered_map<Core::instanceId<Animator>, Animator> _animators;
  };
}// namespace Animation
}// namespace Application