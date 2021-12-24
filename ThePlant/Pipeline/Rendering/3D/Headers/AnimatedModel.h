#pragma once

#include "Core/Geometric/Headers/Transform.h"

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"

#include "Pipeline/ECS/DataOriented/ECS.h"

namespace Application {
namespace Rendering {
  // creates the entity that will be used by a model
  struct InitialAnimatedModelState
  {
    const Data::AssetName<Data::Rendering::AnimatedModelData> asset;
    const EntityId parent = EntityId();
    const Core::Geometric::Transform transform; // transform is local if parent is provided

    InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset);
    InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset, const EntityId& parent);
    InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset, const Core::Geometric::Transform& transform);
    InitialAnimatedModelState(const Data::AssetName<Data::Rendering::AnimatedModelData>& asset, const Core::Geometric::Transform& localTransform, const EntityId& parent);
  };

  Entity CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, ShaderManager& shaderManager, const InitialAnimatedModelState& modelState);
}// namespace Rendering
}// namespace Application