#pragma once

#include "Core/IO/Headers/File.h"
#include "Core/IdTypes/UUID.h"

#include "Data/Headers/AssetName.h"

// represents a file (asset) that has been stored
namespace Factory
{
    struct AssetMetaData;

    struct AssetFileHandle
    {
        Core::UUID uuid;
        Core::IO::FilePath path;
    };

    // Need only ONE asset instance per actual asset! otherwise saving/updating stuff could very easily break!
    template <typename T>
    struct Asset
    {
        AssetFileHandle handle;
        Data::AssetName<T> asset;
        // meta data?

        // how can this be templatized such that it works as void?
        // actual data? <- probably, will need to reference the data and if we don't the handle should be used instead
    };

    template <>
    struct Asset<void>
    {
        AssetFileHandle handle;
        Data::AssetName<void> asset;
        // meta data?

        // no actual data, needs to be treated/converted to the right asset type to get the data (should this be allowed? seems bad -> no -> assets are all strongly typed ONLY)
        // maybe we want to use inheritance here, have a base asset type so that assets can also be stored in a single vector and such (or we do pointers to void like for the asset manager)
    };

    template <typename T>
    AssetMetaData GetMetaDataForAsset(const Asset<T>& asset);
} // namespace Factory