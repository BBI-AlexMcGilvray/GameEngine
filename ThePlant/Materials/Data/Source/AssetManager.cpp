#include "Data/Headers/AssetManager.h"

#include <utility>

namespace Data
{
    AssetManager::~AssetManager()
    {
        unlockAllAssets();
        cleanAssets();

        int retainedAssets = 0;
        for (const std::pair<AssetName<void>, WeakPtr<const void>>& pair : _assets)
        {
            ++retainedAssets;
        }

        if (retainedAssets > 0)
        {
            DEBUG_ERROR(TAG, "Deleting AssetManager while some assets are still being referenced");
        }
    }

    void AssetManager::unlockAsset(const AssetName<void>& asset)
    {
        if (_lockedAssets.find(asset) == _lockedAssets.end())
        {
            DEBUG_THROW_EXCEPTION(InvalidAssetOperation, TAG, "Unlocking asset that is not locked - verify logic");
        }
        _lockedAssets.erase(asset);
    }

    void AssetManager::unlockAllAssets()
    {
        for (const std::pair<AssetName<void>, SharedPtr<const void>>& pair : _lockedAssets)
        {
            unlockAsset(pair.first);
        }
    }

    void AssetManager::cleanAssets()
    {
        // not having the iterator incrementor higher up seems weird, look into cleaning up this code
        for (auto iter = _assets.begin(); iter != _assets.end();/* incrementation handled implicity if erased, or explicitly otherwise */) {
            if (iter->second.expired())
            {
                iter = _assets.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    bool AssetManager::_hasAsset(const AssetName<void>& asset)
    {
        auto stored = _assets.find(asset);
        if (stored == _assets.end())
        {
            return false;
        }

        return !(stored->second.expired());
    }

    bool AssetManager::_hasAssetLocked(const AssetName<void>& asset)
    {
        return _lockedAssets.find(asset) != _lockedAssets.end();
    }

    // debug
    void AssetManager::_AddUsedAssetLocation(const AssetName<void>& asset, const Core::IO::FilePath& filePath)
    {
        // AssetLocation location = { IndividualFile { filePath } };
        // _assetLocations.SetAssetLocation(asset, location);
    }

    void AssetManager::_SaveAssetPaths() const
    {

    }
    // \debug
} // namespace Data