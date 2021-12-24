#include "Pipeline/Rendering/3D/Headers/AnimatedModel.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/ECS/DataOriented/EntityCreator.h"
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

  Entity CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, ShaderManager& shaderManager, const InitialAnimatedModelState& modelState)
  {
    Data::AssetData<Data::Rendering::AnimatedModelData> assetData = assetManager.getAssetData(modelState.asset);
    
    EntityCreator creator;
    creator.AddComponent<MaterialComponent>(CreateMaterial(assetManager.getAssetData(assetData->material), shaderManager));
    creator.AddComponent<MeshComponent>(CreateMesh(assetManager.getAssetData(assetData->mesh)));
    creator.AddComponent<WorldTransformComponent>(Core::Geometric::Transform());

    if (modelState.parent.IsValid())
    {
      creator.AddComponent<ParentComponent>(modelState.parent);
      creator.AddComponent<LocalTransformComponent>(Core::Geometric::Transform());
    }

    // the below conditions may not be entirely valid, we may want to have explicit toggles for components in the model asset data
    // but that can be handled later
    if (modelState.transform.GetPosition() != Core::Math::Float3(0.0f))
    {
      creator.AddComponent<PositionComponent>(modelState.transform.GetPosition());
    }
    if (modelState.transform.GetScale() != Core::Math::Float3(1.0f))
    {
      creator.AddComponent<ScaleComponent>(modelState.transform.GetScale());
    }
    if (modelState.transform.GetRotation() != Core::Math::FQuaternion(Core::Math::II()))
    {
      creator.AddComponent<RotationComponent>(modelState.transform.GetRotation());
    }

    auto animationData = assetData->animations;
    bool isAnimated = (animationData != nullptr && animationData->num > 0);
    if (isAnimated)
    {
      creator.AddComponent<AnimationComponent>(assetData->animations);
      // register animations?
    }

    Entity model = ecsSystem.CreateEntity(creator);

    InitialSkeletonState skeletonState = InitialSkeletonState(assetData->skeleton, model, ecsSystem.GetComponentFor<AnimationComponent>(model).animatorId);
    CreateSkeleton(ecsSystem, assetManager, skeletonState, ecsSystem.GetComponentFor<SkeletonComponent>(model));
  }
}// namespace Rendering
}// namespace Application