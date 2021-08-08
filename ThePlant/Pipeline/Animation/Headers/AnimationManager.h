#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/TimeDefs.h"

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

    void Update(Core::Second dt);

    void End();
    void CleanUp();

    template<typename T, typename... Ts>
    Core::Ptr<T> AddAnimator(Ts &&...args)
    {
      Core::UniquePtr<Animator> newAnimator = Core::MakeUnique<T>(Forward<Ts>(args)...);

      return static_cast<Ptr<T>>(AddAnimator(move(newAnimator)));
    }

    Core::Ptr<Animator> AddAnimator(Core::UniquePtr<Animator> animator);
    void RemoveAnimator(Core::Ptr<Animator> animator);

  private:
    // Should this not be ptrs at all to have contiguous memory?
    // ~ that would mean they would need to live here, and not on a component
    // ~ so components point to element held by array within the system instead of the other way around
    // ~ which is what we want!
    Core::List<Core::UniquePtr<Animator>> _animators;
  };
}// namespace Animation
}// namespace Application