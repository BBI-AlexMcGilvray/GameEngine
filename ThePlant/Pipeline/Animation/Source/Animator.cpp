#include "Pipeline/Animation/Headers/Animator.h"

#include "Core/Logging/Logger.h"

namespace Application {
namespace Animation {
  Core::Hash Animator::AddAnimation(const Animation& animation)
  {
    if (_animations.find(animation.GetName()) != _animations.end()) {
      _animations[animation.GetName()] = animation;
    } else {
      DEBUG_THROW("Animator", "Animation with given name already exists!");
    }
  }

  void Animator::RemoveAnimation(const Core::Hash name)
  {
    if (_animations.find(name) != _animations.end()) {
      _animations.erase(name);
    } else {
      DEBUG_THROW("Animator", "Trying to remove animation that does not exist");
    }
  }


  void Animator::PlayAnimation(const Core::Hash& name)
  {
    if (name == _currentAnimation.name) {
      return;
    }

    _currentAnimation = AnimationState(name);
    _animating = true;
  }

  void Animator::StopAnimation(const Core::Hash& name)
  {
    ASSERT(_currentAnimation.name == name);

    _animating = false;
  }

  void Animator::Update(const Core::Second& dt)// continues current animations
  {
    if (_animating) {
      _currentAnimation.time += dt;
    }
  }
}// namespace Animation
}// namespace Application