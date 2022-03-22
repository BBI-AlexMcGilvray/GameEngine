#include "Pipeline/Animation/Headers/Animator.h"

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Animation {
  Core::Hash Animator::AddAnimation(const Core::Hash& name, Animation&& animation)
  {
    if (_animations.find(name) == _animations.end()) {
      _animations[name] = std::move(animation);
    } else {
      DEBUG_THROW("Animator", "Animation with given name already exists!");
    }

    return name;
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
    _PlayAnimation(name, false);
  }

  void Animator::RepeatAnimation(const Core::Hash& name)
  {
    _PlayAnimation(name, true);
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

      const Core::Second duration = _animations[_currentAnimation.name].GetDuration();
      if (duration < _currentAnimation.time)
      {
        if (_currentAnimation.repeating)
        {
          _currentAnimation.time = _currentAnimation.time - duration;
        }
        else
        {
          _animating = false;
        }
      }
      _currentAnimation.time = std::min(_currentAnimation.time, duration);
    }
  }

  void Animator::_PlayAnimation(const Core::Hash& name, bool repeat)
  {
    DEBUG_ASSERT(_animations.find(name) != _animations.end());
    if (name == _currentAnimation.name) {
      return;
    }

    _currentAnimation = AnimationState(name, repeat);
    _animating = true;
  }
}// namespace Animation
}// namespace Application