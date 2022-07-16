#pragma once

#include <string>
#include <variant>

#include "Core/IO/Headers/File.h"
#include "Data/Headers/AssetExceptions.h"

namespace Data {
// this is to be used when an asset is held within a single file
struct IndividualFile
{
    Core::IO::FilePath path;
};
 
// this is to be used when an asset is stored in a file alongside other assets
struct PartOfFile
{
    IndividualFile containingFile;
    uint64 fileOffset;
    uint64 contentSize;
};

struct AssetLocation
{
    std::variant<IndividualFile, PartOfFile> location;
};
}// namespace Data