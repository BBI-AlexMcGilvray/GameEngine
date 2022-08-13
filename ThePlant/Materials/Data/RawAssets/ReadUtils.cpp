#include "Data/RawAssets/Utils.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/IOUtils.h"
#include "Core/Logging/LogFunctions.h"

#include "Data/RawAssets/ReadUtils.h"
#include "Data/RawAssets/WriteUtils.h"

namespace Data {
RawAsset ReadRawAsset(const IndividualFile& individualFile)
{
    File assetFile = Core::IO::OpenFileI(individualFile.path);

    // this is where we check if the file is binary or text in the future
    RawString data = { assetFile.GetFullText() };
    return { data };
}

RawAsset ReadRawAsset(const PartOfFile& containingFile)
{
    CORE_THROW_EXCEPTION(InvalidAssetOperation, "NOT IMPLEMENTED", "We do not support PartOfFile yet");
}

struct RawAssetReader
{
    RawAsset operator()(const IndividualFile& individualFile) const
    {
        return ReadRawAsset(individualFile);
    }

    RawAsset operator()(const PartOfFile& containingFile) const
    {
        return ReadRawAsset(containingFile);
    }
};

RawAsset ReadData(const AssetLocation& location)
{
    return std::visit(RawAssetReader(), location.location);
}
}// namespace Data