#pragma once

#include "Core/Headers/Exception.h"

using namespace Core;

namespace Data {
struct AssetException : Exception
{
  using Exception::Exception;
};

struct InvalidAssetOperation : AssetException
{
  using AssetException::AssetException;

  InvalidAssetOperation(const std::string& message)
  : AssetException(message)
  {}
};

struct InvalidAsset : AssetException
{
  using AssetException::AssetException;
};

struct FailureToLoad : AssetException
{
  using AssetException::AssetException;
};
}// namespace Data