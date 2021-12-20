#include "Pipeline/Rendering/3D/Headers/Skeleton.h"

#include "Core/Geometric/Headers/Transform.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntityCreator.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

using namespace Core;
using namespace Core::Math;

namespace Application {
namespace Rendering {
  EntityId CreateBone(ECS& ecs, const Data::Rendering::SkeletonBoneData& boneData, const EntityId& parent)
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
    // the bind matrix provided will be relative to the LocalTransformComponent, not the WorldTransformComponent - but that should make it more clear moving forwards as well
    creator.AddComponent<BoneComponent>(bindTransform.GetInverseTransformationMatrix());

    return ecs.CreateEntity(creator).GetEntityId();
  }

  std::vector<EntityId> AddChildBones(ECS& ecs, const Data::AssetData<Data::Rendering::SkeletonData>& skeletonData, const size_t& boneIndex, const EntityId& parent)
  {
    std::vector<EntityId> bones;

    const Data::Rendering::SkeletonBoneData& boneData = skeletonData->bones[boneIndex];

    EntityId newBone = CreateBone(ecs, boneData, parent);
    bones.push_back(newBone);

    size_t firstChildIndex = boneIndex + 1; // +1 because we added 'this' bone
    for (size_t child = 0; child < boneData.children; ++child)
    {
      auto childBones = AddChildBones(ecs, skeletonData, firstChildIndex + child, newBone);
      bones.insert(bones.end(), childBones.begin(), childBones.end());
    }

    return bones;
  }

  SkeletonComponent CreateSkeleton(ECS& ecs, const Data::AssetData<Data::Rendering::SkeletonData>& skeletonData, const EntityId& parent)
  {
    SkeletonComponent skeleton;

    // we assume the first bone is the root of the skeleton (parent to all other bones)
    std::vector<EntityId> allBones = AddChildBones(ecs, skeletonData, 0, parent);
    VERIFY(allBones.size() <= 50); // we only support up to 50 bones
    std::copy(allBones.begin(), allBones.end(), skeleton.entityArray.begin());

    return skeleton;
  }
}// namespace Rendering
}// namespace Application