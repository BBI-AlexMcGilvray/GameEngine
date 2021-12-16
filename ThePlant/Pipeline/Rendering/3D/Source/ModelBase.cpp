#include "Pipeline/Rendering/3D/Headers/ModelBase.h"

#include "Pipeline/ECSSystems/GeneralComponents.h"
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/RenderingComponents.h"

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

  Entity CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, const InitialModelState& modelState)
  {
    Data::AssetData<Data::Rendering::SimpleModelData> assetData = assetManager.getAssetData(modelState.asset);
    
    // ideally we find a way to create a tuple once and add to it (instead of many if-elses or altering the entity many times)
    // because we
    /*
    - only want the parent component if a parent is provided
    - only want a position component if the transform position != 0     [?]
    - only want a rotation component if the transform rotation != II()  [?]
    - only want a scale component if the transform scale != 0           [?]
    - only want a LocalTransformComponent if a parent is provided
    */

    if (modelState.parent.IsValid())
    {
      return ecsSystem.CreateEntity<ParentComponent
                                  , MaterialComponent
                                  , MeshComponent
                                  , PositionComponent
                                  , ScaleComponent
                                  , RotationComponent
                                  , WorldTransformComponent
                                  , LocalTransformComponent>(
                                    modelState.parent,
                                    CreateMaterial(assetData->material),
                                    CreateMesh(assetData->mesh),
                                    modelState.transform.GetPosition(),
                                    modelState.transform.GetScale(),
                                    modelState.transform.GetRotation(),
                                    Transform(),
                                    Transform()
                                  );
    }
    
    return ecsSystem.CreateEntity<MaterialComponent
                                , MeshComponent
                                , PositionComponent
                                , ScaleComponent
                                , RotationComponent
                                , WorldTransformComponent>(
                                  CreateMaterial(assetData->material),
                                  CreateMesh(assetData->mesh),
                                  modelState.transform.GetPosition(),
                                  modelState.transform.GetScale(),
                                  modelState.transform.GetRotation(),
                                  Transform()
                                );
  }
}// namespace Rendering
}// namespace Application