#pragma once

#include <map>

#include "Core/Geometric/Headers/Transform.h"

#include "Pipeline/Animation/FieldAnimation/Headers/FloatAnimationTrack.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"

namespace Application {
namespace Animation {
  class TransformAnimationTrack
  {
  public:
    enum class TransformTarget {
      P_X,
      P_Y,
      P_Z,
      R_X,
      R_Y,
      R_Z,
      R_W,
      S_X,
      S_Y,
      S_Z
    };

    TransformAnimationTrack() = default;
    TransformAnimationTrack(const Data::Rendering::BoneAnimationData &data);
    // maybe a constructor to take a serialized animation curve?

    void SetTrack(TransformTarget target, FloatAnimationTrack animationTrack);

    void SetStartState(const Core::Geometric::Transform &transform);
    Core::Geometric::Transform Evaluate(Core::Second time);

  private:
    Core::Geometric::Transform _startState;

    std::map<TransformTarget, FloatAnimationTrack> _tracks;
  };
}// namespace Animation
}// namespace Application