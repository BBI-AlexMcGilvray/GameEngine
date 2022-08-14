#include "Pipeline/AssetHandling/EntityFactory.h"

#include "Pipeline/Headers/ApplicationManager.h"

namespace Application {
EntityFactory::EntityFactory(AssetLoaderFactory& assetLoader, Data::AssetManager& assetManager)
: _assetManager(assetManager)
, _assetLoader(assetLoader)
{}

EntityId EntityFactory::CreateEntity(ECS& ecs, const Data::AssetName<Data::EntityData>& asset)
{
    return _CreateEntity(ecs, asset, false);
}

EntityId EntityFactory::CreateEntityAndLockAsset(ECS& ecs, const Data::AssetName<Data::EntityData>& asset)
{
    return _CreateEntity(ecs, asset, true);
}

EntityId EntityFactory::_CreateEntity(ECS& ecs, const Data::AssetName<Data::EntityData>& asset, bool lock)
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
}// namespace Application