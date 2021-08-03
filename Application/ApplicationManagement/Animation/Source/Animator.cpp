#include "ApplicationManagement/Animation/Headers/Animator.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application {
namespace Animation {
  Animator::Animator(Core::Ptr<Animatable> animatable)
  {
    SetAnimatable(animatable);
  }

  void Animator::SetAnimatable(Core::Ptr<Animatable> animatable)
  {
    _animatable = animatable;
  }

  Core::Ptr<Animatable> Animator::GetAnimatable()
  {
    return _animatable;
  }

  void Animator::AddAnimation(Core::Hash name, Core::SharedPtr<Animation> data)
  {
    if (!Core::In(_animations, name)) {
      _animations[name] = data;
    } else {
      ALERT("Animation with given name already exists!");
    }
  }

  void Animator::RemoveAnimation(Core::Hash name)
  {
    if (Core::In(_animations, name)) {
      Core::Erase(_animations, name);
    } else {
      ALERT("Trying to remove animation that does not exist");
    }
  }


  void Animator::PlayAnimation(Core::Hash name, Core::Second transitionTime)
  {
    if (name == _currentAnimation.name) {
      return;
    }

    _transition = TransitionData(_currentAnimation, transitionTime);
    _currentAnimation = AnimationState(name);

    _animating = true;
  }

  void Animator::StopAnimation(Core::Hash name, Core::Second stopTime)
  {
    ASSERT(_currentAnimation.name == name);

    _transition = TransitionData(_currentAnimation, stopTime);
    _animating = false;
  }

  void Animator::Update(Core::Second dt)// continues current animations
  {
    Core::Ptr<AnimationMixer> mixer = _animatable->GetMixer();

    if (_animating) {
      _currentAnimation.animationTime += dt;
      mixer->MixAnimation(_currentAnimation.weight, _animations[_currentAnimation.name].get(), _currentAnimation.animationTime);
    }

    if (_transition.transitioning && _transition.transitionTimeLeft > Core::Second(0)) {
      _transition.state.animationTime += dt;
      mixer->MixAnimation(_transition.state.weight, _animations[_transition.state.name].get(), _transition.state.animationTime);

      _transition.transitionTimeLeft -= dt;
      _transition.transitioning = _transition.transitionTimeLeft > Core::Second(0);
    }

    // this may need to be handled by the manager to better allow for multiple animators to be affecting the same mixer
    mixer->Apply();
  }
}// namespace Animation
}// namespace Application