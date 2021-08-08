#include "Pipeline/Animation/Headers/Animatable.h"

#include "Pipeline/Animation/Headers/AnimationMixer.h"


namespace Application {
namespace Animation {
  Animatable::Animatable()
  {}

  Core::Ptr<AnimationMixer> Animatable::GetMixer()
  {
    if (_mixer == nullptr) {
      CreateMixer();
    }

    return _mixer.get();
  }
}// namespace Animation
}// namespace Application