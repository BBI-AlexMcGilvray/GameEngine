#pragma once

#include "Core/IO/Headers/File.h"

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetExceptions.h"
#include "Data/Headers/AssetLocation.h"

#include "Data/RawAssets/RawAsset.h"
#include "Data/RawAssets/ReadUtils.h"
#include "Data/RawAssets/WriteUtils.h"

namespace Data {
template <typename T>
AssetData<T> LoadAsset(const AssetName<T>& asset)
{
    RawAsset rawAsset = ReadData(asset.location);
    return AssetData<T>(asset, std::make_shared<T>(DeserializeData(rawAsset)));
}

template <typename T, typename RAW_TYPE = RawString>
void SaveAsset(const AssetData<T>& asset)
{
    RawAsset rawAsset{ RAW_TYPE{} };
    SerializeData(rawAsset, asset._data);
    WriteData(rawAsset, asset._asset.location);
}
}// namespace Data