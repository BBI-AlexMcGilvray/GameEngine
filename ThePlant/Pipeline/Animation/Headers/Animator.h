#pragma once

#include <unordered_map>

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Pipeline/Animation/Headers/Animation.h"

namespace Application {
namespace Animation {
  class Animator
  {
  public:
    Animator() = default;
    Animator(Animator&&) = default;
    Animator& operator=(Animator&&) = default;

    Animator(const Animator&) = delete;
    Animator& operator=(const Animator&) = delete;

    Core::Hash AddAnimation(const Core::Hash& name, Animation&& animation);
    void RemoveAnimation(const Core::Hash name);

    void PlayAnimation(const Core::Hash& name);

    void StopAnimation(const Core::Hash& name);

    void Update(const Core::Second& dt);// continues current animations

    template <typename ATTRIBUTE>
    bool AffectingTarget(const Core::Hash& target) const
    {
      return _animations.at(_currentAnimation.name).AffectsTarget<ATTRIBUTE>(target);
    }

    template <typename T, typename ATTRIBUTE>
    T Evaluate(const Core::Hash& target) const
    {
      return _animations.at(_currentAnimation.name).Evaluate<T, ATTRIBUTE>(target, _currentAnimation.time);
    }

  private:
    // the below two structs should be removed in favour of behaviuor trees in the future
    struct AnimationState
    {
      AnimationState() = default;

      AnimationState(const Core::Hash& name)
      : name(name)
      , time(Core::Second(0))
      {}

      Core::Second time;
      Core::Hash name;
    };

    bool _animating = false;// this is just the control of the current animation, it can be false and still be transitioning
    AnimationState _currentAnimation;

    std::unordered_map<Core::Hash, Animation> _animations;

    // worry about transitions and blending stuff later
  };
}// namespace Animation
}// namespace Application