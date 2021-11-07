#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimation.h"

#include "Data/Headers/AssetManager.h"

#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
namespace Animation {
  SkeletonAnimation::SkeletonAnimation(Data::AssetName<Data::Rendering::SkeletonAnimationData> data)
    : _data(ApplicationManager::AppAssetManager().getAssetData(data)), _track(_data)
  {}

  void SkeletonAnimation::Evaluate(Core::Second time)
  {
    _evaluationResults = _track.Evaluate(time);
  }

  std::map<string, Core::Geometric::Transform> SkeletonAnimation::GetAnimationResults()
  {
    return _evaluationResults;
  }
}// namespace Animation
}// namespace Application