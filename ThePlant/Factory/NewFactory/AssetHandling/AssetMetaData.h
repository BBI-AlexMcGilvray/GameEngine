#pragma once

#include "Data/Headers/AssetName.h"

// holds the referenced assets USED BY this asset and holds references to assets that USE this asset
namespace Factory
{
    // if we use the Data::AssetType stuff then we are locked to a particular location
    // if we want projects to be able to organize their content in a proper file structure, we need a more complex system
    // which begs the question - does the AssetName/AssetType/AssetData stuff need to be reworked?
    // AssetName = handle to object without data (type + handle?)
    //      * is the handle where we can put in the actual location stuff? i.e. remove it from the type?
    // AssetData = AssetName + actual data
    // AssetType = way to specify allowed asset types/info about that type (just a wrapper for the type? we can remove the file stuff and put that in an AssetHandle class?)

    /*
    * Plan: resuse the asset types (name, data, type) following the above layout. This does mean that runtime would by default have the same locations as when run in editor.
    * SO, when we 'package' the assets for runtime, we update the locations so that they are more streamlined (all meshes and in the one mesh folder)
    *   -> this will also allow us to do things like have different type of AssetHandles. ex: one that points to a file and one that points to a file and a position in the file (for when we use binary packaging instead of json)
    */

    struct AssetMeta
    {
        Data::AssetName<void> asset;
        std::vector<Data::AssetName<void>> references;
        std::vector<Data::AssetName<void>> owners;
    };

    template <typename T>
    Data::AssetName<T> GetAssetFromMetaData(const AssetMetaData& metaData);
    
    template <>
    std::vector<Data::AssetName<void>> GetReferencedAssetsFromMetaData(const AssetMetaData& metaData);

    template <typename T>
    std::vector<Asset<T>> GetOwningAssetsFromMetaData(const AssetMetaData& metaData);
} // namespace Factory