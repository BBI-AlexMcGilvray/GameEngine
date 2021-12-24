#include "Pipeline/Rendering/3D/Headers/Skeleton.h"

#include "Core/Geometric/Headers/Transform.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "Pipeline/ECS/DataOriented/EntityCreator.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

using namespace Core;
using namespace Core::Math;

namespace Application {
namespace Rendering {
  InitialSkeletonState::InitialSkeletonState(const Data::AssetName<Data::Rendering::SkeletonData>& asset, const EntityId& parent, const Core::instanceId<Animator> animatorId = Core::instanceId<Animator>())
  : skeleton(asset)
  , parent(parent)
  , animatorId(animatorId)
  {}

  namespace BoneCreationHelper
  {
    struct BoneCreationData
    {
      const Core::Geometric::Transform rootBone;
      const Core::instanceId<Animator> animatorId;

      BoneCreationData(const Core::Geometric::Transform& rootBone, const Core::instanceId<Animator>& animatorId)
      : rootBone(rootBone)
      , animatorId(animatorId)
      {}
    };
  }

  EntityId CreateBone(ECS& ecsSystem, const Data::Rendering::SkeletonBoneData& boneData, const EntityId& parent, const BoneCreationHelper::BoneCreationData& creationData)
  {
    EntityCreator creator;

    Core::Geometric::Transform bindTransform(boneData.position, boneData.rotation, boneData.scale);

    creator.AddComponent<ParentComponent>(parent);
    creator.AddComponent<LocalTransformComponent>();
    // we may want to have a flag for if a given bone can/should have a world transform component (only needed if we want to be able to make it a parent to other entities)
    creator.AddComponent<WorldTransformComponent>();
    creator.AddComponent<PositionComponent>(bindTransform.GetPosition());
    creator.AddComponent<ScaleComponent>(bindTransform.GetScale());
    creator.AddComponent<RotationComponent>(bindTransform.GetRotation());

    // steps written our for clarity
    Core::Geometric::Float4x4 inverseRootBoneMatrix = creationData.rootBone.GetInverseTransformationMatrix();
    Core::Geometric::Float4x4 initialBoneMatrix = bindTransform.GetTransformationMatrix();
    Core::Geometric::Float4x4 relativeToRootBoneMatrix = inverseRootBoneMatrix * initialBoneMatrix;
    Core::Geometric::Float4x4 bindMatrix = Core::Math::Inverse(relativeToRootBoneMatrix);
    creator.AddComponent<BoneComponent>(bindMatrix);

    if (animatorId.IsValid())
    {
      creator.AddComponent<AnimationComponent>(creationData.animatorId);
    }

    return ecsSystem.CreateEntity(creator).GetEntityId();
  }

  std::vector<EntityId> AddChildBones(ECS& ecsSystem, const Data::AssetData<Data::Rendering::SkeletonData>& skeletonData, const size_t& boneIndex, const EntityId& parent, const BoneCreationHelper::BoneCreationData& creationData)
  {
    std::vector<EntityId> bones;

    const Data::Rendering::SkeletonBoneData& boneData = skeletonData->bones[boneIndex];

    EntityId newBone = CreateBone(ecsSystem, boneData, parent, creationData);
    bones.push_back(newBone);

    size_t firstChildIndex = boneIndex + 1; // +1 because we added 'this' bone
    for (size_t child = 0; child < boneData.children; ++child)
    {
      auto childBones = AddChildBones(ecsSystem, skeletonData, firstChildIndex + child, newBone, creationData);
      bones.insert(bones.end(), childBones.begin(), childBones.end());
    }

    return bones;
  }

  void CreateSkeleton(ECS& ecsSystem, Data::AssetManager& assetManager, const InitialSkeletonState& skeletonState, SkeletonComponent& skeleton)
  {
    Data::AssetData<Data::Rendering::SkeletonData> assetData = assetManager.getAssetData(skeletonState.asset);

    const Data::Rendering::SkeletonBoneData& rootBoneData = assetData->bones[0];
    Core::Geometric::Transform rootBoneTransform(rootBoneData.position, rootBoneData.rotation, rootBoneData.scale);
    BoneCreationHelper::BoneCreationData creationData = BoneCreationHelper::BoneCreationData(rootBoneTransform, skeletonState.animatorId);

    // we assume the first bone is the root of the skeleton (parent to all other bones)
    std::vector<EntityId> allBones = AddChildBones(ecsSystem, assetData, 0, skeletonState.parent, creationData);
    VERIFY(allBones.size() <= 50); // we only support up to 50 bones
    std::copy(allBones.begin(), allBones.end(), skeleton.entityArray.begin());
  }
}// namespace Rendering
}// namespace Application