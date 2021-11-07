#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimationMixer.h"

#include <utility>

#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimation.h"

namespace Application {
namespace Animation {
  SkeletonAnimationMixer::SkeletonAnimationMixer(SkeletonAnimatable &target)
    : AnimationMixer(&target), _target(target)
  {}

  // up to implementations to cast animation into specific animation types
  void SkeletonAnimationMixer::MixAnimation(float weight, Core::Ptr<Animation> value, Core::Second animationTime)
  {
    value->Evaluate(animationTime);
    _animationsToMix.push_back(MixData(weight, static_cast<SkeletonAnimation *>(value)->GetAnimationResults()));
  }

  void SkeletonAnimationMixer::Apply()
  {
    std::map<std::string, Core::Geometric::Transform> mixedTransforms;

    for (MixData mix : _animationsToMix) {
      for (std::pair<const std::string, Core::Geometric::Transform> &transform : mix.transforms) {
        if (mixedTransforms.find(transform.first) != mixedTransforms.end())
        {
          mixedTransforms[transform.first] = Core::Geometric::Transform();
        }

        Core::Geometric::Transform &combinedTransform = mixedTransforms[transform.first];

        combinedTransform.AdjustPosition(transform.second.GetPosition() * mix.weight);
        // combinedTransform.AdjustRotation(transform.second.GetRotation() * mix.weight); // broken, need to fix quaternion first
        combinedTransform.AdjustScale(transform.second.GetScale() * mix.weight);
      }
    }

    for (std::pair<const string, Core::Geometric::Transform> &transform : mixedTransforms) {
      _target.GetTarget().GetSkeletonHierarchy()->GetChild(transform.first)->Transformation.SetLocalPosition(transform.second.GetPosition());
      _target.GetTarget().GetSkeletonHierarchy()->GetChild(transform.first)->Transformation.SetLocalRotation(transform.second.GetRotation());
      _target.GetTarget().GetSkeletonHierarchy()->GetChild(transform.first)->Transformation.SetLocalScale(transform.second.GetScale());
    }
  }
}// namespace Animation
}// namespace Application