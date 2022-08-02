#include "Pipeline/Rendering/3D/Headers/Skeleton.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Geometric/Transform.h"
#include "Core/Math/Headers/MatrixFunctions.h"

#include "Pipeline/Animation/Headers/Animator.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

using namespace Core;
using namespace Core::Math;

namespace Application {
namespace Rendering {
  InitialSkeletonState::InitialSkeletonState(const Data::AssetName<Data::Rendering::SkeletonData>& asset, const EntityId& parent, const Core::instanceId<Animation::Animator> animatorId)
  : asset(asset)
  , parent(parent)
  , animatorId(animatorId)
  {}

  namespace BoneCreationHelper
  {
    struct BoneCreationData
    {
      Core::Geometric::Transform rootBone;
      const Core::instanceId<Animation::Animator> animatorId;

      BoneCreationData(const Core::Geometric::Transform& rootBone, const Core::instanceId<Animation::Animator>& animatorId)
      : rootBone(rootBone)
      , animatorId(animatorId)
      {}
    };
  }

  EntityId CreateBone(ECS& ecsSystem, const Data::Rendering::SkeletonBoneData& boneData, const EntityId& parent, Core::Geometric::Transform& parentTransform, BoneCreationHelper::BoneCreationData& creationData)
  {
    EntityHandler& creator = ecsSystem.CreateEntity();

    Core::Geometric::Transform bindTransform(boneData.position, boneData.rotation, boneData.scale);
    Core::Geometric::Transform localTransform = parentTransform.GetInverseTransformationMatrix() * bindTransform.GetTransformationMatrix();

    creator.AddComponent<ParentComponent>(parent);
    creator.AddComponent<LocalTransformComponent>();
    // we may want to have a flag for if a given bone can/should have a world transform component (only needed if we want to be able to make it a parent to other entities)
    creator.AddComponent<WorldTransformComponent>();
    creator.AddComponent<PositionComponent>(localTransform.GetPosition());
    creator.AddComponent<ScaleComponent>(localTransform.GetScale());
    creator.AddComponent<RotationComponent>(localTransform.GetRotation());

    // steps written our for clarity
    Core::Math::Float4x4 inverseRootBoneMatrix = creationData.rootBone.GetInverseTransformationMatrix();
    Core::Math::Float4x4 initialBoneMatrix = bindTransform.GetTransformationMatrix();
    Core::Math::Float4x4 relativeToRootBoneMatrix = initialBoneMatrix * inverseRootBoneMatrix;
    Core::Math::Float4x4 bindMatrix = Core::Math::Inverse(relativeToRootBoneMatrix);
    creator.AddComponent<BoneComponent>(localTransform, bindMatrix);

    if (creationData.animatorId.IsValid())
    {
      // animator id to know what animator to use, name so the animator knows how this bone is animated
      creator.AddComponent<AnimationComponent>(creationData.animatorId, Core::HashValue(boneData.name));
    }

    return creator;
  }

  std::vector<std::pair<Core::Hash, Application::EntityId>> AddChildBones(ECS& ecsSystem, const Data::AssetData<Data::Rendering::SkeletonData>& skeletonData, const size_t& boneIndex, const EntityId& parent, Core::Geometric::Transform& parentTransform, BoneCreationHelper::BoneCreationData& creationData)
  {
    SCOPED_MEMORY_CATEGORY("ECS");
    std::vector<std::pair<Core::Hash, Application::EntityId>> bones;

    const Data::Rendering::SkeletonBoneData& boneData = skeletonData->bones[boneIndex];

    EntityId newBone = CreateBone(ecsSystem, boneData, parent, parentTransform, creationData);
    bones.push_back({ Core::HashValue(boneData.name), newBone });

    size_t childIndex = boneIndex + 1; // +1 because we added 'this' bone
    Core::Geometric::Transform boneTransform(boneData.position, boneData.rotation, boneData.scale);
    for (size_t child = 0; child < boneData.children; ++child)
    {
      auto childBones = AddChildBones(ecsSystem, skeletonData, childIndex, newBone, boneTransform, creationData);
      childIndex += childBones.size();
      bones.insert(bones.end(), childBones.begin(), childBones.end());
    }

    return bones;
  }

  size_t GetBoneIndex(const Data::Rendering::SkeletonData& skeleton, const std::string& boneName)
  {
    size_t index = 0;
    for (auto& bone : skeleton.bones)
    {
      if (bone.name == boneName)
      {
        return index;
      }
      ++index;
    }

    throw std::exception("bone does not exist in skeleton");
  }

  void CreateSkeleton(ECS& ecsSystem, Data::AssetManager& assetManager, const InitialSkeletonState& skeletonState, SkeletonComponent& skeleton)
  {
    Data::AssetData<Data::Rendering::SkeletonData> assetData = assetManager.getAssetData(skeletonState.asset);

    const Data::Rendering::SkeletonBoneData& rootBoneData = assetData->bones[0];
    Core::Geometric::Transform rootBoneTransform(rootBoneData.position, rootBoneData.rotation, rootBoneData.scale);
    BoneCreationHelper::BoneCreationData creationData = BoneCreationHelper::BoneCreationData(rootBoneTransform, skeletonState.animatorId);

    // we assume the first bone is the root of the skeleton (parent to all other bones)
    std::vector<std::pair<Core::Hash, Application::EntityId>> allBones = AddChildBones(ecsSystem, assetData, 0, skeletonState.parent, rootBoneTransform, creationData);
    DEBUG_ASSERT(allBones.size() <= 50); // we only support up to 50 bones
    skeleton.rootBone = allBones[0].second; // root bone is created first
    std::copy(allBones.begin(), allBones.end(), skeleton.nameAndEntities.begin());
  }
}// namespace Rendering
}// namespace Application