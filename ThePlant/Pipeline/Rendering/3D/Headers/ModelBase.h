#pragma once

#include "Core/Geometric/Headers/Transform.h"

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/SimpleModelData.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/Rendering/Shaders/ShaderManager.h"

namespace Application {
namespace Rendering {
  // creates the entity that will be used by a model
  struct InitialModelState
  {
    const Data::AssetName<Data::Rendering::SimpleModelData> asset;
    const EntityId parent = EntityId();
    const Core::Geometric::Transform transform; // transform is local if parent is provided

    InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset);
    InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset, const EntityId& parent);
    InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset, const Core::Geometric::Transform& transform);
    InitialModelState(const Data::AssetName<Data::Rendering::SimpleModelData>& asset, const Core::Geometric::Transform& localTransform, const EntityId& parent);
  };

  Entity CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, ShaderManager& shaderManager, const InitialModelState& modelState);
}// namespace Rendering
}// namespace Application