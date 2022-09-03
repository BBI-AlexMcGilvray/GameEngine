#pragma once

#include "Core/Headers/Factory.h"

#include "Data/Headers/AssetName.h"
#include "Data/AssetTypes/EntityData.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
struct ApplicationManager;
struct State;
using AssetProcessor = Core::HashFactory<void, State&, const Data::AssetName<void>&>;

// this loads assets (ex: puts materials in the material manager)
// but it doesn't allow for easy connections of those assets (ex: if a given material component references that material)
// presumably that would be handled by the EntityFactory
/*
ex:
    - create entity
        - create each component
            - material component knows asset name for material
            - load material from here
            - get resultant material from the material manager
*/
// but how then would we tell the material manager to release/destroy a given material?
// given the above and other things, we may not want the various asset managers (material, mesh, ...) to use InstanceId's but instead have them use AssetName's (so they _could_ be referenced directly)

// example behaviour: NOTE -> in this case, in State::Start we register a handler for entities in the AssetLoaderFactory and unregister it in State::Stop (need to make sure Stop() is called on existing state before Start() is called on new one)
//      in other cases (like for most managers) the constructors should be added on construction and removed on destruction
// AssetLoaderFactory.Register(HashType<EntityData>, [ecs&](ApplicationManager& applicationManager, const Data::AssetName<void>& asset)
// {
//      applicationManager.EntityFactory().CreateEntity(ecs, asset);
// })
class AssetLoaderFactory : public AssetProcessor
{
public:
    AssetLoaderFactory(ApplicationManager& applicationManager);

    ~AssetLoaderFactory() = default;

    void LoadAsset(const Data::AssetName<void>& asset);
    void LoadAsset(State& state, const Data::AssetName<void>& asset);
    void LoadAndLockAsset(const Data::AssetName<void>& asset);
    void LoadAndLockAsset(State& state, const Data::AssetName<void>& asset);

private:
    ApplicationManager& _applicationManager;
    
    void _LoadAsset(State& state, const Data::AssetName<void>& asset, bool lock);
};
}// namespace Application