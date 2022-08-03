#pragma once

#include "Core/Geometric/Transform.h"

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetManager.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"

#include "Pipeline/Animation/Headers/AnimationManager.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/Rendering/Shaders/ShaderManager.h"

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

  /*
  NOTE: The 'Woman' model has fucked up scales that have been manually changed in the generated skeleton asset file - that may be a problem if we regenerate it
  */

  EntityHandler& CreateModel(ECS& ecsSystem, Data::AssetManager& assetManager, Animation::AnimationManager& animationManager, ShaderManager& shaderManager, const InitialAnimatedModelState& modelState);
}// namespace Rendering
}// namespace Application