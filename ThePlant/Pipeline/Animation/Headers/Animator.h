#pragma once

#include "Core/Debugging/Headers/Macros.h"

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Headers/MapDefs.h"

#include "Pipeline/Animation/Headers/Animatable.h"
#include "Pipeline/Animation/Headers/AnimationMixer.h"
#include "Pipeline/Animation/Headers/Animation.h"

namespace Application {
namespace Animation {
  class Animator
  {
  public:
    Animator(Core::Ptr<Animatable> animatable);

    void SetAnimatable(Core::Ptr<Animatable> animatable);
    Core::Ptr<Animatable> GetAnimatable();

    // we probably want what animations are held to be driven through data?
    // how do we handle different animation types through a similar system?
    void AddAnimation(Core::Hash name, Core::SharedPtr<Animation> data);
    void RemoveAnimation(Core::Hash name);

    void PlayAnimation(Core::Hash name, Core::Second transitionTime);

    void StopAnimation(Core::Hash name, Core::Second stopTime);

    void Update(Core::Second dt);// continues current animations

  private:
    // the below two structs should be removed in favour of behaviuor trees in the future
    struct AnimationState
    {
      AnimationState() = default;

      AnimationState(Core::Hash name, float weight = 1.0f)
      {
        animationTime = Core::Second(0);
        name = name;
        weight = weight;
      }

      Core::Second animationTime;
      Core::Hash name;
      float weight;
    };

    struct TransitionData
    {
      TransitionData() = default;

      TransitionData(AnimationState state, Core::Second transitionTime)
      {
        state = state;
        transitionTimeLeft = transitionTime;
        transitioning = transitionTime != Core::Second(0);
      }

      bool transitioning;
      AnimationState state;
      Core::Second transitionTimeLeft;
    };

    bool _animating = false;// this is just the control of the current animation, it can be false and still be transitioning
    AnimationState _currentAnimation;

    Core::Ptr<Animatable> _animatable = nullptr;
    Core::Map<Core::Hash, Core::SharedPtr<Animation>> _animations;

    // until we have more complex logic, we will just use simple transition data to manage it - as such, we can only blend two animations at the moment
    TransitionData _transition;
    // in the future, we shoud have behaviour trees that dictate the flow from one animation to another based on state and such for smoother transitions
    // BehaviourTree _behaviourTree;
  };
}// namespace Animation
}// namespace Application