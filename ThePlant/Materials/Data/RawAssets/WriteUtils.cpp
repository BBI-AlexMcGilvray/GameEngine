#include "Data/RawAssets/Utils.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/IOUtils.h"
#include "Core/Logging/LogFunctions.h"

#include "Data/RawAssets/ReadUtils.h"
#include "Data/RawAssets/WriteUtils.h"

namespace Data {
void WriteData(const RawBinary& rawAsset, const IndividualFile& individualFile)
{
    CORE_THROW_EXCEPTION(InvalidAssetOperation, "NOT IMPLEMENTED", "We do not support RawBinary yet");
}

void WriteData(const RawString& rawAsset, const IndividualFile& individualFile)
{
    File assetFile = Core::IO::OpenFileO(individualFile.path);
    assetFile.Write(rawAsset.data);
}

void WriteData(const RawBinary& rawAsset, const PartOfFile& containingFile)
{
    CORE_THROW_EXCEPTION(InvalidAssetOperation, "NOT IMPLEMENTED", "We do not support PartOfFile yet");
}

void WriteData(const RawString& rawAsset, const PartOfFile& containingFile)
{
    CORE_THROW_EXCEPTION(InvalidAssetOperation, "NOT IMPLEMENTED", "We do not support PartOfFile yet");
}

struct RawAssetWriter
{
    void operator()(const RawBinary& rawAsset, const IndividualFile& individualFile) const
    {
        WriteData(rawAsset, individualFile);
    }

    void operator()(const RawString& rawAsset, const IndividualFile& individualFile) const
    {
        WriteData(rawAsset, individualFile);
    }

    void operator()(const RawBinary& rawAsset, const PartOfFile& containingFile) const
    {
        WriteData(rawAsset, containingFile);
    }

    void operator()(const RawString& rawAsset, const PartOfFile& containingFile) const
    {
        WriteData(rawAsset, containingFile);
    }
};

void WriteData(const RawAsset& rawAsset, const AssetLocation& location)
{
    std::visit(RawAssetWriter(), rawAsset.data, location.location);
}
}// namespace Data