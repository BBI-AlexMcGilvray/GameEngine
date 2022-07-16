#pragma once

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetExceptions.h"
#include "Data/Headers/AssetLocation.h"

#include "Data/RawAssets/RawAsset.h"

namespace Data {
RawAsset ReadData(const AssetLocation& location);

template <typename T>
T DeserializeData(const RawAsset& data)
{
    T object;

    // need to throw exception for now if data is not json
    Serialization::Format::JSON parsedAssetData;
    parsedAssetData.Parse(assetData);

    DeserializeTo(object, parsedAssetData);

    return object;
}
}// namespace Data