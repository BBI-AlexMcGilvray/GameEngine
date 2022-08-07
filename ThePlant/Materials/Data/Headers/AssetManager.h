#pragma once

#include <unordered_map>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/IO/Headers/IOUtils.h"
#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetExceptions.h"
#include "Data/Headers/AssetLocationMapping.h"
#include "Data/Headers/SerializationUtils.h"

#include "Core/Logging/LogFunctions.h"

namespace Data {
// Should be made/held by whatever is using it (Pipeline -> ApplicationManager) where it can THEN be a singleton
// this way we have consistent behaviour for the base class, but we could have multiple instances
// (such as a longterm and a shortterm asset manager) that get managed based on use-case
class AssetManager
{
private:
    static constexpr const char* TAG = "AssetManager";

public:
    AssetManager() = default;
    ~AssetManager();

    void cleanAssets();
    // locks the asset and prevents it from being destroyed - even if no longer referenced
    template <typename T>
    void lockAsset(const AssetName<T>& asset)
    {
        if (_hasAssetLocked(asset))
        {
            // do NOT double-lock assets
            DEBUG_THROW_EXCEPTION(InvalidAssetOperation, TAG, "Trying to lock asset multiple times");
            return;
        }

        _lockedAssets[asset] = getAssetData(asset);
    }

    // unlocks the asset if it was locked (does not necessarily clean the asset)
    void unlockAsset(const AssetName<void>& asset);
    void unlockAllAssets();

    template <typename T>
    AssetData<T> getAssetData(const AssetName<T>& asset)
    {
        cleanAssets(); // make sure we don't try to get non-held asset

        // static_cast type safety guaranteed by the type check in AssetName
        // it SHOULD be, but it isn't yet due to the fact that names can be shared across asset types
        SharedPtr<const T> data = _hasAsset(asset) ? std::static_pointer_cast<const T>(_assets[asset].lock()) : _loadAsset(asset); // can't do std::dynamic_pointer_cast since we are storing as SharedPtr<void>

        if (data == nullptr)
        {
            DEBUG_THROW_EXCEPTION(FailureToLoad, TAG, "Failed to load the requested asset");
        }

        return AssetData<T>(asset, data);
    }

private:
    AssetLocationMapping _assetLocations; // debug for now
    std::unordered_map<AssetName<void>, WeakPtr<const void>, AssetNameHasher<void>> _assets;
    std::unordered_map<AssetName<void>, SharedPtr<const void>, AssetNameHasher<void>> _lockedAssets;

    bool _hasAsset(const AssetName<void>& asset);
    bool _hasAssetLocked(const AssetName<void>& asset);

    template <typename T>
    SharedPtr<const T> _loadAsset(const AssetName<T>& asset)
    {
        // update this to use AssetLocationMapping (verify it works)
        // for starters it can be kinda hacky, then we can start working on the Factory and this at the same time
        SCOPED_MEMORY_CATEGORY("Assets");
        const auto assetPath = _getFilePath(asset);
        File assetFile = OpenFileI(assetPath);
        // debug
        // do this with used assets to make the first AssetLocationMapping to be used, then change how locations are used
        _AddUsedAssetLocation(asset, assetPath);
        // \debug

        std::string assetData = assetFile.GetFullText();

        // non-const to start for deserialization
        SharedPtr<T> loadedData = MakeShared<T>();

        Serialization::Format::JSON parsedAssetData;
        parsedAssetData.Parse(assetData);

        DeserializeTo(*loadedData, parsedAssetData);
        
        // // is now implicitly cast to const in storage
        _assets[asset] = loadedData; // need to store asset by AssetName AND AssetType (runtimeId_t)

        assetFile.Close();

        // return implicitly-cast const version
        return loadedData;
    }

    template <typename T>
    FilePath _getFilePath(const AssetName<T>& asset)
    {
        return FilePath{ GetCWD() + AssetType<T>::GetPath(), to_string(asset) + AssetType<T>::GetFileType() };
    }

    // debug
    void _AddUsedAssetLocation(const AssetName<void>& asset, const Core::IO::FilePath& filePath);
    void _SaveAssetPaths() const;
    // \debug
};
} // namespace Data