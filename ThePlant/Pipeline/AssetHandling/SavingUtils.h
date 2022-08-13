#pragma once

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetManager.h"
#include "Data/RawAssets/RawAsset.h"

namespace Application {
namespace Internal
{
    template <typename ASSET, typename OBJECT>
    Data::AssetData<ASSET> WriteAsset(const Data::AssetName<ASSET>& asset, const OBJECT& object)
    {

    }
} // namespace Internal

template <typename ASSET, typename OBJECT>
Data::AssetData<ASSET> SaveObject(const Data::AssetName<ASSET>& asset, const OBJECT& object)
{
    return WriteAsset(object);
}
}// namespace Application