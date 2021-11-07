#pragma once

#include <map>
#include <string>
#include <vector>

#include "Pipeline/Animation/Headers/AnimationMixer.h"

#include "Pipeline/Rendering/3D/Headers/Skeleton.h"
#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimatable.h"

namespace Application {
namespace Animation {
  class SkeletonAnimationMixer : public AnimationMixer
  {
  public:
    SkeletonAnimationMixer(SkeletonAnimatable &target);
    ~SkeletonAnimationMixer() = default;

    // up to implementations to cast animation into specific animation types
    void MixAnimation(float weight, Core::Ptr<Animation> value, Core::Second animationTime) override;
    void Apply() override;

  private:
    struct MixData
    {
      float weight;
      std::map<std::string, Core::Geometric::Transform> transforms;

      MixData(float weight, std::map<string, Core::Geometric::Transform> transform)
        : weight(weight), transforms(transform)
      {}
    };

    SkeletonAnimatable &_target;
    std::vector<MixData> _animationsToMix;
  };
}// namespace Animation
}// namespace Application