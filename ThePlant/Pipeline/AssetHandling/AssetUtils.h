#pragma once

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetManager.h"

#include "Pipeline/AssetHandling/LoadingUtils.h"
#include "Pipeline/AssetHandling/SavingUtils.h"

namespace Application {
template <typename OBJECT, typename ASSET>
OBJECT LoadAndLockAsset(Data::AssetManager& assetManager, const Data::AssetName<ASSET>& asset)
{
    return LoadAsset(assetManager, asset, true);
}

template <typename OBJECT, typename ASSET>
OBJECT LoadAsset(Data::AssetManager& assetManager, const Data::AssetName<ASSET>& asset)
{
    return LoadAsset(assetManager, asset, false);
}

template <typename ASSET, typename OBJECT>
Data::AssetData<ASSET> SaveObject(const Data::AssetName<ASSET>& asset, const OBJECT& object)
{
    return SaveObject(asset, object);
}
}// namespace Application