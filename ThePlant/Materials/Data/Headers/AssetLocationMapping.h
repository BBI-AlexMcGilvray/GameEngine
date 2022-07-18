#pragma once

#include <unordered_map>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetExceptions.h"
#include "Data/Headers/AssetLocation.h"

#include "Core/Logging/LogFunctions.h"

namespace Data {
// Should be made/held by whatever is using it (Pipeline -> ApplicationManager) where it can THEN be a singleton
// this way we have consistent behaviour for the base class, but we could have multiple instances
// (such as a longterm and a shortterm asset manager) that get managed based on use-case
class AssetLocationMapping
{
private:
    static constexpr const char* TAG = "AssetLocationMapping";

public:
    AssetLocationMapping() = default;
    ~AssetLocationMapping() = default;

    void Load(const FilePath& mappingLocation);
    void Save(const FilePath& mappingLocation) const;

    template <typename T>
    const AssetLocation& GetLocationOfAsset(const AssetName<T>& asset)
    {
        AssetName<void> typlessAsset = asset;
        return _mapping[typlessAsset];
    }

    template <typename T>
    void SetAssetLocation(const AssetName<T>& asset, const AssetLocation& location)
    {
        AssetName<void> typlessAsset = asset;
        _mapping[typlessAsset] = location;
    }

private:
    std::unordered_map<AssetName<void>, AssetLocation, AssetNameHasher<void>> _mapping;
};
} // namespace Data