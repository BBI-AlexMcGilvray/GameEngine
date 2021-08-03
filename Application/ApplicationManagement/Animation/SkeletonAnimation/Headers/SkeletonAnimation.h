#pragma once

#include "ApplicationManagement/Animation/Headers/Animation.h"

#include "Data/Rendering/Headers/SkeletonAnimationData.h"
#include "ApplicationManagement/Animation/SkeletonAnimation/Headers/SkeletonAnimationTrack.h"

namespace Application {
namespace Animation {
  struct SkeletonAnimation : public Animation
  {
    SkeletonAnimation(Data::AssetName<Data::Rendering::SkeletonAnimationData> data);

    void Evaluate(Core::Second time) override;
    Map<string, Transform> GetAnimationResults();

  private:
    Data::AssetData<Data::Rendering::SkeletonAnimationData> _data;
    SkeletonAnimationTrack _track;
    Map<string, Transform> _evaluationResults;
  };
}// namespace Animation
}// namespace Application
