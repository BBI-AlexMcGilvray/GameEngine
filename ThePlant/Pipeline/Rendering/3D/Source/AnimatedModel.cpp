#include "Pipeline/Rendering/3D/Headers/AnimatedModel.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/Animation/Headers/Animator.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECSSystems/AnimationComponents.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/Rendering/3D/Headers/Skeleton.h"

using namespace Core;

namespace Application {
namespace Rendering {
  InitialAnimatedModelState::InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset)
  : InitialAnimatedModelState(asset, Core::Geometric::Transform(), EntityId())
  {}

  InitialAnimatedModelState::InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset, const EntityId& parent)
  : InitialAnimatedModelState(asset, Core::Geometric::Transform(), parent)
  {}
  
  InitialAnimatedModelState::InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset, const Core::Geometric::Transform& transform)
  : InitialAnimatedModelState(asset, transform, EntityId())
  {}

  InitialAnimatedModelState::InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset, const Core::Geometric::Transform& localTransform, const EntityId& parent)
  : asset(asset)
  , transform(localTransform)
  , parent(parent)
  {}

  EntityHandler& CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, Animation::AnimationManager& animationManager, ShaderManager& shaderManager, const InitialAnimatedModelState& modelState)
  {
    Data::AssetData<Data::Rendering::AnimatedModelData> assetData = assetManager.getAssetData(modelState.asset);
    
    Data::AssetData<Data::Rendering::SkeletonData> skeletonData = assetManager.getAssetData(assetData->skeleton);

    EntityHandler& creator = ecsSystem.CreateEntity();

    creator.AddComponent<MaterialComponent>(CreateMaterial(assetManager.getAssetData(assetData->material), shaderManager));
    creator.AddComponent<SkinnedMeshComponent>(CreateMesh(assetManager.getAssetData(assetData->mesh), skeletonData));
    creator.AddComponent<WorldTransformComponent>(Core::Geometric::Transform());
    creator.AddComponent<SkeletonComponent>();

    if (modelState.parent.IsValid())
    {
      creator.AddComponent<ParentComponent>(modelState.parent);
      creator.AddComponent<LocalTransformComponent>(Core::Geometric::Transform());
    }

    // the below conditions may not be entirely valid, we may want to have explicit toggles for components in the model asset data
    // but that can be handled later
    // if (modelState.transform.GetPosition() != Core::Math::Float3(0.0f))
    {
      creator.AddComponent<PositionComponent>(modelState.transform.GetPosition());
    }
    // if (modelState.transform.GetScale() != Core::Math::Float3(1.0f))
    {
      creator.AddComponent<ScaleComponent>(modelState.transform.GetScale());
    }
    // if (modelState.transform.GetRotation() != Core::Math::FQuaternion(Core::Math::II()))
    {
      creator.AddComponent<RotationComponent>(modelState.transform.GetRotation());
    }

    // with this here, we are getting it twice (here and in CreateSkeleton below) - ideally we strip one of those calls
    // but we should still be able to create a skeleton from just an asset name
    // maybe all 'create' calls should have overloads for [AssetManager, AssetName] and [AssetData] (former redirects to the latter)
    bool isAnimated = (skeletonData->animations.size() > 0);
    if (isAnimated)
    {
      // register animations?
      auto animatorId = animationManager.CreateAnimator(assetManager, skeletonData->animations);
      creator.AddComponent<AnimatorComponent>(animatorId);
    }

    InitialSkeletonState skeletonState = InitialSkeletonState(assetData->skeleton, creator, ecsSystem.GetComponentFor<AnimatorComponent>(creator).animatorId);
    CreateSkeleton(ecsSystem, assetManager, skeletonState, ecsSystem.GetComponentFor<SkeletonComponent>(creator));

    return creator;
  }
}// namespace Rendering
}// namespace Application