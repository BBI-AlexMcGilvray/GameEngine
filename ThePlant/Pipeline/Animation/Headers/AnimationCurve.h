#pragma once

#include <vector>
#include <tuple>

#include "Core/Headers/TimeDefs.h"

#include "Pipeline/Animation/Headers/Keyframe.h"

namespace Application {
namespace Animation {
  struct AnimationCurve
  {
  public:
    AnimationCurve();
    AnimationCurve(std::vector<Keyframe> keyframes);

    float Evaluate(Core::Second time) const;

  private:
    std::vector<Keyframe> _keyframes;

    std::tuple<Keyframe, Keyframe> GetClosestKeyframes(Core::Second time) const;
  };
}// namespace Animation
}// namespace Application