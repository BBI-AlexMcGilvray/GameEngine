#pragma once

#include "Core/IdTypes/InstanceId.h"

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/SkeletonData.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"

namespace Application {
namespace Animation
{
    struct Animator;
} // namespae Animation

namespace Rendering {
  struct InitialSkeletonState
  {
    const Data::AssetName<Data::Rendering::SkeletonData> asset;
    const EntityId& parent;
    const Core::instanceId<Animation::Animator> animatorId;

    InitialSkeletonState(const Data::AssetName<Data::Rendering::SkeletonData>& asset, const EntityId& parent, const Core::instanceId<Animation::Animator> animationId = Core::instanceId<Animation::Animator>());
  };

  void CreateSkeleton(ECS& ecsSystem, Data::AssetManager& assetManager, const InitialSkeletonState& skeletonState, SkeletonComponent& skeleton);
}// namespace Rendering
}// namespace Application