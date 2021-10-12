#pragma once

#include "Core/Headers/Hash.h"

#include "Pipeline/Animation/TransformAnimation/Headers/TransformAnimationTrack.h"
#include "Pipeline/Rendering/3D/Headers/Skeleton.h"

namespace Application {
namespace Animation {
  class SkeletonAnimationTrack
  {
  public:
    SkeletonAnimationTrack(const Data::AssetData<Data::Rendering::SkeletonAnimationData> &data);

    void SetTrack(string boneName, TransformAnimationTrack animationTrack);

    void SetStartState(const Rendering::Skeleton &skeleton);
    Core::Map<string, Core::Geometric::Transform> Evaluate(Core::Second time);

  private:
    Core::List<Core::Geometric::Transform> _startState;

    // <bone name, animation track>
    Core::Map<string, TransformAnimationTrack> _tracks;

    int CreateStartState(Core::Ptr<Geometric::Node> rootBone, int index);
  };
}// namespace Animation
}// namespace Application