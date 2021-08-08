#pragma once

#include "Pipeline/Animation/Headers/AnimationCurve.h"

namespace Application {
namespace Animation {
  class FloatAnimationTrack
  {
  private:
    AnimationCurve _curve;

  public:
    FloatAnimationTrack() = default;
    FloatAnimationTrack(AnimationCurve curve);
    // maybe a constructor to take a serialized animation curve?

    void SetCurve(AnimationCurve curve);
    AnimationCurve &GetCurve();

    float Evaluate(Core::Second time);
  };
}// namespace Animation
}// namespace Application