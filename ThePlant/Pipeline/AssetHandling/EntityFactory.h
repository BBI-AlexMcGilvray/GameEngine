#pragma once

#include "Core/Headers/Factory.h"
#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetManager.h"
#include "Data/AssetTypes/EntityData.h"

#include "Pipeline/AssetHandling/AssetLoaderFactory.h"
#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
struct ApplicationManager;

using ComponentFactory = Core::HashFactory<void, EntityHandler&, const Core::Serialization::Format::JSON&>;

// This returns an explicit EntityId because the only things should be possible to directly load/create from code are entities
// it makes no sense to diretly register things like materials
// though if we wanted to, you create it, then reference it directly through the manager instead
class EntityFactory : public ComponentFactory
{
public:
    EntityFactory(AssetLoaderFactory& assetLoader, Data::AssetManager& assetManager);
    ~EntityFactory() = default;

    EntityId CreateEntity(ECS& ecs, const Data::AssetName<Data::EntityData>& asset);
    EntityId CreateEntityAndLockAsset(ECS& ecs, const Data::AssetName<Data::EntityData>& asset);

private:
    Data::AssetManager& _assetManager;
    AssetLoaderFactory& _assetLoader;
    
    EntityId _CreateEntity(ECS& ecs, const Data::AssetName<Data::EntityData>& asset, bool lock);
};
}// namespace Application