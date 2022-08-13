#pragma once

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetManager.h"

namespace Application {
namespace Internal
{
    template <typename OBJECT, typename ASSET>
    OBJECT CreateObject(const Data::AssetData<ASSET>& asset)
    {

    }
} // namespace Internal

template <typename OBJECT, typename ASSET>
OBJECT LoadAsset(Data::AssetManager& assetManager, const Data::AssetName<ASSET>& asset)
{
    const auto assetData = assetManager.getAssetData(asset);

    if (lock)
    {
        assetManager.lockAsset(asset);
    }

    Internal::CreateObject<T>(assetData);
}
}// namespace Application