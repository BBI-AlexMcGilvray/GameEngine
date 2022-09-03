#include "Pipeline/AssetHandling/EntityFactory.h"

#include "Core/Headers/Hash.h"

#include "Pipeline/Headers/ApplicationManager.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Application {
EntityFactory::EntityFactory(AssetLoaderFactory& assetLoader, Data::AssetManager& assetManager)
: _assetManager(assetManager)
, _assetLoader(assetLoader)
{
    // by default, we load into the current state.
    // when states need to create their startup state in initialization, they should provide themselves as a direct argument
  _assetLoader.Register(Core::HashType<Data::EntityData>(), [&](Application::ApplicationManager& applicationManager, const Data::AssetName<void>& asset)
  {
      CreateEntity(applicationManager.StateManager().GetActiveState(), asset);
  });
}
   
EntityFactory::~EntityFactory()
{
  _assetLoader.Unregister(Core::HashType<Data::EntityData>());
}

EntityHandler& EntityFactory::CreateEntity(State& state, const Data::AssetName<Data::EntityData>& asset)
{
    return _CreateEntity(state, asset, false);
}

EntityHandler& EntityFactory::CreateEntityAndLockAsset(State& state, const Data::AssetName<Data::EntityData>& asset)
{
    return _CreateEntity(state, asset, true);
}

EntityHandler& EntityFactory::_CreateEntity(State& state, const Data::AssetName<Data::EntityData>& asset, bool lock)
{
    Data::AssetData<Data::EntityData> data = _assetManager.getAssetData(asset);
    if (lock)
    {
        _assetManager.lockAsset(asset);
    }

    auto& entityHandler = state.ECS().CreateEntity();
    for (const auto& component : data->components)
    {
        Create(Core::HashValue(component.componentType), entityHandler, component.componentData);
    }

    return entityHandler;
}
}// namespace Application