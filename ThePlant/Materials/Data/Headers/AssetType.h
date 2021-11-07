#pragma once

#include <string>

#include "Core/Headers/Hash.h"
#include "Data/Headers/AssetExceptions.h"

using namespace Core;

namespace Data {
template<typename T = void>
struct AssetType
{
  static Hash ClassHash()
  {
    return HashValue("void");
  }

  static std::string GetPath()
  {
    return "";
  }

  static std::string GetFileType()
  {
    return "";
  }
};
}// namespace Data