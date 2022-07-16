#pragma once

#include <string>
#include <variant>
#include <vector>

#include "Data/Headers/AssetExceptions.h"

namespace Data {
struct RawBinary
{
    std::vector<bool> data;
};

struct RawString
{
    std::string data;
};

// can also do things for RawImage etc (although maybe thats just binary?)

struct RawAsset
{
    std::variant<RawBinary, RawString> data;
};
}// namespace Data