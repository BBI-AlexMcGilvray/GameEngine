#pragma once

#include "Core/Headers/Factory.h"
#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetManager.h"
#include "Data/AssetTypes/EntityData.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
using ComponentFactory = Core::HashFactory<void, EntityHandler&, const Core::Serialization::Format::JSON&>;

// This returns an explicit EntityId because the only things should be possible to directly load/create from code are entities
// it makes no sense to diretly register things like materials
// though if we wanted to, you create it, then reference it directly through the manager instead
class EntityFactory : ComponentFactory
{
public:
    EntityFactory(Data::AssetManager& assetManager)
    : _assetManager(assetManager)
    {}

    ~EntityFactory() = default;

    EntityId CreateEntity(ECS& ecs, const Data::AssetName<Data::EntityData>& asset)
    {
        _CreateEntity(ecs, asset, false);
    }

    EntityId CreateEntityAndLockAsset(ECS& ecs, const Data::AssetName<Data::EntityData>& asset)
    {
        _CreateEntity(ecs, asset, true);
    }

private:
    Data::AssetManager& _assetManager;
    
    EntityId _CreateEntity(ECS& ecs, const Data::AssetName<Data::EntityData>& asset, bool lock)
    {
        Data::AssetData<Data::EntityData> data = _assetManager.getAssetData(asset);
        if (lock)
        {
            _assetManager.lockAsset(asset);
        }

        auto& entityHandler = ecs.CreateEntity();
        for (const auto& component : data->components)
        {
            Create(Core::HashValue(component.componentType), entityHandler, component.componentData);
        }

        return entityHandler;
    }
};
}// namespace Application