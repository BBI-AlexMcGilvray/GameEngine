#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimatable.h"

#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimationMixer.h"

namespace Application {
namespace Animation {
  SkeletonAnimatable::SkeletonAnimatable(Rendering::Skeleton &target)
    : _target(&target)
  {}

  SkeletonAnimatable::SkeletonAnimatable(const SkeletonAnimatable &other)
  {
    _target = other._target;
  }

  SkeletonAnimatable &SkeletonAnimatable::operator=(const SkeletonAnimatable &other)
  {
    _target = other._target;

    return *this;
  }

  Rendering::Skeleton &SkeletonAnimatable::GetTarget() const
  {
    return *_target;
  }

  void SkeletonAnimatable::CreateMixer()
  {
    _mixer = Core::MakeUnique<SkeletonAnimationMixer>(*this);
  }
}// namespace Animation
}// namespace Application