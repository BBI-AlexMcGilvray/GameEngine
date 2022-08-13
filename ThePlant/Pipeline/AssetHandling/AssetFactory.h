#pragma once

#include "Core/Headers/Factory.h"

#include "Data/Headers/AssetName.h"
#include "Data/AssetTypes/EntityData.h"

#include "Pipeline/ECS/DataOriented/ECS.h"
#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Application {
struct ApplicationManager;
using AssetProcessor = Core::HashFactory<void, ApplicationManager&, const Data::AssetName<void>&>;

class FromAssetFactory : AssetProcessor
{
public:
    FromAssetFactory(ApplicationManager& applicationManager)
    : _applicationManager(applicationManager)
    {}

    ~FromAssetFactory() = default;

    void LoadAsset(const Data::AssetName<void>& asset)
    {
        _LoadAsset(asset, false);
    }

    void LoadAndLockAsset(const Data::AssetName<void>& asset)
    {
        _LoadAsset(asset, true);
    }

private:
    ApplicationManager& _applicationManager;
    
    void _LoadAsset(const Data::AssetName<void>& asset, bool lock)
    {
        Create(asset.getType(), _applicationManager, asset);
    }
};
}// namespace Application