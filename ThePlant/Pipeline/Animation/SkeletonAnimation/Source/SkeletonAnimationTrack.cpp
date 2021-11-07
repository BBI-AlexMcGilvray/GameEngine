#include "Pipeline/Animation/SkeletonAnimation/Headers/SkeletonAnimationTrack.h"

#include <utility>

#include "Core/Logging/Logger.h"
#include "Data/Headers/AssetExceptions.h"

#include "Pipeline/Geometric/Headers/Node.h"
#include "Pipeline/Rendering/3D/Headers/Bone.h"

namespace Application {
namespace Animation {
  SkeletonAnimationTrack::SkeletonAnimationTrack(const Data::AssetData<Data::Rendering::SkeletonAnimationData> &data)
  {
    int index = 0;
    for (const Data::Rendering::BoneAnimationData& boneAnimationData : data->boneAnimations)
    {
      // the data is not stored in correct order, so we can't do it this way - we need to get the skeleton get the index right
      SetTrack(boneAnimationData.name, TransformAnimationTrack(boneAnimationData));
      index++;
    }
  }

  void SkeletonAnimationTrack::SetTrack(string boneName, TransformAnimationTrack animationTrack)
  {
    if (_tracks.find(boneName) != _tracks.end())
    {
      _tracks[boneName] = animationTrack;
    }

    DEBUG_THROW_EXCEPTION(Data::InvalidAsset, "SkeletonAnimationTrack", "Bone index " + boneName + " already being affected by an animationtrack");
  }

  void SkeletonAnimationTrack::SetStartState(const Rendering::Skeleton &skeleton)
  {
    Core::Ptr<Rendering::Bone> hierarchy = skeleton.GetSkeletonHierarchy();
    CreateStartState(hierarchy, 0);
  }

  std::map<string, Core::Geometric::Transform> SkeletonAnimationTrack::Evaluate(Core::Second time)
  {
    std::map<string, Core::Geometric::Transform> skeleton;

    for (std::pair<const string, TransformAnimationTrack> &pair : _tracks) {
      skeleton[pair.first] = pair.second.Evaluate(time);
    }

    return skeleton;
  }

  int SkeletonAnimationTrack::CreateStartState(Core::Ptr<Geometric::Node> rootBone, int index)
  {
    _startState[index] = rootBone->Transformation.GetLocalTransform();

    int offset = 0;
    for (Core::Ptr<Geometric::Node> child : rootBone->GetChildren()) {
      offset++;
      offset += CreateStartState(child, index + offset);
    }

    return offset;
  }
}// namespace Animation
}// namespace Application