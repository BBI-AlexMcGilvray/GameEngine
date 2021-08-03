#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Animation {
  class Animatable;
  class Animation;

  // in the case of a skeleton, each bone is an animatable and they each get a mixer - do we want each animatable to have a mixer? it kind of makes sense...
  // this allows us to mix each one separately if the animations do not affect all bones
  class AnimationMixer
  {
  public:
    AnimationMixer(Core::Ptr<Animatable> target);
    virtual ~AnimationMixer() = default;

    Core::Ptr<Animatable> &GetTarget();

    // up to implementations to cast animation into specific animation types
    virtual void MixAnimation(float weight, Core::Ptr<Animation> value, Core::Second animationTime) = 0;
    virtual void Apply() = 0;

  protected:
    // implementations should also have a T& to the target of the animatable
    Core::Ptr<Animatable> _target;
  };
}// namespace Animation
}// namespace Application