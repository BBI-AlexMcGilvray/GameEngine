#include "Pipeline/Rendering/3D/Headers/ModelBase.h"

#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Geometric;

namespace Application {
namespace Rendering {
  InitialModelState::InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset)
  : InitialModelState(asset, Transform(), EntityId())
  {}

  InitialModelState::InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset, const EntityId& parent)
  : InitialModelState(asset, Transform(), parent)
  {}
  
  InitialModelState::InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset, const Transform& transform)
  : InitialModelState(asset, transform, EntityId())
  {}

  InitialModelState::InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset, const Transform& localTransform, const EntityId& parent)
  : asset(asset)
  , transform(localTransform)
  , parent(parent)
  {}

  InitialStaticModelState::InitialStaticModelState(const Data::AssetName<Data::Rendering::StaticModelData>& asset)
  : InitialStaticModelState(asset, Transform(), EntityId())
  {}

  InitialStaticModelState::InitialStaticModelState(const Data::AssetName<Data::Rendering::StaticModelData>& asset, const EntityId& parent)
  : InitialStaticModelState(asset, Transform(), parent)
  {}
  
  InitialStaticModelState::InitialStaticModelState(const Data::AssetName<Data::Rendering::StaticModelData>& asset, const Transform& transform)
  : InitialStaticModelState(asset, transform, EntityId())
  {}

  InitialStaticModelState::InitialStaticModelState(const Data::AssetName<Data::Rendering::StaticModelData>& asset, const Transform& localTransform, const EntityId& parent)
  : asset(asset)
  , transform(localTransform)
  , parent(parent)
  {}

  EntityId CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, ShaderManager& shaderManager, const InitialModelState& modelState)
  {
    Data::AssetData<Data::Rendering::SimpleModelData> assetData = assetManager.getAssetData(modelState.asset);
    
    EntityHandler creator;
    creator.AddComponent<MaterialComponent>(CreateMaterial(assetManager.getAssetData(assetData->material), shaderManager));
    creator.AddComponent<MeshComponent>(CreateMesh(assetManager.getAssetData(assetData->mesh)));
    creator.AddComponent<WorldTransformComponent>(Transform());

    if (modelState.parent.IsValid())
    {
      creator.AddComponent<ParentComponent>(modelState.parent);
      creator.AddComponent<LocalTransformComponent>(Transform());
    }

    // the below conditions may not be entirely valid, we may want to have explicit toggles for components in the model asset data
    // but that can be handled later
    // if (modelState.transform.GetPosition() != Float3(0.0f))
    {
      creator.AddComponent<PositionComponent>(modelState.transform.GetPosition());
    }
    // if (modelState.transform.GetScale() != Float3(1.0f))
    {
      creator.AddComponent<ScaleComponent>(modelState.transform.GetScale());
    }
    // if (modelState.transform.GetRotation() != FQuaternion(Core::Math::II()))
    {
      creator.AddComponent<RotationComponent>(modelState.transform.GetRotation());
    }

    return ecsSystem.CreateEntity(creator);
  }

  EntityId CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, ShaderManager& shaderManager, const InitialStaticModelState& modelState)
  {
    Data::AssetData<Data::Rendering::StaticModelData> assetData = assetManager.getAssetData(modelState.asset);
    
    EntityHandler creator;
    creator.AddComponent<MaterialComponent>(CreateMaterial(assetManager.getAssetData(assetData->material), shaderManager));
    creator.AddComponent<MeshComponent>(CreateMesh(assetManager.getAssetData(assetData->mesh)));
    creator.AddComponent<WorldTransformComponent>(Transform());

    if (modelState.parent.IsValid())
    {
      creator.AddComponent<ParentComponent>(modelState.parent);
      creator.AddComponent<LocalTransformComponent>(Transform());
    }

    // the below conditions may not be entirely valid, we may want to have explicit toggles for components in the model asset data
    // but that can be handled later
    // if (modelState.transform.GetPosition() != Float3(0.0f))
    {
      creator.AddComponent<PositionComponent>(modelState.transform.GetPosition());
    }
    // if (modelState.transform.GetScale() != Float3(1.0f))
    {
      creator.AddComponent<ScaleComponent>(modelState.transform.GetScale());
    }
    // if (modelState.transform.GetRotation() != FQuaternion(Core::Math::II()))
    {
      creator.AddComponent<RotationComponent>(modelState.transform.GetRotation());
    }

    return ecsSystem.CreateEntity(creator);
  }
}// namespace Rendering
}// namespace Application