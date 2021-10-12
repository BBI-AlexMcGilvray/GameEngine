#pragma once

#include "Pipeline/Animation/Headers/Animation.h"

#include "Data/Rendering/Headers/SkeletonAnimationData.h"
#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimationTrack.h"

namespace Application {
namespace Animation {
  struct SkeletonAnimation : public Animation
  {
    SkeletonAnimation(Data::AssetName<Data::Rendering::SkeletonAnimationData> data);

    void Evaluate(Core::Second time) override;
    Map<string, Core::Geometric::Transform> GetAnimationResults();

  private:
    Data::AssetData<Data::Rendering::SkeletonAnimationData> _data;
    SkeletonAnimationTrack _track;
    Map<string, Core::Geometric::Transform> _evaluationResults;
  };
}// namespace Animation
}// namespace Application
