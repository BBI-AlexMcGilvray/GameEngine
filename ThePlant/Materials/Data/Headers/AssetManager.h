#pragma once

#include <map>

#include "Core/IO/Headers/IOUtils.h"

#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetExceptions.h"

#include "Core/Logging/Logger.h"

namespace Data {
// Should be made/held by whatever is using it (Pipeline -> ApplicationManager) where it can THEN be a singleton
// this way we have consistent behaviour for the base class, but we could have multiple instances
// (such as a longterm and a shortterm asset manager) that get managed based on use-case
class AssetManager
{
private:
    static constexpr char* TAG = "AssetManager";

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

    template <typename T>
    AssetData<T> getAssetData(const AssetName<T>& asset)
    {
        // static_cast type safety guaranteed by the type check in AssetName
        SharedPtr<const T> data = _hasAsset(asset) ? static_cast<WeakPtr<const T>>(_assets[asset]).lock() : _loadAsset(asset);

        if (data == nullptr)
        {
            DEBUG_THROW_EXCEPTION(FailureToLoad, TAG, "Failed to load the requested asset");
        }

        return AssetData<T>(asset, data);
    }

private:
    std::map<AssetName<void>, WeakPtr<void>> _assets;
    std::map<AssetName<void>, SharedPtr<void>> _lockedAssets;

    bool _hasAsset(const AssetName<void>& asset);
    bool _hasAssetLocked(const AssetName<void>& asset);

    template <typename T>
    SharedPtr<const T> _loadAsset(const AssetName<T>& asset)
    {
        File assetFile = OpenFileI(_getFilePath(asset));

        String assetData = assetFile.GetFullText();

        T instance;
        // read into file using visitor
        // add asset data into map
        
        SharedPtr<const T> loadedData = MakeShared<const T>(instance);
        _assets[asset] = WeakPtr<const T>(loadedData);

        return MakeShared<const T>(instance);
    }

    template <typename T>
    FilePath _getFilePath(const AssetName<T>& asset)
    {
        return FilePath{ GetCWD() + AssetType<T>::GetPath(), ToString(asset) + AssetType<T>::GetFileType() };
    }
};
} // namespace Data