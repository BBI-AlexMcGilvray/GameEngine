#include "Data/Headers/AssetManager.h"

namespace Data
{
    AssetManager& AssetManager::getInstance()
    {
        if (_instance == nullptr)
        {
            _instance = MakeUnique<AssetManager>();
        }

        return *_instance;
    }

    AssetManager::~AssetManager()
    {
        cleanAssets();

        int retainedAssets = 0;
        for (const Pair<AssetName<void>, WeakPtr<void>>& pair : _assets)
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
    #if _DEBUG
        if (_lockedAssets.find(asset) == _lockedAssets.end())
        {
            DEBUG_THROW(InvalidAssetOperation, TAG, "Unlocking asset that is not locked - verify logic");
        }
    #endif
        _lockedAssets.erase(asset);
    }

    void AssetManager::cleanAssets()
    {
        for (const Pair<AssetName<void>, WeakPtr<void>>& pair : _assets)
        {
            if (pair.second.expired())
            {
                _assets.erase(pair.first);
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
} // namespace Data