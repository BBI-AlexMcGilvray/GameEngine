#pragma once

#include "Core/IO/Headers/File.h"
#include "Core/Serialization/Formats/JSON/JSON.h"
#include "Core/Serialization/Serialization.h"

#include "Data/Headers/AssetData.h"
#include "Data/Headers/AssetName.h"
#include "Data/Headers/AssetExceptions.h"
#include "Data/Headers/AssetLocation.h"

#include "Data/RawAssets/RawAsset.h"

namespace Data {
void WriteData(const RawAsset& rawAsset, const AssetLocation& location);

template <typename T>
void SerializeData(RawAsset& target, const T& data)
{
    if (std::holds_alternative<RawBinary>(target.data))
    {
        THROW_EXCEPTION(InvalidAssetOperation, "NOT IMPLEMENTED", "We do not support RawBinary yet");
    }

    Serialization::Format::JSON parsedAssetData;
    SerializeTo(parsedAssetData, data);

    RawString data { parsedAssetData.ToString(); };
    target.data = data;
}
}// namespace Data